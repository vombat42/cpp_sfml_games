#ifndef TARGET_H
#define TARGET_H

#pragma once

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
#include <math.h>


#include "AssetManager.h"
#include "Animator.h"

using namespace sf;

class Target
{
public:
    Sprite target;

    Target(int size, int weight, int height, std::string const& name_texture,  std::string const& file_texture, int x, int y, int dx, int dy);  // конструктор объекта
    ~Target();

    void Update(Time const& dt) {
        animator.Update(dt);
    };

    bool getStatus() {return this->is_active ;}

    void setStatus(bool status) {
        this->is_active = status;
    }

    Vector2i getGoalPosition() {
        return this->goal_pos;
    }

    void setPosition(Vector2i p) {
        this->pos.x = p.x;
        this->pos.y = p.y;
        this->goal_pos.x = p.x + static_cast<float>(this->delta.x) * this->koef;
        this->goal_pos.y = p.y + static_cast<float>(this->delta.y) * this->koef;
        target.setPosition(this->pos.x, this->pos.y);
    }

    bool is_target(Vector2f p) {
        if ((abs(this->goal_pos.x - p.x) < this->w / 4) && (p.y - this->goal_pos.y) < this->h / 6 && p.y > this->goal_pos.y) {
            return true;
        }
        return false;
    }


private:
    Vector2i pos; // позиция в окне
    Vector2i goal_pos; // целевая точка
    Vector2i delta; // позиция целевой точки относительно позиции
    bool is_active; // статус цели
    int h, w; // размеры
    Animator animator;
    float koef; // множитель размера

};

#endif