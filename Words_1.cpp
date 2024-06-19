#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unistd.h>


#include "Word.h"

using namespace sf;


int Words_1() {

    const int item_size = 200;
    const int speed = 2;
    const int road_w = 100;
    srand(time(NULL));
    int win_w, win_h;

    RenderWindow win;
    win.create(VideoMode::getDesktopMode(), L"Слова 1", Style::Fullscreen);
    win.setMouseCursorVisible(false); //отключаем видимость курсора
    win.setPosition(Vector2i(0, 0));
    // Размер экрана
    win_w = static_cast<int>(VideoMode::getDesktopMode().width);
    win_h = static_cast<int>(VideoMode::getDesktopMode().height);

    RectangleShape background(Vector2f(win_w, win_h));
    Texture texture_wood;
    background.setTextureRect(IntRect(0,0, win_w, win_h));
    if (!texture_wood.loadFromFile("img/wood_1.jpg")) exit(2);
    texture_wood.setRepeated(true);
    background.setTexture(&texture_wood);


    // Звездочка молодец
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

    // звук молодец
    SoundBuffer umnitsa; 
    umnitsa.loadFromFile("audio/umnitsa.ogg");
    Sound soundGood;
    soundGood.setBuffer(umnitsa);

    // Слово
    const String word = L"хеелебел";
    std::string const audio_file = "audio/good.ogg";
    std::string const texture_file = "img/хлеб.png";
    Word slovo(win, 900, 300, 50, word, audio_file, texture_file);


    Clock clock;
    float time, timeCar;

    bool is_goal {false};

    while (win.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timeCar = time / 6000 * speed;
        clock.restart();

        while (win.pollEvent(event))
        {
            if(event.type == Event::Closed){
                win.close();
            }
            // Управление
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == slovo.getKeyLetter()) {
                    slovo.play();
                    if (!slovo.nextLetter()) is_goal = true;
                }
                if (event.key.code == Keyboard::Escape) {
                    win.close();
                }
                break;
            case Event::KeyReleased:
                // if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right || event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) {
                //     distance = 0;
                //     soundMotor.pause();
                // }
                break;
            default:
                break;
            }
        }

        win.clear();

        if (is_goal) {
            win.draw(background);
            // win.draw(wordGood);
            win.draw(signGood);
            win.draw(slovo.getGoalSprite());
            soundGood.play();
        }
        else {
            win.draw(background);
            slovo.draw();
        }

        win.display();

        if (is_goal) {
            sleep(3);
            is_goal = false;
            slovo.restart();
        }
    }

    return 0;
}