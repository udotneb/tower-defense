//
//  projectile.hpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/25/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef projectile_hpp
#define projectile_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <list>

#endif /* projectile_hpp */

class Projectile {
    int x;
    int y;
    int vel_x;
    int vel_y;
    int time_left;
    sf::CircleShape projectile_drawable;
    
public:
    Projectile(int x1, int y1, int x2, int y2, int time_left_);
    void move_projectile();
    void draw_projectile(sf::RenderWindow *window);
    bool done(); // whether or not to remove from projectile list, returns true when time_left <= 0
};

void draw_projectiles(std::list <Projectile> *projectile_lst, sf::RenderWindow *window);
void move_projectiles(std::list <Projectile> *projectile_lst);

