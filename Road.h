#ifndef ROAD_H
#define ROAD_H

#pragma once

#include <SFML/Graphics.hpp>
// #include <unistd.h>
#include <iostream>

class Road
{
public:
    Road(sf::RenderWindow& window, std::vector<sf::Vector2f>& p);

    void draw();                        // Рисуем дорогу
    sf::Vector2f move(int delta);       // Перемещение по дороге и возвращает текущую координату объекта на дороге
    float getAngle();                   // угол текущего участки дороги относительно оси Х (0, +90, -90, +180)
    void setWidth(int w);
    void update(std::vector<sf::Vector2f>& p);
private:
    std::vector<sf::Vector2f>& points;  // ссылка массив узлов дороги
    sf::Vector2f pos;                   // текущая координата объекта на дороге
    float angle;                        // угол текущего участки дороги относительно оси Х (0, +90, -90, +180)
    int curr_section;                   // порядковый номер текущего участка дороги (в массиве узлов дороги)
    int max_point;                      // количество узлов дороги
    int width;                          // ширина дороги в пикселях
    sf::RectangleShape rect;            // прямоугольник для рисования участков дороги
    sf::Texture texture_road;           // тестура дороги
    sf::RenderWindow& win;              // Ссылка на графическое окно
    void updateAngle();                // угол текущего участки дороги относительно оси Х (0, +90, -90, +180)
};

#endif