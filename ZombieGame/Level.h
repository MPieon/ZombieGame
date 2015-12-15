#pragma once

#include <string>
#include <vector>

#include <SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
public:
    // Load the level
    Level(const std::string& fileName);
    ~Level();

    void draw();

    // Getters
    int getWidth() const { return _levelData[0].size(); }
    int getHeight() const { return _levelData.size(); }
    int getNumHumans() const { return _numHumans; }
    const std::vector<std::string>& getLevelData() const { return _levelData; }
    glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
    const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPositions; }
	const std::vector<glm::vec2>& getSoldierStartPositions() const { return _soldierStartPositions; }
	const std::vector<std::vector<glm::vec2>>& getSoldierPath() const { return _soldierPathWaypoints; }

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Bengine::SpriteBatch _spriteBatch;

    glm::vec2 _startPlayerPos;
    std::vector<glm::vec2> _zombieStartPositions;

	std::vector<glm::vec2> _soldierStartPositions;
	std::vector<std::vector<glm::vec2>> _soldierPathWaypoints;
};

