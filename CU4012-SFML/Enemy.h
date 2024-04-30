#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Enemy : public GameObject
{

	int speed;
	Animation walk;
	Animation idle;

	Animation* currentAnimation;

	sf::Texture enemySpriteSheet;

public:
	Enemy();
	bool isMoving;

};

