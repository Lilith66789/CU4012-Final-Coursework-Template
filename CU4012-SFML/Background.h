#pragma once
#include "Framework/GameObject.h"

/*
 To use a 2-dimensional array for background textures,
 we would need a 2d array for sf::Texture
 we would load all the into the 2d array and when we draw them,
 we draw them as blocks instead of individual textures.


All the different background textures are loaded in the background class
it uses a 2d array to achieve that.


each bacground contains 4 individual textures which are layered on top to achive a background/foreground depth

we need 4 of these backgrounds.


new approach instead of using gameobjects to move the texture 
we are assigning the texture to a sprite which then can be moved around 

the way it works we have a 5x5 grid of texture and sprites we load and set them.
*/
class Background
{
	int scaleFactor;
	sf::Texture backgroundTex[5][5];
	sf::Sprite backgroundSprites[5][5];
public:
	Background();
	sf::Sprite& getBackgroundSprite(int row, int column) { return backgroundSprites[row][column]; }
	void LoadTextures();
};

class BackgroundManager
{
	Background dayBackgrounds;

public:
	BackgroundManager();
	void update(float dt);
	void render(sf::RenderWindow* wind);
	//sf::Sprite
};

