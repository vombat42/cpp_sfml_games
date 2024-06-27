#ifndef WORD_H
#define WORD_H

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unistd.h>


class Word
{
public:
    Word(sf::RenderWindow& window, float centerX, float centerY, int fSize, const sf::String& word, std::string const& audioF, std::string const& textureF);
    ~Word();

    void draw();                                     // Пишем слово
    void draw_whole();                               // Пишем слово целиком
    void play();                                     // Произнести слово
    void play_letter();                              // Произнести текущую букву
    bool nextLetter();                               // Перемещение на следующую букву, true - если не конец слова, false - если конец слова
    bool animate_letter(float delta);
    sf::Sprite getGoalSprite(); // спрайт слова (изображение)
    sf::Keyboard::Key getKeyLetter();               // Возвращает код клавиши для текущей буквы

private:
    // структура свойств букв алфавита
    struct letter
    {
        int key;
        std::string sound_file;
    };
    // словарь свойств букв алфавита
    std::map<unsigned int, letter> letter_code {
        {1040, {5,  "а.ogg"}}, // А
        {1041, {49, "б.ogg"}}, // Б
        {1042, {3,  "в.ogg"}}, // В
        {1044, {11, "д.ogg"}}, // Д
        {1045, {19, "е.ogg"}}, // Е
        {1048, {1,  "и.ogg"}}, // И
        {1050, {17, "к.ogg"}}, // К
        {1051, {10, "л.ogg"}}, // Л
        {1052, {21, "м.ogg"}}, // М
        {1053, {24, "н.ogg"}}, // Н
        {1054, {9,  "о.ogg"}}, // О
        {1055, {6,  "п.ogg"}}, // П
        {1057, {2,  "с.ogg"}}, // С
        {1058, {13, "т.ogg"}}, // Т
        {1059, {4,  "у.ogg"}}, // У
        {1061, {46, "х.ogg"}}, // Х

    };
    
    float x;                                              // Координаты центра слова по X
    float y;                                              // Координаты центра слова по Y
    int len;                                              // длина слова (количество букв)
    int size_font;                                        // Размер шрифта
    int current_letter_num;                               // Номер текущей буквы в слове 
    sf::Font font;                                        // Шрифт букв 
    std::vector<sf::Text> letter_list;                    // Динамический массив букв
    sf::Text current_letter;                              // Текущая буква (крупная)
    sf::Vector2f current_letter_pos;                      // Позиция текущей бувы (крупной)
    sf::Text whole_word;                                  // Слово целиком (для отображения после написания слова)
    sf::SoundBuffer zvuk_buffer;                          // звук слова (буффер)
    sf::Sound zvuk;                                       // звук слова
    sf::SoundBuffer letter_zvuk_buffer;                   // звук буквы (буффер)
    sf::Sound letter_zvuk;                                // звук буквы 
    sf::Texture texture;                                  // изображение слова (текстура)
    sf::Sprite sprite;                                    // изображение слова
    sf::Color letter_color= sf::Color::Green;             // Цвет букв
    sf::Color current_letter_color = sf::Color::Yellow;   // Цвет текущей буквы
    sf::RenderWindow& win;                                // Ссылка на графическое окно
    float time_anim = 1500;                               // длительность анимации буквы

    // Настройка отображения букв (позиция, цвет, размер)
    void setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

};

#endif