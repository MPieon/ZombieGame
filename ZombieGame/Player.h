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

    void init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);
	Gun* getGun();

    void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;
private:
    Bengine::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;

    Bengine::Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};


