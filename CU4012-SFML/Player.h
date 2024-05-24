#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Projectiles.h"
#include "Framework/World.h"
#include<vector>
#include <iostream>

class Player : public GameObject
{
	//constructs variables and animations the player uses
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

	std::vector<Projectiles*> bullets;

	World* world;


public:
	//constructs functions for the player class to use
	Player();
	void handleInput(float dt) override;
	bool isMoving ;
	bool isFlipped;
	void AddCollectable() { CollectableCount++; }
	int getCollectableCount() { return CollectableCount; }
	void ReduceHealth(float h);
	float getHealth() { return health; }

	void setWorld(World* world) { this->world = world; }

	std::vector<Projectiles*>& getBullets() { return bullets; }
};

