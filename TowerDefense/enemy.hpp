//
//  ball.hpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 3/29/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef enemy_hpp
#define enemy_hpp

#include <stdio.h>
#include "list"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#endif /* enemy_hpp */

const float ENEMY_RADIUS = 30.f;


class Enemy {
    // for drawing the object
    sf::CircleShape circle;
    
public:
    int index;
    int speed;
    int health;

    float x;
    float y;

    Enemy();
    void draw_enemy(sf::RenderWindow *window);
    bool is_dead();
};

void draw_enemies(std::list <Enemy> *enemy_lst, sf::RenderWindow *window);
