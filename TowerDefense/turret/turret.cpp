//
//  turret.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/21/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "turret.hpp"
#include <iostream>


Turret::Turret(int x_, int y_, float r_, Path *path_) {
    x = x_;
    y = y_;
    fire_radius = r_;
    path = path_;
    path_blocks = path->get_blocks(x, y, fire_radius);
    rate_of_fire = 20;
    current_fire_count = 0;
    
    std::cout << path_blocks.size();
    std::cout << " number of path blocks in turret range \n";

    damage = 10;
    
    sf::CircleShape turret_drawable_(10.f);
    turret_drawable = turret_drawable_;
    turret_drawable.setOrigin(turret_drawable.getRadius(), turret_drawable.getRadius());
    turret_drawable.setFillColor(sf::Color(250, 250, 250));
    turret_drawable.setPosition(x, y);

    
    sf::CircleShape fire_radius_circle_(fire_radius);
    fire_radius_drawable = fire_radius_circle_;
    fire_radius_drawable.setOrigin(fire_radius_drawable.getRadius(), fire_radius_drawable.getRadius());
    fire_radius_drawable.setFillColor(sf::Color(250, 250, 250, 0)); // make the fill 0 opacity
    fire_radius_drawable.setOutlineThickness(5.f);
    fire_radius_drawable.setOutlineColor(sf::Color(250, 150, 100));
    fire_radius_drawable.setPosition(x, y);

}

void Turret::fire(std::list <Projectile> *projectile_lst) {
    Enemy *e = 0;
    
    current_fire_count++;
    if (current_fire_count % rate_of_fire != 0) {
        return;
    }
    
    for (std::list<PathBlock*>::iterator it = path_blocks.begin(); it != path_blocks.end(); ++it) {
        PathBlock *path_block = *it;
        std::list <Enemy*> enemy_lst = path_block->enemies_here;
        for (std::list<Enemy*>::iterator iter = enemy_lst.begin(); iter != enemy_lst.end(); ++iter) {
            e = (*iter);
        }
    }
    
    if (e != 0) {
        e->health -= damage;
        Projectile p(this->x, this->y, e->x, e->y, 5);
        projectile_lst->push_back(p);
    }
}

void Turret::draw_turret(sf::RenderWindow *window) {
    window->draw(turret_drawable);
}

void Turret::draw_fire_radius(sf::RenderWindow *window) {
    window->draw(fire_radius_drawable);
}

void draw_turrets(std::list <Turret> *turret_lst, sf::RenderWindow *window) {
    for (std::list<Turret>::iterator it = turret_lst->begin(); it != turret_lst->end(); ++it){
        it->draw_turret(window);
    }
}

void fire_turrets(std::list <Turret> *turret_lst, std::list <Projectile> *projectile_lst) {
    for (std::list<Turret>::iterator it = turret_lst->begin(); it != turret_lst->end(); ++it){
        it->fire(projectile_lst);
    }
}

void draw_turret_fire_radius_outline(std::list <Turret> *turret_lst, sf::RenderWindow *window) {
    for (std::list<Turret>::iterator it = turret_lst->begin(); it != turret_lst->end(); ++it){
        it->draw_fire_radius(window);
    }
}
