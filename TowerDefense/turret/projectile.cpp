//
//  projectile.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/25/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "projectile.hpp"

Projectile::Projectile(int x1, int y1, int x2, int y2, int time_left_) {
    // x1 y1 are the starting coordinates, x2 y2 are the destination coordinates
    x = x1;
    y = y1;
    time_left = time_left_;
    
    vel_x = (x2 - x1) / time_left;
    vel_y = (y2 - y1) / time_left;
    
    sf::CircleShape projectile_drawable_(5.f);
    projectile_drawable = projectile_drawable_;
    projectile_drawable.setFillColor(sf::Color(250, 250, 250));
    projectile_drawable.setOrigin(projectile_drawable.getRadius(), projectile_drawable.getRadius());
    projectile_drawable.setPosition(x, y);
}

void Projectile::move_projectile() {
    x += vel_x;
    y += vel_y;
    time_left--;
}

void Projectile::draw_projectile(sf::RenderWindow *window) {
    projectile_drawable.setPosition(x, y);
    window->draw(projectile_drawable);
}

void move_projectiles(std::list <Projectile> *projectile_lst) {
    // moves all of the projectiles
    std::list<Projectile>::iterator it = projectile_lst->begin();
    while(it != projectile_lst->end()) {
        it->move_projectile();
        if (it->done()) {
            projectile_lst->erase(it++);
        } else {
            it++;
        }
    }
}

void draw_projectiles(std::list <Projectile> *projectile_lst, sf::RenderWindow *window) {
    for (std::list<Projectile>::iterator it = projectile_lst->begin(); it != projectile_lst->end(); ++it){
        it->draw_projectile(window);
    }
}

bool Projectile::done() {
    // whether or not to remove from projectile list, returns true when time_left <= 0
    return time_left <= 0;
}
