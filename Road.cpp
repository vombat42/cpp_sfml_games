#include "Road.h"


Road::Road(sf::RenderWindow &window, std::vector<sf::Vector2f> &p)
            :win(window), points(p), max_point(p.size()), curr_section(1), pos(p[0]), rect{}, width(20), texture_road{}
{
    // rect.setFillColor(sf::Color::Green);
    // rect.setOutlineThickness(3);
    // rect.setOutlineColor(sf::Color::Green);
    if (!texture_road.loadFromFile("img/road_2.jpg")) exit(2);
    texture_road.setRepeated(true);
    rect.setTexture(&texture_road);
    updateAngle();
}

void Road::draw()
{
    sf::Vector2f temp;
    for (int i = 0; i < this->max_point - 1; i++) {
        temp = this->points[i+1] - this->points[i];
        temp += sf::Vector2f(this->width, this->width);
        this->rect.setSize(temp);
        this->rect.setPosition(this->points[i] - sf::Vector2f(this->width / 2, this->width / 2));
        rect.setTextureRect(sf::IntRect(0,0, temp.x, temp.y));
        this->win.draw(this->rect);
        // std::cout << a << " temp " << temp.x << ":" << temp.y << " pos(" << this->rect.getPosition().x << ":" << this->rect.getPosition().y << ") rot(";
        // std::cout << this->rect.getRotation() << ") size("  << this->rect.getSize().x << ":" << this->rect.getSize().y << ")"<< std::endl;
    }
}

sf::Vector2f Road::move(int delta)
{
    if (this->angle == 0) {
        this->pos.x += delta;
        if (this->pos.x > this->points[this->curr_section].x) {
            // this->pos.x = this->points[this->curr_section].x;
            if (this->curr_section < max_point - 1) {this->pos.x = this->points[this->curr_section].x; this->curr_section++;}
            // this->curr_section++;
            updateAngle();
        }
        return this->pos;
    }
    if (this->angle == 180) {
        this->pos.x -= delta;
        if (this->pos.x <= this->points[this->curr_section].x) {
            this->pos.x = this->points[this->curr_section].x;
            this->curr_section++;
            updateAngle();
        }
        return this->pos;
    }
    if (this->angle == 90) {
        this->pos.y += delta;
        if (this->pos.y >= this->points[this->curr_section].y) {
            this->pos.y = this->points[this->curr_section].y;
            this->curr_section++;
            updateAngle();
        }
        return this->pos;
    }
    if (this->angle == -90) {
        this->pos.y -= delta;
        if (this->pos.y <= this->points[this->curr_section].y) {
            this->pos.y = this->points[this->curr_section].y;
            this->curr_section++;
            updateAngle();
        }
        return this->pos;
    }
    return sf::Vector2f{};
}

float Road::getAngle()
{
    return this->angle;
}

void Road::setWidth(int w)
{
    this->width = w;
}

void Road::update(std::vector<sf::Vector2f> &p)
{
    this->points = p;
    this->max_point = p.size();
    this->curr_section = 1;
    this->pos = p[0];
    updateAngle();
}

void Road::updateAngle()
{
    sf::Vector2f temp;
    temp = this->points[curr_section] - this->points[curr_section-1];
    if (temp.x > 0.1) { this->angle = 0; return; }
    if (temp.x < -0.1) { this->angle = 180; return; }
    if (temp.y > 0.1) { this->angle = 90; return; }
    if (temp.y < -0.1) { this->angle = -90; return; }
}
