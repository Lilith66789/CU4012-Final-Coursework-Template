#include "Enemy.h"

Enemy::Enemy()
{

	speed = 300;

	enemySpriteSheet.loadFromFile("gfx/toothwalker/toothwalker/tooth walker sprite-Sheet.png");
	setSize(sf::Vector2f(16 * 4, 44 * 4));
	setPosition(400, 400);
	setTexture(&enemySpriteSheet);


	idle.addFrame(sf::IntRect(32, 80, 16, 44));
	idle.addFrame(sf::IntRect(96, 80, 16, 44));
	idle.addFrame(sf::IntRect(160, 80, 16, 44));
	idle.addFrame(sf::IntRect(224, 80, 16, 44));

	idle.setFrameSpeed(1.f / 2.f);

	walk.addFrame(sf::IntRect(32, 16, 16, 44));
	walk.addFrame(sf::IntRect(96, 16, 16, 44));
	walk.addFrame(sf::IntRect(158, 16, 16, 44));
	walk.addFrame(sf::IntRect(220, 16, 16, 44));
	walk.addFrame(sf::IntRect(282, 16, 16, 44));
	walk.addFrame(sf::IntRect(350, 16, 16, 44));

	walk.setFrameSpeed(1.f / 4.f);

	currentAnimation = &walk;
	setTextureRect(currentAnimation->getCurrentFrame());
}

void Enemy::handleInput(float dt)
{
	isMoving = false;
	velocity.x = 0;
	setTextureRect(currentAnimation->getCurrentFrame());

	currentAnimation->animate(dt);
}
