#include "Enemy.h"

Enemy::Enemy()
{

	speed = 300;

	enemySpriteSheet.loadFromFile("gfx/tooth walker/tooth walker/tooth walker sprite - Sheet.png");
	setSize(sf::Vector2f(13 * 4, 44 * 4));
	setPosition(400, 400);
	setTexture(&enemySpriteSheet);

	if (!enemySpriteSheet.loadFromFile("gfx/toothwalker/toothwalker/tooth walker sprite-Sheet.png")) {
		std::cout << "Error loading enemy sprite sheet" << std::endl;
	}


	idle.addFrame(sf::IntRect(32, 80, 16, 48));
	idle.addFrame(sf::IntRect(96, 80, 13, 48));
	idle.addFrame(sf::IntRect(160, 80, 13, 48));
	idle.addFrame(sf::IntRect(224, 80, 13, 48));

	idle.setFrameSpeed(1.f / 2.f);

	currentAnimation = &idle;
	setTextureRect(currentAnimation->getCurrentFrame());
}

void Enemy::handleInput(float dt)
{
	isMoving = false;
	velocity.x = 0;
	setTextureRect(currentAnimation->getCurrentFrame());

	currentAnimation->animate(dt);
}
