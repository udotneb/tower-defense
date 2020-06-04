//
//  ball.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 3/29/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "enemy.hpp"
#include "list"

Enemy::Enemy() {
    sf::CircleShape circle_(ENEMY_RADIUS);
    circle = circle_;
    index = -1;
    speed = 1;
    health = 100;
    
    circle.setFillColor(sf::Color(health, 250, 50));
    circle.setOrigin(circle.getRadius(), circle.getRadius());

}

bool Enemy::is_dead() {
    return health <= 0;
}

void Enemy::draw_enemy(sf::RenderWindow *window) {
    circle.setFillColor(sf::Color(health, 250, 50));

    circle.setPosition(x, y);
    window->draw(circle);
}

void draw_enemies(std::list <Enemy> *enemy_lst, sf::RenderWindow *window) {
    for (std::list<Enemy>::iterator it = enemy_lst->begin(); it != enemy_lst->end(); ++it){
        it->draw_enemy(window);
    }
}

