#include "Human.h"
#include <ctime>
#include <random>
#include <gtx/rotate_vector.hpp>
#include <ResourceManager.h>

Human::Human() : _frames(0) {

}


Human::~Human() {

}

void Human::init(float speed, glm::vec2 pos) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

	_health = 20;

	_color.r = 200;
	_color.g = 200;
	_color.b = 200;
	_color.a = 255;

	_speed = speed;
	_position = pos;
	// Get random direction
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	// Make sure direction isn't zero
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

	_direction = glm::normalize(_direction);

}

void Human::draw(Bengine::SpriteBatch& _spriteBatch) {

	textureID[0] = Bengine::ResourceManager::getTexture("Textures/Civ1.png").id;	
	textureID[1] = Bengine::ResourceManager::getTexture("Textures/Civ2.png").id;
	textureID[2] = Bengine::ResourceManager::getTexture("Textures/Civ3.png").id;

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
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

void Human::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) {

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

	_position += _direction * _speed;
	
    // Randomly change direction every 20 frames
    if (_frames == 20) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    } else {
        _frames++;
    }
	if (_animation == 60)
	{
		_animation = 0;
	}
	else
	{
		_animation++;
	}

    if (collideWithLevel(levelData)) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    }
}