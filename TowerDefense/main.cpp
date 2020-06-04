
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
#include "towerselect.hpp"

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
    
    std::list <Enemy> enemy_lst;
    std::list <Turret> turret_lst;
    std::list <Projectile> projectile_lst;
    
    Path path;
    initialize_path(&path);
    TowerSelect tower_select;
    
    int tower_place_index = -1; // index of tower that the player is trying to place, is -1 if no tower
    int game_time = 0;
    sf::Vector2i mouse_position;
    
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
            
            mouse_position = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (tower_select.panel_pressed(&window, mouse_position)) { // selecting a tower from the menu
                    tower_place_index = tower_select.index_pressed_tower(&window, mouse_position); // get tower from menu
                    std::cout << tower_place_index;
                    std::cout << "\n";
                } else { // placing a tower
                    if (tower_place_index != -1) {
                        Turret t(mouse_position.x, mouse_position.y, tower_place_index, &path);
                        turret_lst.push_back(t);
                        tower_place_index = -1;
                    }
                }
            }
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
        
        if (tower_place_index != -1) {
            draw_mouse_turret(&window, mouse_position.x, mouse_position.y, tower_place_index);
        } else { // draw on fire_radius of turret being hovered over
            draw_turret_fire_radius_outline(&turret_lst, &window, mouse_position);
        }

        tower_select.draw_tower_select(&window);
        
        // Update the window
        window.display();
        game_time++;
    }

    return EXIT_SUCCESS;
}
