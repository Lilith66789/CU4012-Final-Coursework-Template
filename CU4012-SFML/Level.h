#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include "Framework/TileManager.h"
#include "Framework/AudioManager.h"
#include "Background.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <iostream>

class Level : public BaseLevel {
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, sf::View* view, World* w, TileManager* tm);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();
	void adjustViewToWindowSize(unsigned int width, unsigned int height);
private:
	// Default variables for level class.
	Player player;

	Enemy enemyArray[5];

	BackgroundManager backgroundMng;

	sf::Sprite testSprite;
	sf::Texture testTex;
};