#include "Player.h"
#include <SDL.h>
#include <iostream>
#include "Gun.h"
#include <ResourceManager.h>

Player::Player() :
    _currentGunIndex(-1) {
    // Empty
}

Player::~Player() {
    // Empty
}

void Player::init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets) {
    _speed = speed;
    _position = pos;
    _inputManager = inputManager;
    _bullets = bullets;
    _camera = camera;	
	_color.r = 200;
	_color.g = 200;
	_color.b = 200;
    _color.a = 255;
    _health = 150;
}

void Player::addGun(Gun* gun) {
    // Add the gun to his inventory
    _guns.push_back(gun);

    // If no gun equipped, equip gun.
    if (_currentGunIndex == -1) {
        _currentGunIndex = 0;
    }
}

void Player::draw(Bengine::SpriteBatch& _spriteBatch) {

	textureID[0] = Bengine::ResourceManager::getTexture("Textures/Hero1.png").id;
	textureID[1] = Bengine::ResourceManager::getTexture("Textures/Hero2.png").id;
	textureID[2] = Bengine::ResourceManager::getTexture("Textures/Hero3.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	if (_animation <= 10 || _animation <= 40)
	{
		_spriteBatch.draw(destRect, uvRect, textureID[0], 0.0f, _color);
		_spriteBatch1 = _spriteBatch;
	}
	else if (_animation <= 20 || _animation <= 50)
	{
		_spriteBatch.draw(destRect, uvRect, textureID[1], 0.0f, _color);
		_spriteBatch2 = _spriteBatch;
	}
	else if (_animation <= 30 || _animation <= 60)
	{
		_spriteBatch.draw(destRect, uvRect, textureID[2], 0.0f, _color);
		_spriteBatch3 = _spriteBatch;
	}
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies) {

    if (_inputManager->isKeyPressed(SDLK_w)) {
        _position.y += _speed;
		_animation++;
    } else if (_inputManager->isKeyPressed(SDLK_s)) {
        _position.y -= _speed;
		_animation++;
    }
    if (_inputManager->isKeyPressed(SDLK_a)) {
        _position.x -= _speed;
		_animation++;
    } else if (_inputManager->isKeyPressed(SDLK_d)) {
        _position.x += _speed;
		_animation++;
    }
	if (_animation == 60)
	{
		_animation = 0;
	}

    if (_inputManager->isKeyPressed(SDLK_1) && _guns.size() >= 0) {
        _currentGunIndex = 0;
    } else if (_inputManager->isKeyPressed(SDLK_2) && _guns.size() >= 1) {
        _currentGunIndex = 1;
    } else if (_inputManager->isKeyPressed(SDLK_3) && _guns.size() >= 2) {
        _currentGunIndex = 2;
    }

    if (_currentGunIndex != -1) {

        glm::vec2 mouseCoords = _inputManager->getMouseCoords();
        mouseCoords = _camera->convertScreenToWorld(mouseCoords);

        glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		//std::cout << "mouseCoords x:" << mouseCoords.x << " mouseCoords y:" << mouseCoords.y << std::endl;
        glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

        _guns[_currentGunIndex]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT),
                                        centerPosition,
                                        direction,
                                        *_bullets);                                  

    }

    collideWithLevel(levelData);
}
