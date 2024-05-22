#include "Player.h"

Player::Player()
{
	speed = 700;
	health = 100;
	CollectableCount = 0;

	playerSpriteSheet.loadFromFile("gfx/DarkSamuraiAssets/DarkSamurai (64x64).png");
	setSize(sf::Vector2f(60*2, 81*2));
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

	currentAnimation = &walk;
	setTextureRect(currentAnimation->getCurrentFrame());

	duck.addFrame(sf::IntRect(0, 44, 17, 17));
	duck.setFrameSpeed(1.f / 2.f);
}

void Player::handleInput(float dt)
{

	isMoving = false;
	velocity.x = 0;
	setTextureRect(currentAnimation->getCurrentFrame());

	if (input->isKeyDown(sf::Keyboard::A)) {
		velocity.x = -speed;
		currentAnimation = &walk;
		currentAnimation->setFlipped(true);
		idle.setFlipped(true);
		jump.setFlipped(true);
		isMoving = true;
		isFlipped = true;
	}

	else if (input->isKeyDown(sf::Keyboard::D)) {
		velocity.x = speed;
		currentAnimation = &walk;
		currentAnimation->setFlipped(false);
		idle.setFlipped(false);
		jump.setFlipped(false);
		isMoving = true;
		isFlipped = false;
	}


	else {
		//currentAnimation->reset();
		currentAnimation = &idle;
	}

	if (input->isKeyDown(sf::Keyboard::Space) && canJump || input->isKeyDown(sf::Keyboard::W)&&canJump) {
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

	if (CollisionWithTag("Collectable")) {
		AddCollectable();
		std::cout << CollectableCount << std::endl;
		
	}

	if (input->isLeftMouseDown())
	{
		//set Key up 
		input->setLeftMouse(Input::MouseState::UP); // Mark the mouse click as handled

		// Create a new projectile
		Projectiles* bullet = new Projectiles();
		if (isFlipped == false) {
			sf::Vector2f BulletPos = getPosition() - sf::Vector2f(-120,- 81);
			bullet->setPosition(BulletPos);
		}
		else if(isFlipped == true){
			sf::Vector2f BulletPos = getPosition() + sf::Vector2f(0, 81);
			bullet->setPosition(BulletPos);
		}
		// Calculate the position of the mouse
		sf::Vector2f MousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());

		// Calculate the direction from the bullet's position to the mouse position
		sf::Vector2f direction = MousePos - getPosition();

		// Normalize the direction vector
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f normalizedDirection = direction / magnitude;

		// Set the velocity of the bullet to be in the direction of the mouse
		// Adjust the speed as needed by multiplying the normalized direction by the desired speed
		if (isFlipped == true) {
			bullet->setVelocity(-1000,0); // You can adjust the speed by changing 1000.f
		}
		else if (isFlipped == false) {
			bullet->setVelocity(1000, 0);
		}

		// Add the bullet to the list of bullets
		bullets.push_back(bullet);

		// Add the bullet to the world
		world->AddGameObject(*bullet);
	}







	currentAnimation->animate(dt);

}

void Player::ReduceHealth(float h)
{
	health -= h;
}
