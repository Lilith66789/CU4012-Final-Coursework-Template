#include "Projectiles.h"

Projectiles::Projectiles()
{
	speed = 500;
	velocity.x = speed;
	if (!texture.loadFromFile("gfx/Beach_Ball.png"))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
	setSize(sf::Vector2f(10, 10));
	setCollisionBox(getPosition(), getSize());
	setTag("Bullet");
	setMass(10.f);
	//setTrigger(true);
}