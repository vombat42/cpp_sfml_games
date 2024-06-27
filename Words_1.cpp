#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unistd.h>

#include "Word.h"


using namespace sf;


enum status {
    start_word,
    letter_run,
    wait_press,
    letter_pressed,
    letter_done,
    done_word,
    finish,
};

struct word_data {
    String const word;
    std::string const audioF;
    std::string const textureF;
};

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

    // звук "нажми букву"
    SoundBuffer press_letter_buff; 
    press_letter_buff.loadFromFile("audio/нажми_букву.ogg");
    Sound sound_press_letter;
    sound_press_letter.setBuffer(press_letter_buff);

    // звук верного нажатия
    SoundBuffer good_press_buff; 
    good_press_buff.loadFromFile("audio/good_press.ogg");
    Sound sound_good_press;
    sound_good_press.setBuffer(good_press_buff);

    // звук ошибочного нажатия
    SoundBuffer bad_press_buff; 
    bad_press_buff.loadFromFile("audio/bad_press.ogg");
    Sound sound_bad_press;
    sound_bad_press.setBuffer(bad_press_buff);

    // Слова
    std::vector<word_data> words;                    // Динамический массив слов
    int num = 0;
    words.push_back({L"МАМА",  "audio/мама.ogg",   "img/мама.png"});
    words.push_back({L"ДОМ",   "audio/дом.ogg",    "img/дом.png"});
    words.push_back({L"ВОДА",  "audio/вода.ogg",   "img/вода.png"});
    words.push_back({L"ХЛЕБ",  "audio/хлеб.ogg",   "img/хлеб.png"});
    words.push_back({L"ПАПА",  "audio/папа.ogg",   "img/папа.png"});
    words.push_back({L"СТУЛ",  "audio/стул.ogg",   "img/стул.png"});
    words.push_back({L"ЛИМОН", "audio/лимон.ogg",  "img/лимон.png"});
    // words.push_back({L"КОЛБАСА", "audio/колбаса.ogg", "img/колбаса.png"});
    Word* word = new Word(win);
    word->setParams(win_w / 2, 150, 150, words[num].word, words[num].audioF, words[num].textureF);

    int num_max = words.size();

    Clock clock;
    float time {0}; // miliseconds

    int current_status {start_word};

    // Основной цикл событий
    while (win.isOpen())
    {
        Event event_words;
        while (win.pollEvent(event_words)){} // цикл опроса событий для служебных нужд окна
        switch (current_status)
        {
        case start_word: // -----------------------------------------
            win.clear();
            win.draw(background);
            word->draw_whole();
            win.display();
            sound_write_word.play();
            while (sound_write_word.getStatus() == Sound::Playing) {
                sleep(milliseconds(500));
            }
            word->play();
            sleep(milliseconds(1000));
            
            current_status = letter_run;
            break;
        case wait_press: // -----------------------------------------
            if (win.waitEvent(event_words)) {
                if(event_words.type == Event::Closed){
                    win.close();
                }
                switch (event_words.type)
                {
                case Event::KeyPressed:
                    if (event_words.key.code == Keyboard::Escape) {
                        win.close();
                    }
                    if (event_words.key.code == word->getKeyLetter()) {
                        current_status = letter_pressed;
                        clock.restart();
                    }
                    else
                    {
                        sound_bad_press.play();
                    }
                    break;
                }
            }
            break;
        case letter_pressed: // -----------------------------------------
            sound_good_press.play();
            while (word->animate_letter(time)) {
                time = clock.getElapsedTime().asMilliseconds();
                win.clear();
                win.draw(background);
                word->draw();
                win.display();
                sleep(milliseconds(5));
            }
            time = 0;
            current_status = letter_done;
            break;
        case letter_done: // -----------------------------------------
            if (!word->nextLetter()) {
                current_status = done_word;
            }
            else {
                current_status = letter_run;
            }
            break;
        case letter_run: // -----------------------------------------
            win.clear();
            win.draw(background);
            word->draw();
            win.display();

            sound_press_letter.play();
            while (sound_press_letter.getStatus() == sf::Sound::Playing) {
                sf::sleep(sf::milliseconds(100));
            }

            word->play_letter(); // звучание текущей буквы в слове
            current_status = wait_press;
            break;
        case done_word: // -----------------------------------------
            win.clear();
            win.draw(background);
            word->draw_whole();
            win.draw(word->getGoalSprite());
            
            win.display();
            sleep(seconds(1));
            word->play(); // звучание всего слова

            sleep(seconds(3));

            if (++num >= num_max) {
                current_status = finish;
            }
            else {
                sound_lets_continue.play();
                while (sound_lets_continue.getStatus() == Sound::Playing) {
                    sleep(milliseconds(500));
                }
                word->setParams(win_w / 2, 150, 150, words[num].word, words[num].audioF, words[num].textureF);
                current_status = start_word;
            }
            break;
        case finish: // -----------------------------------------
            win.clear();
            win.draw(background);
            win.draw(wordGood);
            win.draw(signGood);
            win.display();
            soundGood.play();
            sleep(seconds(3));
            win.close();
            break;         
        default: // -----------------------------------------
            break;
        }
    }

    return 0;
}