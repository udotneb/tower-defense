
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <iterator>
#include <iostream>
#include "ResourcePath.hpp"

#include "turret.hpp"

const int HEIGHT = 800;
const int WIDTH = 600;

bool load_icon(sf::RenderWindow *window) {
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return false;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    return true;
}

void initialize_path(Path *path) {
    for (int i = 0; i < HEIGHT; i++) {
        path->add_to_path(i, WIDTH / 2);
    }
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    if (!load_icon(&window)) {
        return EXIT_FAILURE;
    }
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    
    // add a circle
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color(100, 250, 50));
    float x = 50.f;
    
    std::list <Enemy> enemy_lst;
    std::list <Turret> turret_lst;
    std::list <Projectile> projectile_lst;
    
    Path path;
    initialize_path(&path);
    
    int game_time = 0;
    // Start the game loop
    while (window.isOpen())
    {
        if (game_time % 50 == 0) {
            Enemy e;
            enemy_lst.push_back(e);
        }
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                Turret turret(localPosition.x, localPosition.y, 50, &path);
                turret_lst.push_back(turret);
            }
            
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            
        }
        
        window.clear();
    
        // Draw the sprite
        window.draw(sprite);
        
        
        // Draw on enemy path
        path.draw_path_blocks(&window);
        
        draw_turrets(&turret_lst, &window);
        fire_turrets(&turret_lst, &projectile_lst);
        
        move_projectiles(&projectile_lst);
        draw_projectiles(&projectile_lst, &window);
        
        // move and draw enemies
        move_enemies(&enemy_lst, &path);
        draw_enemies(&enemy_lst, &window);
        
        draw_turret_fire_radius_outline(&turret_lst, &window);
        // Update the window
        window.display();
        game_time++;
    }

    return EXIT_SUCCESS;
}
