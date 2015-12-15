#pragma once

#include "Human.h"
#include <InputManager.h>
#include <Camera2D.h>
#include "Bullet.h"

class Gun;

class Player : public Human
{
public:
    Player();
    ~Player();

	//static int _texture;

	void init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

	void draw(Bengine::SpriteBatch& _spriteBatch);

    void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;

	
private:
	Bengine::SpriteBatch _spriteBatch1;
	Bengine::SpriteBatch _spriteBatch2;
	Bengine::SpriteBatch _spriteBatch3;
	const glm::vec4 uvRect;
	glm::vec4 destRect;
	glm::vec2 _direction;
	int textureID[3];
	int _animation;

    Bengine::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;	

    Bengine::Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};

