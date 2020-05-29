//
//  enemy_path.cpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 4/22/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "path.hpp"

Path::Path() {
    length = 0;
}

void Path::move_enemy(Enemy *e) {

    if (e->index != -1) { // enemy is alread on path, so there is a previous
        PathBlock *prev_path_block = &path_lst[e->index];
        prev_path_block->remove_enemy(e);
    }
    
    if (e->is_dead()) { // dont move to next segment because enemy is dead
        return;
    }
    
    e->index += e->speed;
    if (e->index >= length) { // got to the end of the path
        e->index = 0; // wrap back around for now
    }
    
    PathBlock *next_path_block = &path_lst[e->index];
    next_path_block->add_enemy(e);
}

void move_enemies(std::list <Enemy> *enemy_lst, Path *path) {
    std::list<Enemy>::iterator it = enemy_lst->begin();
    while (it != enemy_lst->end()) {
        Enemy *enemy_ptr = &(*it);
        
        // if dead, remove from enemy_lst
        if (enemy_ptr->is_dead()) {
            enemy_lst->erase(it++);
        } else {
            it++;
        }
        path->move_enemy(enemy_ptr);

    }
}

void Path::add_to_path(int x, int y) {
    PathBlock path_block(x,y);
    path_lst.push_back(path_block);
    length++;
}

std::list <PathBlock*> Path::get_blocks(int x, int y, int radius) {
    std::list <PathBlock*> returned;
    for (int i = 0; i < length; i++) {
        PathBlock *path_block = &path_lst[i];
        if (radius + ENEMY_RADIUS >= path_block->distance(x, y)) {
            returned.push_back(path_block);
        }
    }
    return returned;
}

void Path::draw_path_blocks(sf::RenderWindow *window) {
    for (int i = 0; i < length; i++) {
        PathBlock *path_block = &path_lst[i];
        path_block->draw_path_block(window);
    }
}
