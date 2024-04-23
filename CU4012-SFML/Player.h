#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Player : public GameObject
{
	int speed;
	Animation walk;
	Animation swim;
	Animation duck;
	Animation idle;
	Animation jump;

	Animation* currentAnimation;

	sf::Texture playerSpriteSheet;

public:
	Player();
	void handleInput(float dt) override;
	bool isMoving;
};

