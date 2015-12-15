#include "Zombie.h"
#include <ResourceManager.h>
#include "Human.h"

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos) {
    _speed = speed;
    _position = pos;
    _health = 150;
    // Set Green Color
    _color.r = 200;
    _color.g = 200;
    _color.b = 200;
    _color.a = 255;
}

void Zombie::draw(Bengine::SpriteBatch& _spriteBatch) {

	textureID[0] = Bengine::ResourceManager::getTexture("Textures/Zombie1.png").id;
	textureID[1] = Bengine::ResourceManager::getTexture("Textures/Zombie2.png").id;
	textureID[2] = Bengine::ResourceManager::getTexture("Textures/Zombie3.png").id;

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

void Zombie::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies) {

    // Find the closest human
    Human* closestHuman = getNearestHuman(humans);

    // If we found a human, move towards him
    if (closestHuman != nullptr) {
        // Get the direction vector twoards the player
        glm::vec2 direction = glm::normalize(closestHuman->getPosition() - _position);
        _position += direction * _speed;		
    }

	if (_animation == 60)
	{
		_animation = 0;
	}
	else
	{
		_animation++;
	}

    // Do collision
    collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
    Human* closestHuman = nullptr;
    float smallestDistance = 9999999.0f;

    for (int i = 0; i < humans.size(); i++) {
        // Get the direction vector
        glm::vec2 distVec = humans[i]->getPosition() - _position;
        // Get distance
        float distance = glm::length(distVec);

        // If this person is closer than the closest person, this is the new closest
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closestHuman = humans[i];
        }
    }
    
    return closestHuman;
}