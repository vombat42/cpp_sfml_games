#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <unistd.h>


#include "StartMenu.h"
#include "ArrowFirst.cpp"
#include "FireFighter.cpp"


using namespace sf;

int main(int argc, char const *argv[])
{
    // Создаём окно windows
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);
    window.setMouseCursorVisible(false); //отключаем видимость курсора
    // Размер экрана
    auto width = static_cast<float>(VideoMode::getDesktopMode().width);
    auto height = static_cast<float>(VideoMode::getDesktopMode().height);

    // Название пунктов меню
    std::vector<String> name_menu{ L"\"Наведи на цель\"",L"\"Пожарный\"", L"Выход" };

    // Объект меню
    StartMenu mymenu(window, 900, 300, 100, 120, name_menu);
    // Установка цвета отображения меню
    mymenu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
    // mymenu.AlignMenu(2);


    // Устанавливаем фон экрана меню
    RectangleShape background(Vector2f(width, height));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::KeyReleased)
            {
                // События выбра пунктов меню
                if (event.key.code == Keyboard::Up) { mymenu.MoveUp(); }      // вверх
                if (event.key.code == Keyboard::Down) { mymenu.MoveDown(); }  // вниз
                if (event.key.code == Keyboard::Return)                       // ввод
                {
                    // Переходим на выбранный пункт меню
                    switch (mymenu.getSelectedMenuNumber())
                    {
                    case 0:ArrowFirst(); break;    // первая игра
                    case 1:FireFighter(); break;
                    case 2:window.close(); break;
                    default:break;
                    }
                }
            }
        }

        // Область отрисовки объектов      
        window.clear();
        mymenu.draw();
        window.display();
    }
    return 0;

}