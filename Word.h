#ifndef WORD_H
#define WORD_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Word
{
public:
    Word(sf::RenderWindow& window, float centerX, float centerY, int fSize, const sf::String& word, std::string const& audioF, std::string const& textureF);
    ~Word();

    void draw();                                     // Пишем слово
    void play();                                     // Произнести слово
    bool nextLetter();                               // Перемещение на следующую букву, true - если не конец слова, false - если конец слова
    void restart();
    sf::Sprite getGoalSprite();

    // Цвет букв слова
    // void setLettersColor(sf::Color LCol, sf::Color CLCol);

    sf::Keyboard::Key getKeyLetter();    // Возвращает код клавиши для текущей буквы

private:
    float x;                                        // Координаты центра слова по X
    float y;                                        // Координаты центра слова по Y
    int len;                                   // длина слова (количество букв)
    int size_font;                                  // Размер шрифта
    int current_letter;                              // Номер текущей буквы в слове 
    sf::Font font;                                  // Шрифт букв 
    std::vector<sf::Text> letter_list;                // Динамический массив букв
    sf::SoundBuffer zvuk_buffer;
    sf::Sound zvuk;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Color letter_color= sf::Color::Green;            // Цвет букв
    sf::Color current_letter_color = sf::Color::Yellow;   // Цвет текущей буквы
    std::wstring stroka;

    // Настройка букв
    void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

    sf::RenderWindow& win;                     // Ссылка на графическое окно

    std::map<unsigned int, int> letter_code {
        {1093, 46}, // х
        {1083, 10}, // л
        {1077, 19}, // е
        {1073, 49}, // б
    };
};

#endif