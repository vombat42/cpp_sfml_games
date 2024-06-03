#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>


#include "AssetManager.h"
#include "Animator.h"


using namespace sf;

int FireFighter() {
    AssetManager manager;

    srand(time(NULL));
    int win_w, win_h;
    const int item_size = 140;
    const int speed = 1;

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
    SoundBuffer buffer; 
    buffer.loadFromFile("audio/good.ogg");
    Sound soundGood;
    soundGood.setBuffer(buffer);

    Vector2f moveRec, pos, target_pos;

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



    // Цель
    // Анимация костра
    int fire_w = 180;
    int fire_h = 200;
    Vector2i spriteSize(fire_w, fire_h);
    Sprite target;
    koef =  (static_cast<float>(item_size) / static_cast<float>(fire_h));
    target.setScale(koef, koef);

    target_pos.x = rand() % (win_w - item_size * 2);
    target_pos.y = rand() % (win_h - item_size * 2);
    target.setPosition(target_pos.x, target_pos.y);

    Animator animator(target);
    auto& fireAnimation = animator.CreateAnimation("flame", "img/flame.png", seconds(1), true);
    fireAnimation.AddFrames(Vector2i(0, 0), spriteSize, 3, 2);



    Clock clock;
    float time, timePointer;

    bool is_goal {false};

    while (win.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timePointer = time / 6000 * speed;
        // clock.restart();

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
        if (pos.x > win_w - item_size * 2) pointer.setPosition(win_w - item_size * 2, pos.y);
        if (pos.x < 0) pointer.setPosition(0, pos.y);
        if (pos.y > win_h - item_size * 2) pointer.setPosition(pos.x, win_h - item_size * 2);
        if (pos.y < 0) pointer.setPosition(pos.x, 0);
        if (sqrt(pow((target_pos.x - pos.x), 2) + pow((target_pos.y - pos.y), 2)) < item_size / 2 ) {
            is_goal = true;
        }
        else {
            is_goal = false;
        }


        win.clear();
        if (is_goal) {
            win.draw(starGood);
            win.draw(signGood);
            soundGood.play();
        }
        else {
            // Обновление анимации
            Time deltaTime = clock.restart();
            animator.Update(deltaTime);
            win.draw(target);
            win.draw(pointer);
        }
        win.display();

        if (is_goal) {
            sleep(3);
            is_goal = false;
            pointer.setPosition((win_w - item_size)/ 2,(win_h - item_size)/ 2);
            target_pos.x = rand() % (win_w - item_size * 2);
            target_pos.y = rand() % (win_h - item_size * 2);
            target.setPosition(target_pos.x, target_pos.y);
        }
    }

    return 0;

}