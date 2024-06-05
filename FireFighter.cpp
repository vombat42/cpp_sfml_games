#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>


#include "AssetManager.h"
#include "Animator.h"
#include "Target.h"

using namespace sf;

int FireFighter() {
    srand(time(NULL));
    int win_w, win_h;
    const int item_size = 140;
    const int speed = 2;

    RenderWindow win;
    win.create(VideoMode::getDesktopMode(), L"Наведи на цель", Style::Fullscreen);
    win.setMouseCursorVisible(false); //отключаем видимость курсора
    win.setPosition(sf::Vector2i(0, 0));
    // Размер экрана
    win_w = static_cast<int>(VideoMode::getDesktopMode().width);
    win_h = static_cast<int>(VideoMode::getDesktopMode().height);

    Image icon;
    if (!icon.loadFromFile("img/icon.png")) { return 1; }
    win.setIcon(32, 32, icon.getPixelsPtr());

    // Звездочка молодец
    Texture TextureStarGood;
    TextureStarGood.loadFromFile("img/star_good.png");
    Sprite starGood;
    starGood.setPosition((win_w - 618) / 2, (win_h - 548) / 2 + 50);
    starGood.setTexture(TextureStarGood);
    
    // надпись умница
    Texture TextureSignGood;
    TextureSignGood.loadFromFile("img/umnitsa.png");
    Sprite signGood;
    signGood.setPosition((win_w - 737) / 2, 50);
    signGood.setTexture(TextureSignGood);

    // звук молодец
    SoundBuffer bufferGood; 
    bufferGood.loadFromFile("audio/good.ogg");
    Sound soundGood;
    soundGood.setBuffer(bufferGood);

    // звук тушения
    SoundBuffer bufferPshh; 
    bufferPshh.loadFromFile("audio/pshhh.ogg");
    Sound soundPshhh;
    soundPshhh.setBuffer(bufferPshh);


    Vector2f moveRec, pos;

    // Указатель
    int bailer_w = 385;
    int bailer_h = 380;
    Texture TexturePointer;
    TexturePointer.loadFromFile("img/bailer.png");
    Sprite pointer;
    pointer.setPosition((win_w - item_size)/ 2, (win_h - item_size)/ 2);
    pointer.setTexture(TexturePointer);
    float koef =  (static_cast<float>(item_size) / static_cast<float>(bailer_h));
    pointer.setScale(koef, koef);
    float p_dx = static_cast<float>(bailer_w) / 5 * koef;
    float p_dy = static_cast<float>(bailer_h) * koef;

    // Цели
    int num = 5;
    int flame_w = 180;
    int flame_h = 200;
    Target* goals[num];
    for (int i = 0; i < num; ++i) {
        goals[i] = new Target(item_size, flame_w, flame_h, "flame", "img/flame.png", rand() % (win_w - item_size * 2) + item_size, rand() % (win_h - item_size * 2) + item_size, 90, 130);
    } 


    Clock clock;
    float time, timePointer;

    bool is_goal {false};

    while (win.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timePointer = time / 6000 * speed;

        while (win.pollEvent(event))
        {
            if(event.type == Event::Closed){
                win.close();
            }
            // Управление
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Left) {
                    moveRec.x = -timePointer;
                }
                if (event.key.code == Keyboard::Right) {
                    moveRec.x = timePointer;
                }
                if (event.key.code == Keyboard::Up) {
                    moveRec.y = -timePointer;
                }
                if (event.key.code == Keyboard::Down) {
                    moveRec.y = timePointer;
                }
                if (event.key.code == Keyboard::Escape) {
                    win.close();
                }
                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right) {
                    moveRec.x = 0;
                }
                if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) {
                    moveRec.y = 0;
                }
                break;
            default:
                break;
            }
        }


        pointer.move(moveRec);
        pos = pointer.getPosition();
        if (pos.x > win_w - item_size) pointer.setPosition(win_w - item_size, pos.y);
        if (pos.x < 0) pointer.setPosition(0, pos.y);
        if (pos.y > win_h - item_size) pointer.setPosition(pos.x, win_h - item_size);
        if (pos.y < 0) pointer.setPosition(pos.x, 0);

        is_goal = true;
        for (int i = 0; i < num; ++i) {
            if (goals[i]->getStatus()) {
                if (goals[i]->is_target(Vector2f(pos.x + p_dx, pos.y + p_dy))) {
                    goals[i]->setStatus(false);
                    soundPshhh.play();
                }
                else {
                    is_goal = false;
                }
            }
        }    

        win.clear();
        if (is_goal) {
            win.draw(starGood);
            win.draw(signGood);
            soundPshhh.stop();
            soundGood.play();
        }
        else {
            // Обновление анимации
            Time deltaTime = clock.restart();
            for (int i = 0; i < num; ++i) {
                if (goals[i]->getStatus()) {
                    goals[i]->Update(deltaTime);
                    win.draw(goals[i]->getSprite());
                }
            }    
            win.draw(pointer);
        }
        win.display();

        if (is_goal) {
            sleep(3);
            is_goal = false;
            pointer.setPosition((win_w - item_size)/ 2,(win_h - item_size)/ 2);
            for (int i = 0; i < num; ++i) {
                goals[i]->setStatus(true);
                goals[i]->setPosition(Vector2i(rand() % (win_w - item_size * 2) + item_size, rand() % (win_h - item_size * 2) + item_size));
            }  
        }
    }

    return 0;

}