#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unistd.h>

#include "Word.h"


using namespace sf;


int Words_1() {
    RenderWindow win;
    win.create(VideoMode::getDesktopMode(), L"Слова 1", Style::Fullscreen);
    win.setMouseCursorVisible(false); //отключаем видимость курсора
    win.setPosition(Vector2i(0, 0));
    // Размер экрана
    int win_w = static_cast<int>(VideoMode::getDesktopMode().width);
    int win_h = static_cast<int>(VideoMode::getDesktopMode().height);

    // фон
    RectangleShape background(Vector2f(win_w, win_h));
    Texture texture_wood;
    background.setTextureRect(IntRect(0,0, win_w, win_h));
    if (!texture_wood.loadFromFile("img/wood_1.jpg")) exit(2);
    texture_wood.setRepeated(true);
    background.setTexture(&texture_wood);


// вспомогательная линия
sf::Vertex line[] =
{
    sf::Vertex(sf::Vector2f(win_w/2, 0)),
    sf::Vertex(sf::Vector2f(win_w/2, win_h))
};

    // Спрайт молодец
    Texture TextureGood;
    TextureGood.loadFromFile("img/word_good.png");
    Sprite wordGood;
    wordGood.setPosition((win_w - 694) / 2, (win_h - 714) / 2 + 50);
    wordGood.setTexture(TextureGood);
    
    // надпись умница
    Texture TextureSignGood;
    TextureSignGood.loadFromFile("img/umnitsa.png");
    Sprite signGood;
    signGood.setPosition((win_w - 737) / 2, 50);
    signGood.setTexture(TextureSignGood);

    // звук умница
    SoundBuffer umnitsa; 
    umnitsa.loadFromFile("audio/umnitsa.ogg");
    Sound soundGood;
    soundGood.setBuffer(umnitsa);

    // звук "напиши слово"
    SoundBuffer write_word_buff; 
    write_word_buff.loadFromFile("audio/напиши_слово.ogg");
    Sound sound_write_word;
    sound_write_word.setBuffer(write_word_buff);

    // звук "давай продолжим"
    SoundBuffer lets_continue_buff; 
    lets_continue_buff.loadFromFile("audio/давай_продолжим.ogg");
    Sound sound_lets_continue;
    sound_lets_continue.setBuffer(lets_continue_buff);

    // Слова
    std::vector<Word*> word_list;                    // Динамический массив слов
    int num = 0;
    // Word* d = new Word(win, win_w / 2, 150, 150, word, audio_file, texture_file);
    word_list.push_back(new Word(win, win_w / 2, 150, 150, L"ДОМ", "audio/дом.ogg", "img/дом.png"));
    word_list.push_back(new Word(win, win_w / 2, 150, 150, L"ВОДА", "audio/вода.ogg", "img/вода.png"));
    word_list.push_back(new Word(win, win_w / 2, 150, 150, L"ЛИМОН", "audio/лимон.ogg", "img/лимон.png"));
    word_list.push_back(new Word(win, win_w / 2, 150, 150, L"СТУЛ", "audio/стул.ogg", "img/стул.png"));
    word_list.push_back(new Word(win, win_w / 2, 150, 150, L"ХЛЕБ", "audio/хлеб.ogg", "img/хлеб.png"));
    // word_list.push_back(new Word(win, win_w / 2, 150, 150, L"КОЛБАСА", "audio/колбаса.ogg", "img/колбаса.png"));

    int num_max = word_list.size();
    // std::cout << "kol-vo = " << num_max << std::endl;

    bool is_goal {false};
    bool is_start {true};
    bool is_event {true};

   
    while (win.isOpen())
    {
        Event event;

        while (win.pollEvent(event))
        {
            if(event.type == Event::Closed){
                win.close();
            }
            // Управление
            switch (event.type)
            {
            case Event::KeyPressed:
                if (!is_event) {
                    if (event.key.code == word_list[num]->getKeyLetter()) {
                        if (!word_list[num]->nextLetter()) is_goal = true;
                        is_event = true;
                    }
                }
                if (event.key.code == Keyboard::Escape) {
                    win.close();
                }
                break;
            default:
                break;
            }
        }

        if (is_event) {
            is_event = false;
            win.clear();

            if (is_goal) {
                win.draw(background);
                word_list[num]->draw_whole();
                win.draw(word_list[num]->getGoalSprite());
                
                win.display();
                
                word_list[num]->play(); // звучание всего слова

            }
            else {
                if (is_start) {
                    win.draw(background);
                    word_list[num]->draw_whole();
                    win.display();
                    sound_write_word.play();
                    while (sound_write_word.getStatus() == Sound::Playing) {
                        sleep(milliseconds(500));
                    }
                    word_list[num]->play();
                    sleep(milliseconds(1000));
                    
                    win.clear();
                    win.draw(background);
                    word_list[num]->draw();
                    win.display();
                    word_list[num]->play_letter(); // звучание текущей (первой) буквы в слове
                    is_start = false;
                }
                else {
                    win.draw(background);
                    word_list[num]->draw();
                    win.display();
                    word_list[num]->play_letter(); // звучание текущей буквы в слове
                }
            }

            // win.display();

            if (is_goal) {
                sleep(4);
                is_goal = false;
                is_start = true;
                is_event = true;
                if (++num >= num_max) {
                    win.clear();
                    win.draw(background);
                    win.draw(wordGood);
                    win.draw(signGood);
                    win.display();
                    soundGood.play();
                    sleep(3);
                    win.close();
                }
                else {
                    sound_lets_continue.play();
                    while (sound_lets_continue.getStatus() == Sound::Playing) {
                        sleep(milliseconds(500));
                    }
                }
            }

        }
    }

    return 0;
}