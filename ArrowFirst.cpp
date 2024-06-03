#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <unistd.h>

using namespace sf;

enum parametrs {
    item_size = 75,
    speed = 1,
};

int ArrowFirst()
{
    srand(time(NULL));
    int win_w, win_h;

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
    buffer.loadFromFile("audio/umnitsa.ogg");
    Sound soundGood;
    soundGood.setBuffer(buffer);

    // Указатель
    Vector2f moveRec, pos, target_pos;
    CircleShape pointer(item_size);
    pointer.setFillColor(Color::Green);
    pointer.setPosition((win_w - item_size)/ 2, (win_h - item_size)/ 2);

    // Цель
    CircleShape target(item_size);
    target.setFillColor(Color(0,0,0,0));
    target.setOutlineThickness(3);
    target.setOutlineColor(Color::Green);
    target_pos.x = rand() % (win_w - item_size * 2);
    target_pos.y = rand() % (win_h - item_size * 2);
    target.setPosition(target_pos.x, target_pos.y);
    
    Clock clock;
    float time, timePointer;

    bool is_goal {false};

    while (win.isOpen())
    {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        timePointer = time / 6000 * speed;
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
            win.draw(target);
            win.draw(pointer);
        }
        win.display();

        if (is_goal) {
            sleep(4);
            is_goal = false;
            pointer.setPosition((win_w - item_size)/ 2,(win_h - item_size)/ 2);
            target_pos.x = rand() % (win_w - item_size * 2);
            target_pos.y = rand() % (win_h - item_size * 2);
            target.setPosition(target_pos.x, target_pos.y);
        }
    }

    return 0;
}