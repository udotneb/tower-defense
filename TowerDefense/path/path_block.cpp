//
//  path_block.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/19/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "path_block.hpp"
#include <cmath>
#include <iostream>

PathBlock::PathBlock(int x_, int y_) {
    x = x_;
    y = y_;
    
    
    sf::CircleShape circle_(50.f);
    circle = circle_;
    
    circle.setFillColor(sf::Color(0, 0, 0));
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(x, y);
}

float PathBlock::distance(int x_, int y_) {
    return pow(pow(abs(x_ - x), 2) + pow(abs(y_ - y), 2), 0.5);
}

void PathBlock::add_enemy(Enemy *e) {
    // changes the enemy x and y values, adds the enemy to enemies_here
    e->x = x;
    e->y = y;
    
    enemies_here.push_back(e);
}

void PathBlock::remove_enemy(Enemy *e) {
    enemies_here.remove(e);
}

void PathBlock::draw_path_block(sf::RenderWindow *window) {
    window->draw(circle);
}

