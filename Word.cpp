
#include "Word.h"


void Word::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
{

	text.setFont(font);
	// text.setFillColor(letter_color);
	text.setFillColor(sf::Color(0, 0, 0, 0));
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(2);
	text.setOutlineColor(letter_color);
}

Word::Word(sf::RenderWindow& window, float centerX, float centerY, int fSize, const sf::String& word, std::string const& audioF, std::string const& textureF)
            : win(window), x(centerX), y(centerY), letter_list(word.getSize()), len(word.getSize()), size_font(fSize)
{
    // if (!font.loadFromFile("font/Industry-Bold.ttf")) exit(32);
    if (!font.loadFromFile("font/Waffle-Slab2.otf")) exit(32);
    zvuk_buffer.loadFromFile(audioF);
    zvuk.setBuffer(zvuk_buffer);
    texture.loadFromFile(textureF);
    sprite.setPosition((win.getSize().x - texture.getSize().x ) / 2, (win.getSize().y - texture.getSize().y) / 2);
    sprite.setTexture(texture);

    setInitText(letter_list[0], word[0], 0, 0); // просто чтоб получить ширину буквы, для центрирования слова
    x = (win.getSize().x - ((len - 1) * 1 * size_font + letter_list[0].getLocalBounds().width)) / 2; // центрируем слов по горизонтали

    // слово целиком
    setInitText(whole_word, word, 0, 0);
    whole_word.setFillColor(letter_color);
    whole_word.setLetterSpacing(5);
    whole_word.setPosition((win.getSize().x - whole_word.getLocalBounds().width) / 2, 50);

    // слово по буквам
    for (int i = 0, xpos = static_cast<int>(x); i < len; i++, xpos += size_font * 1) {
		setInitText(letter_list[i], word[i], static_cast<float>(xpos), y);
    }

    // настройка текущей буквы
	current_letter_num = 0;
    setInitText(current_letter, word[current_letter_num], window.getSize().x / 2, y + size_font);
    current_letter.setFillColor(letter_color);
    current_letter.setCharacterSize(size_font * 4);
    current_letter.setPosition(current_letter.getPosition().x - current_letter.getLocalBounds().width / 2, current_letter.getPosition().y);

	letter_list[current_letter_num].setFillColor(current_letter_color);

    press_letter_buff.loadFromFile("audio/нажми_букву.ogg");
    sound_press_letter.setBuffer(press_letter_buff);
}

Word::~Word()
{
}

void Word::draw()
{
    for (int i = 0; i < len; i++) win.draw(letter_list[i]); // слово по буквам

    win.draw(current_letter); // текущая буква
}

void Word::draw_whole()
{
    win.draw(whole_word); // слово целиком
}

void Word::play()
{
    this->zvuk.play();
    while (this->zvuk.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(500));
    }
}

void Word::play_letter()
{
    sound_press_letter.play();
    while (sound_press_letter.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(500));
    }
    letter_zvuk_buffer.loadFromFile("audio/letters/" + letter_code[letter_list[current_letter_num].getString()[0]].sound_file);
    letter_zvuk.setBuffer(letter_zvuk_buffer);
    this->letter_zvuk.play();
    while (this->letter_zvuk.getStatus() == sf::Sound::Playing) {
        sf::sleep(sf::milliseconds(500));
    }
}

bool Word::nextLetter()
{
    if (++current_letter_num == len) return false;

     // this->play_letter();

    letter_list[current_letter_num - 1].setFillColor(letter_color);
    letter_list[current_letter_num - 1].setCharacterSize(size_font);
    letter_list[current_letter_num].setFillColor(current_letter_color);
    current_letter.setString(letter_list[current_letter_num].getString());
    return true;
}

bool Word::animate_letter(int delta)
{
    if (delta >= this->time_anim.asMilliseconds()) {
        current_letter.setCharacterSize(size_font * 4);
        // current_letter.setPosition(0, 0);
        return true;
    }

    int s;
    s = size_font * (4 - 3 * delta / this->time_anim.asMilliseconds());
    // current_letter.setPosition(0, 0);
    current_letter.setCharacterSize(s);
    return false;
}

// void Word::restart()
// {
//     letter_list[current_letter_num - 1].setFillColor(letter_color);
//     letter_list[current_letter_num - 1].setCharacterSize(size_font);
//     current_letter_num = 0;
//     letter_list[current_letter_num].setFillColor(current_letter_color);
//     // letter_list[current_letter_num].setCharacterSize(size_font * 2);
// }

sf::Sprite Word::getGoalSprite()
{
    return this->sprite;
}

sf::Keyboard::Key Word::getKeyLetter()
{
    return static_cast<sf::Keyboard::Key>(letter_code[this->letter_list[this->current_letter_num].getString()[0]].key);
}
