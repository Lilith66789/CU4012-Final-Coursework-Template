#include "Background.h"
#include "Framework/WindowSize.h"
#include "Level.h"
Background::Background()
{
    // Load textures 
    scaleFactor = 7;
    LoadTextures();
}
void Background::LoadTextures()
{
    for (int a = 0; a < 5; a++)
    {
        for (int b = 1; b <= 5; b++)
        {
            if (b == 4)
            {
                b = 5;
            }
            if (!backgroundTex[a][b-1].loadFromFile("gfx/free-scrolling-city-backgrounds-pixel-art/Backgrounds/" + std::to_string(a + 1) + "/Day/" + std::to_string(b) + ".png"))
            {
                // Handle error
            }
            backgroundSprites[a][b-1].setTexture(backgroundTex[a][b-1]);
            backgroundSprites[a][b - 1].setScale(scaleFactor, scaleFactor);
            backgroundSprites[a][b - 1].setPosition(WINDOWWIDTH * a, 0);
        }
    }
    
}

BackgroundManager::BackgroundManager()
{
}

void BackgroundManager::update(float dt)
{
    // Define the base speed for the parallax effect
    

    // Loop through each row
    for (int row = 0; row < 5; ++row)
    {

        // Loop through each column in the current row
        for (int col = 0; col < 5; ++col)
        {
 

            
        }
    }
}

void BackgroundManager::render(sf::RenderWindow* window)
{
    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++)
        {
            std::cout << "Draw backrgound" << a << b <<" Position: "<<WINDOWWIDTH*a<<":"<<0 << std::endl;
            window->draw(dayBackgrounds.getBackgroundSprite(a, b));
        }
    }
}