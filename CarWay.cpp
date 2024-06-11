#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <unistd.h>

#include "Road.h"

using namespace sf;

void generateLevel(std::vector<Vector2f>& level, const int i_size, const int r_w, const float& k_x, const float& k_y) {
    bool is_x = true;
    int x = 0;
    int y = rand() % 10; // генерируем случайное число от 0 до 9
    const int max = 9;
    level.clear();
    while (true) {
        level.push_back(Vector2f(x * k_x + i_size, y * k_y + r_w));
        if (x == max) {
            break;
        }
        if (is_x) {
            // x += rand() % 3 + 1; // от 1 до 3
            x += rand() % 2 + 2; // от 2 до 3
            if (x > max) { x = max; }
            is_x = false;
        }
        else {
            y = (y + rand() % 7 + 2) % 10; // от 0 до 9, исключая предыдущее значение и отличающиеся от него на 1
            is_x = true;
        }
    }
}


int CarWay() {

    const int item_size = 200;
    const int speed = 2;
    const int road_w = 100;
    srand(time(NULL));
    int win_w, win_h;

    RenderWindow win;
    win.create(VideoMode::getDesktopMode(), L"Машинка", Style::Fullscreen);
    win.setMouseCursorVisible(false); //отключаем видимость курсора
    win.setPosition(Vector2i(0, 0));
    // Размер экрана
    win_w = static_cast<int>(VideoMode::getDesktopMode().width);
    win_h = static_cast<int>(VideoMode::getDesktopMode().height);

    RectangleShape grass(Vector2f(win_w, win_h));
    Texture texture_grass;
    grass.setTextureRect(IntRect(0,0, win_w, win_h));
    if (!texture_grass.loadFromFile("img/grass_2.jpg")) exit(2);
    texture_grass.setRepeated(true);
    grass.setTexture(&texture_grass);


    // std::vector<Vector2f> p{
    //     Vector2f(0, 5),
    //     Vector2f(2, 5),
    //     Vector2f(2, 9),
    //     Vector2f(5, 9),
    //     Vector2f(5, 4),
    //     Vector2f(6, 4),
    //     Vector2f(6, 0),
    //     Vector2f(8, 0),
    //     Vector2f(8, 8),
    //     Vector2f(9, 8),
    // };

    float kx = (win_w - 2 * item_size) / 9;
    float ky = (win_h - 2 * road_w) / 9;
    std::vector<Vector2f> p;
    generateLevel(p, item_size, road_w, kx, ky);

    // for (int i = 0; i < p.size(); ++i) {
    //     // std::cout <<  i << " - " << p[i].x << ":" << p[i].y << std::endl;
    //     p[i].x = p[i].x * kx + item_size;
    //     p[i].y = p[i].y * ky + road_w;
    // }


    const int x_max = win_w - item_size;
    Road road(win, p);
    road.setWidth(road_w);



    // Звездочка молодец
    Texture TextureCarGood;
    TextureCarGood.loadFromFile("img/car_good.png");
    Sprite carGood;
    carGood.setPosition((win_w - 484) / 2, (win_h - 500) / 2 + 50);
    carGood.setTexture(TextureCarGood);
    
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

    // Машинка
    Vector2f pos;
    int distance = 0;
    float car_w = 192;
    float car_h = 96;
    const Vector2f delta_car {car_w / 2, car_h / 2};
    Texture TexturePointer;
    TexturePointer.loadFromFile("img/car.png");
    Sprite car;
    car.setPosition(p[0]);
    car.setOrigin(delta_car);
    car.setTexture(TexturePointer);
    float koef =  (static_cast<float>(item_size) / (car_w));
    car.setScale(koef, koef);
    
    // звук мотора
    SoundBuffer motor; 
    motor.loadFromFile("audio/motor.ogg");
    Sound soundMotor;
    soundMotor.setBuffer(motor);


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
                if ( (event.key.code == Keyboard::Left && road.getAngle()== 180) ||
                     (event.key.code == Keyboard::Right && road.getAngle()== 0) ||
                     (event.key.code == Keyboard::Up && road.getAngle()== -90) ||
                     (event.key.code == Keyboard::Down && road.getAngle()== 90))
                {
                    distance = timeCar;
                    if (soundMotor.getStatus() != 2) {
                        soundMotor.play();
                    }
                }
                else {distance = 0; soundMotor.pause();}

                if (event.key.code == Keyboard::Escape) {
                    win.close();
                }
                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Left || event.key.code == Keyboard::Right || event.key.code == Keyboard::Up || event.key.code == Keyboard::Down) {
                    distance = 0;
                    soundMotor.pause();
                }
                break;
            default:
                break;
            }
        }
        pos = road.move(distance);
        car.setPosition(pos);
        car.setOrigin(delta_car);
        car.setRotation(road.getAngle());

        if (car.getPosition().x >= x_max ) {
            is_goal = true;
            soundMotor.stop();
        }

        win.clear();

        if (is_goal) {
            win.draw(carGood);
            win.draw(signGood);
            soundGood.play();
        }
        else {
            win.draw(grass);
            road.draw();
            win.draw(car);
        }

        win.display();

        if (is_goal) {
            sleep(3);
            is_goal = false;
            car.setPosition(p[0]);
            car.setOrigin(delta_car);
            generateLevel(p, item_size, road_w, kx, ky);
            road.update(p);
        }
    }

    return 0;
}
