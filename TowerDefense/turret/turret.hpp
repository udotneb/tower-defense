//
//  turret.hpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/21/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef turret_hpp
#define turret_hpp

#include <stdio.h>
#include "path.hpp"
#include "projectile.hpp"

#endif /* turret_hpp */

class Turret {
    
    int damage;
    int rate_of_fire;
    int current_fire_count;
    float fire_radius;
    int x;
    int y;
    
    std::list <PathBlock*> path_blocks;
    Path *path;
    sf::CircleShape turret_drawable;
    sf::CircleShape fire_radius_drawable;

    
public:
    Turret(float x_, float y_, int turret_index, Path *path_);
    void fire(std::list <Projectile> *projectile_lst);
    void draw_turret(sf::RenderWindow *window);
    void draw_fire_radius(sf::RenderWindow *window, sf::Vector2i mouse_position);
};

void draw_turrets(std::list <Turret> *turret_lst, sf::RenderWindow *window);
void fire_turrets(std::list <Turret> *turret_lst, std::list <Projectile> *projectile_lst);
void draw_turret_fire_radius_outline(std::list <Turret> *turret_lst, sf::RenderWindow *window, sf::Vector2i mouse_position);
void draw_mouse_turret(sf::RenderWindow *window, float x, float y, int turret_index);
