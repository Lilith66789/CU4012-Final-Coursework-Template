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
	//audioManager->addMusic("sfx/dark-forest_chosic.com_.ogg", "bgm");
	//audioManager->addSound("sfx/smb_jump-super.wav", "jump");


	audioManager->playMusicbyName("bgm");


	world->AddGameObject(player);
	player.setWorld(world);


	enemyArray[0].setPosition(500, 100);
	enemyArray[1].setPosition(3480, 200);
	enemyArray[2].setPosition(10760,500);
	enemyArray[3].setPosition(9800,608);
	enemyArray[4].setPosition(6560, 1038);

	for (int i = 0; i < 5; i++) {
		world->AddGameObject(enemyArray[i]);
	}

	player.setInput(input);
	player.setAudio(audioManager);

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
	player.handleInput(dt);
	for (int i = 0; i < 5; i++) {
		enemyArray[i].handleInput(dt);
	}

}

// Update game objects
void Level::update(float dt)
{

	view->setCenter(view->getCenter().x, WINDOWHEIGHT / 2);

	sf::Vector2f playerPosition = player.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);

	for (int i = 0; i < 5; i++) {
		if (enemyArray[i].CollisionWithTag("Player")) {
			player.ReduceHealth(0.01 * dt);
		}
	}

	if (player.CollisionWithTag("Collectable"))
	{
		// Player is Colliding with Collectable
		player.AddCollectable(); // Increment Collectable count
		tileManager->RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = player.getCollectableCount(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	if ((player.getHealth() <= 0) || (player.getPosition().y > 1920))
	{
		player.setPosition(100, 100);
		player.setAlive(false);
		world->RemoveGameObject(player);
		view->setCenter(WINDOWWIDTH / 2, WINDOWWIDTH / 2);
		gameState->setCurrentState(State::DEAD);

	}

	if (player.getPosition().x > 12000) {
		player.setPosition(100, 100);
		view->setCenter(WINDOWWIDTH / 2, WINDOWWIDTH / 2);
		gameState->setCurrentState(State::WIN);

	}

	for (int i = 0; i < 5; i++) {
		if (!enemyArray[i].isAlive()) {
			world->RemoveGameObject(enemyArray[i]);
		}
	}
}

// Render level
void Level::render()
{
	if (player.isAlive()) {
	backgroundMng.render(window);
	}

	if (gameState->getCurrentState() == State::TILEEDITOR)
	{
		window->draw(player.getDebugCollisionBox());
	}
	else
	{
		tileManager->render(false);
	}

	if (player.isAlive())
	{
		window->draw(player);
		//window->draw(p1.getDebugCollisionBox());
	}

	for (int i = 0; i < 5; i++) {
		if (enemyArray[i].isAlive())
		{
			window->draw(enemyArray[i]);
			//window->draw(enemyArray[i].getDebugCollisionBox());
		}
	}

	auto bullets = player.getBullets();
	for (auto& bullet : bullets)
	{
		window->draw(*bullet);
		window->draw(bullet->getDebugCollisionBox());
	}


}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}