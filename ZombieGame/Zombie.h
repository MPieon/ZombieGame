#pragma once

#include "Agent.h"

class Zombie : public Agent
{
public:
    Zombie();
    ~Zombie();

    void init(float speed, glm::vec2 pos);

	void draw(Bengine::SpriteBatch& _spriteBatch);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies);
	
private:
	Bengine::SpriteBatch _spriteBatch1;
	Bengine::SpriteBatch _spriteBatch2;
	Bengine::SpriteBatch _spriteBatch3;
	const glm::vec4 uvRect;
	glm::vec4 destRect;
	glm::vec2 _direction;
	int textureID[3];
	int _animation;
    Human* getNearestHuman(std::vector<Human*>& humans);
};

