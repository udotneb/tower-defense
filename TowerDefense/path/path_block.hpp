//
//  path_block.hpp
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 5/19/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef path_block_hpp
#define path_block_hpp

#include <stdio.h>
#include "enemy.hpp"

#endif /* path_block_hpp */
#include <list>

class PathBlock {
    int x;
    int y;
    sf::CircleShape circle;

public:

    std::list <Enemy*> enemies_here;
    
    PathBlock(int x_, int y_);
    float distance(int x_, int y_);
    void add_enemy(Enemy *e);
    void remove_enemy(Enemy *e);
    void draw_path_block(sf::RenderWindow *window);
};

