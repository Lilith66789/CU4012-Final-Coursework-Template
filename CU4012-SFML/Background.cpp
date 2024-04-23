#include "Background.h"
#include "Framework/WindowSize.h"
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
    float baseSpeed = 50.0f; // Adjust this value as needed

    // Loop through each row
    for (int row = 0; row < 5; ++row)
    {
        // Calculate the speed for this row based on its index
        // The idea is to move the sprites in the rows with lower indices slower than those in the rows with higher indices
        float speed = baseSpeed * (5 - row); // Adjust the formula as needed to get the desired effect

        // Loop through each column in the current row
        for (int col = 0; col < 5; ++col)
        {
            // Get the current sprite
            sf::Sprite& sprite = dayBackgrounds.getBackgroundSprite(row, col);

            // Calculate the new position based on the speed and the time delta
            float newX = sprite.getPosition().x - speed * dt;

            // If the sprite has moved off the screen, reset its position to the right side of the screen
            if (newX < -WINDOWWIDTH)
            {
                newX += WINDOWWIDTH * 5; // Adjust this value based on the number of columns
            }

            // Update the sprite's position
            sprite.move(newX, sprite.getPosition().y);
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