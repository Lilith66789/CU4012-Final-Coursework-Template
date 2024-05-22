#include "DeathScreen.h"
#include "Framework/WindowSize.h"
#include "Player.h"

Death::Death(sf::RenderWindow* hwnd, Input* in, GameState* DEAD)
{
	window = hwnd;
	input = in;
	gameState = DEAD;


	UIfont.loadFromFile("font/VirtualRotRegular-R51V.ttf");
	titleFont.loadFromFile("font/VirtualRotRegular-R51V.ttf");


	menu_texture.loadFromFile("gfx/menu.png");
	menu_sprite.setTexture(menu_texture);
	menu_sprite.setScale(1, 1);


	Title.setFont(titleFont);
	Title.setFillColor(sf::Color::Magenta);
	Title.setString("You Have Died");
	Title.setOutlineColor(sf::Color::Black);
	Title.setCharacterSize(70);
	Title.setPosition(0.5 * WINDOWWIDTH, WINDOWHEIGHT - 200);



	UIText[1].text.setFont(UIfont);
	UIText[1].text.setFillColor(sf::Color::White);
	UIText[1].text.setString("Exit");
	UIText[1].text.setPosition(sf::Vector2f(0.5* WINDOWWIDTH, WINDOWHEIGHT -200));
	UIText[1].setCollisionBox(sf::FloatRect(600, 165, 35, 15));



	selectedItem = 0;

	mouseOverAnyItem = false;

}
Death::~Death()
{
}

void Death::update(float dt)
{
	mouseOverAnyItem = false; // Reset this flag each frame


	// Update the position of the text
	sf::Vector2u windowSize = window->getSize();

	float TextOffset = 1.5;
	Title.setPosition(WINDOWWIDTH/ TextOffset - Title.getGlobalBounds().width / TextOffset, 50);


	UIText[0].text.setPosition(sf::Vector2f(WINDOWWIDTH / TextOffset - UIText[0].text.getGlobalBounds().width / TextOffset, 120));
	UIText[0].setCollisionBox(sf::FloatRect(WINDOWWIDTH / TextOffset - UIText[0].text.getGlobalBounds().width / TextOffset, 135, 35, 15));

	UIText[1].text.setPosition(WINDOWWIDTH / TextOffset - UIText[1].text.getGlobalBounds().width / TextOffset, 150);
	UIText[1].setCollisionBox(sf::FloatRect(WINDOWWIDTH / TextOffset - UIText[1].text.getGlobalBounds().width / TextOffset, 165, 35, 15));


	// Update mouse position
	MousePos.x = input->getMouseX();
	MousePos.y = input->getMouseY();

	for (int i = 0; i < 2; i++) {
		if (Collision::checkBoundingBox(UIText[i].getCollisionBox(), MousePos)) {
			if (!mouseOverAnyItem) { // Only change if the mouse wasn't already over an item
				selectedItem = i;
				mouseOverAnyItem = true;
			}
		}
	}

	updateVisualFeedback(); // Update visual feedback at the end to reflect any changes
}

void Death::updateVisualFeedback()
{
	for (int i = 0; i < 2; i++) {
		if (i == selectedItem) {
			UIText[i].text.setFillColor(sf::Color::Red); // Highlight selected item
		}
		else {
			UIText[i].text.setFillColor(sf::Color::White); // Default color for non-selected items
		}
	}
}

void Death::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		UIText[selectedItem].text.setFillColor(sf::Color::White);
		selectedItem--;
		UIText[selectedItem].text.setFillColor(sf::Color::Red);
	}
}
void Death::MoveDown()
{
	if (selectedItem + 1 < 2)
	{
		UIText[selectedItem].text.setFillColor(sf::Color::White);
		selectedItem++;
		UIText[selectedItem].text.setFillColor(sf::Color::Red);
	}

}
int Death::handleInput(float dt)
{
	// Keyboard handling for menu navigation
	if (input->isKeyDown(sf::Keyboard::Up)) {
		MoveUp();
		input->setKeyUp(sf::Keyboard::Up);
	}

	if (input->isKeyDown(sf::Keyboard::Down)) {
		MoveDown();
		input->setKeyUp(sf::Keyboard::Down);
	}

	// Execute action for the current selected item
	if (input->isKeyDown(sf::Keyboard::Enter) || (input->isLeftMouseDown() && mouseOverAnyItem)) {
		switch (selectedItem) {
		case 0:
			std::cout << "Play Button has been pressed" << std::endl;
			gameState->setCurrentState(State::LEVEL);
			break;
		case 1:
			std::cout << "Exit Button has been pressed" << std::endl;
			exit(0);
			break;
		}

		// Reset input states
		if (input->isKeyDown(sf::Keyboard::Enter)) {
			input->setKeyUp(sf::Keyboard::Enter);
		}
		if (input->isLeftMouseDown()) {
			input->setLeftMouse(Input::MouseState::UP); // Assuming you have a method to reset the mouse state
		}
	}

	return 0; // Return value can be used if needed for further input handling logic

}

void Death::render()
{
	window->draw(menu_sprite);
	window->draw(Title);
	for (int i = 0; i < 2; i++)
	{
		window->draw(UIText[i].text);
	}

	//Uncomment so debug shapes for the menu text
	//for (int i = 0; i < 2; i++)
	//{
	//	window->draw(UIText[i].getDebugShape());
	//}

}




void Death::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}
void Death::endDraw()
{
	window->display();
}