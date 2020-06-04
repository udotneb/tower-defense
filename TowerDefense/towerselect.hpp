//
//  towerselect.hpp
//  TowerDefense
//
//  Created by Benjamin Ulrich on 5/29/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef towerselect_hpp
#define towerselect_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#endif /* towerselect_hpp */

class TowerSelect {
    sf::RectangleShape underlying_rect;
    
    std::list <sf::RectangleShape> rect_lst;
    std::list <sf::CircleShape> circ_lst;
    
    sf::RectangleShape get_rect(int index);
    sf::CircleShape get_circ(int index);
    
public:
    TowerSelect(); // initializes the tower select window
    bool panel_pressed(sf::RenderWindow *window, sf::Vector2i mouse_position);
    int index_pressed_tower(sf::RenderWindow *window, sf::Vector2i mouse_position);
    void draw_pressed_tower(int index);
    void draw_tower_select(sf::RenderWindow *window);
};
