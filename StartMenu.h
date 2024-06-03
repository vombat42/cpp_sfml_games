#ifndef STARTMENU_H
#define STARTMENU_H

#pragma once

#include <SFML/Graphics.hpp>


class StartMenu
{
public:
    StartMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name);
    ~StartMenu();

    void draw();                                     // Рисуем меню
    void MoveUp();                                   // Перемещение выбора меню вверх
    void MoveDown();                                 // Перемещение выбора меню вниз

    // Цвет элементов игрового меню
    void setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor);

    // void AlignMenu(int posx);       // Выравнивание положения меню (по левому по правому по центру)

    int getSelectedMenuNumber() const     // Возвращает номер выбраного элемента
    {
        return selected_item;
    }
private:
    float x;                                        // Координаты меню по X
    float y;                                        // Координаты меню по Y
    int step;                                       // Расстояние между пунктами меню
    int max_item;                                   // Максимальное количество пунктов меню
    int size_font;                                  // Размер шрифта
    int selected_item;                              // Номер текущего пункта меню 
    sf::Font font;                                  // Шрифт меню 
    std::vector<sf::Text> item_list;                // Динамический массив названий меню

    sf::Color menu_text_color = sf::Color::White;   // Цвет меню
    sf::Color chose_text_color = sf::Color::Yellow; // Цвет выбора меню
    sf::Color border_color = sf::Color::Black;      // Цвет обводки текста

    // Настройка текста меню
    void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

    sf::RenderWindow& mywindow;                     // Ссылка на графическое окно
};

#endif