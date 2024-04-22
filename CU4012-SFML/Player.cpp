#include "Player.h"

Player::Player()
{
	speed = 200;

	playerSpriteSheet.loadFromFile("gfx/DarkSamuraiAssets/DarkSamurai (64x64).png");
	setSize(sf::Vector2f(60, 81));
	setPosition(100, 100);
	setTexture(&playerSpriteSheet);


	idle.addFrame(sf::IntRect(16, 16, 32, 32));
	idle.addFrame(sf::IntRect(80, 16, 32, 32));
	idle.addFrame(sf::IntRect(144, 16, 32, 32));
	idle.addFrame(sf::IntRect(208, 16, 32, 32));
	idle.addFrame(sf::IntRect(272, 16, 32, 32));
	idle.addFrame(sf::IntRect(336, 16, 32, 32));
	idle.addFrame(sf::IntRect(400, 16, 32, 32));
	idle.addFrame(sf::IntRect(464, 16, 32, 32));

	idle.setFrameSpeed(1.f / 8.f);


	walk.addFrame(sf::IntRect(16, 80, 32, 32));
	walk.addFrame(sf::IntRect(80, 80, 32, 32));
	walk.addFrame(sf::IntRect(144, 80, 32, 32));
	walk.addFrame(sf::IntRect(208, 80, 32, 32));
	walk.addFrame(sf::IntRect(272, 80, 32, 32));
	walk.addFrame(sf::IntRect(336, 80, 32, 32));
	walk.addFrame(sf::IntRect(400, 80, 32, 32));
	walk.addFrame(sf::IntRect(464, 80, 32, 32));

	walk.setFrameSpeed(1.f / 10.f);

	jump.addFrame(sf::IntRect(16, 272, 32, 32));
	jump.addFrame(sf::IntRect(80, 272, 32, 32));
	jump.addFrame(sf::IntRect(144, 272, 32, 32));
	jump.addFrame(sf::IntRect(208, 272, 32, 32));
	jump.addFrame(sf::IntRect(16, 336, 32, 32));
	jump.addFrame(sf::IntRect(80, 336, 32, 32));
	jump.addFrame(sf::IntRect(144, 336, 32, 32));
	jump.addFrame(sf::IntRect(208, 336, 32, 32));

	jump.setFrameSpeed(1.f / 6.f);

	swim.addFrame(sf::IntRect(0, 21, 16, 20));
	swim.addFrame(sf::IntRect(16, 21, 16, 20));
	swim.addFrame(sf::IntRect(32, 21, 16, 20));
	swim.setFrameSpeed(1.f / 4.f);

	currentAnimation = &walk;
	setTextureRect(currentAnimation->getCurrentFrame());

	duck.addFrame(sf::IntRect(0, 44, 17, 17));
	duck.setFrameSpeed(1.f / 2.f);


}

void Player::handleInput(float dt)
{
	velocity.x = 0;
	setTextureRect(currentAnimation->getCurrentFrame());

	if (input->isKeyDown(sf::Keyboard::A)) {
		velocity.x = -speed;
		currentAnimation = &walk;
		currentAnimation->setFlipped(true);
		idle.setFlipped(true);
		jump.setFlipped(true);
	}

	else if (input->isKeyDown(sf::Keyboard::D)) {
		velocity.x = speed;
		currentAnimation = &walk;
		currentAnimation->setFlipped(false);
		idle.setFlipped(false);
		jump.setFlipped(false);
	}

	else if (input->isKeyDown(sf::Keyboard::S)) {
		currentAnimation = &duck;
	}


	else {
		//currentAnimation->reset();
		currentAnimation = &idle;
	}

	if (input->isKeyDown(sf::Keyboard::Space) && canJump) {
		Jump(200.f);
		audio->playSoundbyName("jump");
	}

	if (!canJump)
	{
		currentAnimation = &jump;
	}
	else
	{
		jump.reset();
	}


	currentAnimation->animate(dt);

}