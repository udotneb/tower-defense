//
//  turret.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/21/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "turret.hpp"
#include <iostream>


const float fire_radius_arr[] = {100, 300, 500};
const int rate_of_fire_arr[] = {50, 10, 100}; // inverse of the fire rate 
const int damage_arr[] = {20, 10, 100};
const sf::Color turret_color_arr[] = {sf::Color::White, sf::Color::Blue, sf::Color::Red};

Turret::Turret(float x_, float y_, int turret_index, Path *path_) {
    x = x_;
    y = y_;
    
    fire_radius = fire_radius_arr[turret_index];
    rate_of_fire = rate_of_fire_arr[turret_index];
    damage = damage_arr[turret_index];
    
    path = path_;
    path_blocks = path->get_blocks(x, y, fire_radius);
    current_fire_count = 0;
    
    std::cout << path_blocks.size();
    std::cout << " number of path blocks in turret range \n";
    
    sf::CircleShape turret_drawable_(10.f);
    turret_drawable = turret_drawable_;
    turret_drawable.setOrigin(turret_drawable.getRadius(), turret_drawable.getRadius());
    turret_drawable.setFillColor(turret_color_arr[turret_index]);
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

void Turret::draw_fire_radius(sf::RenderWindow *window, sf::Vector2i mouse_position) {
    if (turret_drawable.getGlobalBounds().contains(window->mapPixelToCoords(mouse_position))) {
        window->draw(fire_radius_drawable);
    }
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

void draw_turret_fire_radius_outline(std::list <Turret> *turret_lst, sf::RenderWindow *window, sf::Vector2i mouse_position) {
    for (std::list<Turret>::iterator it = turret_lst->begin(); it != turret_lst->end(); ++it){
        it->draw_fire_radius(window, mouse_position);
    }
}

void draw_mouse_turret(sf::RenderWindow *window, float x, float y, int turret_index) {
    sf::CircleShape turret_drawable(10.f);
    turret_drawable.setOrigin(turret_drawable.getRadius(), turret_drawable.getRadius());
    turret_drawable.setFillColor(turret_color_arr[turret_index]);
    turret_drawable.setPosition(x, y);
    
    window->draw(turret_drawable);
    
    sf::CircleShape fire_radius_drawable(fire_radius_arr[turret_index]);
    fire_radius_drawable.setOrigin(fire_radius_drawable.getRadius(), fire_radius_drawable.getRadius());
    fire_radius_drawable.setFillColor(sf::Color(250, 250, 250, 0)); // make the fill 0 opacity
    fire_radius_drawable.setOutlineThickness(5.f);
    fire_radius_drawable.setOutlineColor(sf::Color(250, 150, 100));
    fire_radius_drawable.setPosition(x, y);
    
    window->draw(fire_radius_drawable);
}
