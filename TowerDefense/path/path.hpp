//
//  path.h
//  PhysicsEngine
//
//  Created by Benjamin Ulrich on 4/22/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#ifndef path_hpp
#define path_hpp

#endif /* path_hpp */

#include <vector>
#include <list>
#include "path_block.hpp"

class Path {
    
    int length;
    std::vector <PathBlock> path_lst;
    
public:
    
    Path();
    void add_to_path(int x, int y);
    void move_enemy(Enemy *e);
    std::list <PathBlock*> get_blocks(int x, int y, int radius);
    void draw_path_blocks(sf::RenderWindow *window);
};

void move_enemies(std::list <Enemy> *enemy_lst, Path *path);
