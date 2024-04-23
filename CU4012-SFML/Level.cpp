#include "Level.h"
#include "Framework/WindowSize.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	view = v;
	world = w;
	tileManager = tm;
	audioManager = new AudioManager();

	audioManager->addMusic("sfx/Cantina.ogg", "bgm");
	audioManager->addSound("sfx/smb_jump-super.wav", "jump");


	audioManager->playMusicbyName("bgm");


	world->AddGameObject(player);

	player.setInput(input);
	player.setAudio(audioManager);


	if (!testTex.loadFromFile("gfx/free-scrolling-city-backgrounds-pixel-art/Backgrounds/1/Day/1.png"))
	{

	}

	testSprite.setTexture(testTex);
	testSprite.setPosition(0, 0);

}

Level::~Level()
{
	//Making pointers null
	window = nullptr;
	input = nullptr;
	gameState = nullptr;
	view = nullptr;
	world = nullptr;
	tileManager = nullptr;
	if (audioManager != nullptr) {
		delete audioManager;
		audioManager = nullptr;
	}
}

void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		input->setKeyUp(sf::Keyboard::Tab);
		gameState->setCurrentState(State::TILEEDITOR);
	}
	//zomb.handleInput(dt);
	player.handleInput(dt);

}

// Update game objects
void Level::update(float dt)
{

	view->setCenter(view->getCenter().x, WINDOWHEIGHT/2);

	sf::Vector2f playerPosition = player.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);
	if(player.isMoving) backgroundMng.update(dt);

}

// Render level
void Level::render()
{
	beginDraw();
	//window->draw(testSprite);
	backgroundMng.render(window);

	tileManager->render(false);
	//window->draw(zomb);
	window->draw(player);
	
	
	endDraw();
}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}