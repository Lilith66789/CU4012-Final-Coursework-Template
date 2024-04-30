#include "Enemy.h"

Enemy::Enemy()
{

	speed = 300;

	enemySpriteSheet.loadFromFile("gfx/tooth walker/ tooth walker/ tooth walker sprite-Sheet.png");
	setSize(sf::Vector2f(60 * 2, 81 * 2));
	setPosition(400, 400);
	setTexture(&enemySpriteSheet);


	idle.addFrame(sf::IntRect(32, 80, 13, 44));
	idle.addFrame(sf::IntRect(96, 80, 13, 44));
	idle.addFrame(sf::IntRect(160, 80, 32, 32));
	idle.addFrame(sf::IntRect(208, 16, 32, 32));
	idle.addFrame(sf::IntRect(272, 16, 32, 32));
	idle.addFrame(sf::IntRect(336, 16, 32, 32));
	idle.addFrame(sf::IntRect(400, 16, 32, 32));
	idle.addFrame(sf::IntRect(464, 16, 32, 32));

	idle.setFrameSpeed(1.f / 8.f);
}
