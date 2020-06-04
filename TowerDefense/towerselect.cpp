//
//  towerselect.cpp
//  TowerDefense
//
//  Created by Benjamin Ulrich on 5/29/20.
//  Copyright © 2020 Benjamin Ulrich. All rights reserved.
//

#include "towerselect.hpp"
#include <iostream>

const float tower_select_height= 50.f;
const float tower_select_width = 150.f;
const float tower_individual_width = 50.f;


const int number_turrets = 3;

const sf::Color panel_color = sf::Color(168, 166, 50, 100);
const sf::Color color_arr[] = {sf::Color::White, sf::Color::Blue, sf::Color::Red};

TowerSelect::TowerSelect() {
    sf::RectangleShape rectangle_(sf::Vector2f(tower_select_width, tower_select_height));
    underlying_rect = rectangle_;
    underlying_rect.setFillColor(sf::Color::Black);
    underlying_rect.setPosition(0,0);
    underlying_rect.setSize(sf::Vector2f(tower_select_width, tower_select_height));
    
    for (int i = 0; i < number_turrets; i++) {
        rect_lst.push_back(get_rect(i));
        circ_lst.push_back(get_circ(i));
    }
}

sf::RectangleShape TowerSelect::get_rect(int index) {
    // returns an individual tower rect for panel
    sf::RectangleShape rect(sf::Vector2f(tower_individual_width, tower_select_height));
    rect.setPosition(index * tower_individual_width, 0);
    rect.setFillColor(panel_color);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.f);
    return rect;
}

sf::CircleShape TowerSelect::get_circ(int index) {
    // returns a tower circle for panel
    sf::CircleShape circ(10.f);
    circ.setFillColor(color_arr[index]);
    circ.setOrigin(circ.getRadius(), circ.getRadius());
    circ.setPosition((2 * index + 1) * (tower_individual_width / 2), tower_select_height / 2);
    return circ;
}

void TowerSelect::draw_tower_select(sf::RenderWindow *window) {
    // draws the panel and the towers
    window->draw(underlying_rect);
    
    for (std::list<sf::RectangleShape>::iterator it = rect_lst.begin(); it != rect_lst.end(); ++it){
        window->draw(*it);
    }
    
    for (std::list<sf::CircleShape>::iterator it = circ_lst.begin(); it != circ_lst.end(); ++it){
        window->draw(*it);
    }
}

bool TowerSelect::panel_pressed(sf::RenderWindow *window, sf::Vector2i mouse_position) {
    // returns whether anywhere on the panel was pressed
    return underlying_rect.getGlobalBounds().contains(window->mapPixelToCoords(mouse_position));
}

int TowerSelect::index_pressed_tower(sf::RenderWindow *window, sf::Vector2i mouse_position) {
    // Returns the index of the tower that was pressed
    int index = 0;
    for (std::list<sf::RectangleShape>::iterator it = rect_lst.begin(); it != rect_lst.end(); ++it){
        if (it->getGlobalBounds().contains(window->mapPixelToCoords(mouse_position))) {
            return index;
        }
        index++;
    }
    return index - 1;
}


