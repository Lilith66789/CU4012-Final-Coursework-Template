#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
class Player : public GameObject
{
	int speed;
	int health;
	Animation walk;
	Animation swim;
	Animation duck;
	Animation idle;
	Animation jump;

	Animation* currentAnimation;

	sf::Texture playerSpriteSheet;

	int CollectableCount = 0;
	sf::Text collectableText;
	sf::Font font;


public:
	Player();
	void handleInput(float dt) override;
	bool isMoving ;
	void AddCollectable() { CollectableCount++; }
	int getCollectableCount() { return CollectableCount; }
	void ReduceHealth(float h);
	float getHealth() { return health; }
};

