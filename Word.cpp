
#include "Word.h"



// void Word::setInitText(sf::Text& text, char str, float xpos, float ypos) const
// {
// 	text.setFont(font);
// 	text.setFillColor(letter_color);
// 	text.setString(static_cast<sf::String>(str));
// 	text.setCharacterSize(size_font);
// 	text.setPosition(xpos, ypos);
// 	// text.setOutlineThickness(3);
// 	// text.setOutlineColor(border_color);
// }

// Word::Word(sf::RenderWindow& window, float centerX, float centerY, int fSize, std::string& word, std::string const& audioF, std::string const& textureF)
//             : win(window), x(centerX), y(centerY), len(word.length()), size_font(fSize), letter_list{}
// {
//     if (!font.loadFromFile("font/Vollkorn-SemiBoldItalic.ttf")) exit(32);
//     zvuk_buffer.loadFromFile(audioF);
//     zvuk.setBuffer(zvuk_buffer);
//     texture.loadFromFile(textureF);
//     sprite.setPosition((win.getSize().x - texture.getSize().x ) / 2, (win.getSize().y - texture.getSize().y) / 2);
//     sprite.setTexture(texture);

//     for (int i = 0, xpos = static_cast<int>(x); i < len; i++, xpos += size_font * 2) {
//         Word::setInitText(letter_list[i], static_cast<char>(word[i]),  static_cast<float>(xpos), y);
//         std::cout << i << "(" << word[i] << ")"<< std::endl;
//     }
// 	current_letter = 0;
// 	letter_list[current_letter].setFillColor(current_letter_color);
//     letter_list[current_letter].setCharacterSize(size_font * 2);
// }

void Word::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
// void Word::setInitText(sf::Text& text, std::string const& str, float xpos, float ypos) const
{

	text.setFont(font);
	text.setFillColor(letter_color);
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setPosition(xpos, ypos);
	// text.setOutlineThickness(3);
	// text.setOutlineColor(border_color);
}

Word::Word(sf::RenderWindow& window, float centerX, float centerY, int fSize, const sf::String& word, std::string const& audioF, std::string const& textureF)
            // : win(window), x(centerX), y(centerY), letter_list(word.getSize()), len(word.getSize()), size_font(fSize), stroka(str)
            : win(window), x(centerX), y(centerY), letter_list(word.getSize()), len(word.getSize()), size_font(fSize)
{
    if (!font.loadFromFile("font/Vollkorn-SemiBoldItalic.ttf")) exit(32);
    zvuk_buffer.loadFromFile(audioF);
    zvuk.setBuffer(zvuk_buffer);
    texture.loadFromFile(textureF);
    sprite.setPosition((win.getSize().x - texture.getSize().x ) / 2, (win.getSize().y - texture.getSize().y) / 2);
    sprite.setTexture(texture);


    for (int i = 0, xpos = static_cast<int>(x); i < len; i++, xpos += size_font * 2) {
		// setInitText(letter_list[i], word[i],  static_cast<float>(xpos), y); // так работатет
		setInitText(letter_list[i], word[i], static_cast<float>(xpos), y);
		// setInitText(letter_list[i], static_cast<sf::String>(L"" + str[i]),  static_cast<float>(xpos), y);
		// setInitText(letter_list[i], str,  static_cast<float>(xpos), y);
    }
	current_letter = 0;
	letter_list[current_letter].setFillColor(current_letter_color);
    letter_list[current_letter].setCharacterSize(size_font * 2);
}

Word::~Word()
{
}

void Word::draw()
{
    // this->win.draw(sprite);
    for (int i = 0; i < len; i++) win.draw(letter_list[i]);
}

void Word::play()
{
    this->zvuk.play();
}

bool Word::nextLetter()
{
    if (++current_letter == len) return false;

    letter_list[current_letter - 1].setFillColor(letter_color);
    letter_list[current_letter - 1].setCharacterSize(size_font);
    letter_list[current_letter].setFillColor(current_letter_color);
    letter_list[current_letter].setCharacterSize(size_font * 2);
    return true;
}

void Word::restart()
{
    letter_list[current_letter - 1].setFillColor(letter_color);
    letter_list[current_letter - 1].setCharacterSize(size_font);
    current_letter = 0;
    letter_list[current_letter].setFillColor(current_letter_color);
    letter_list[current_letter].setCharacterSize(size_font * 2);
}

sf::Sprite Word::getGoalSprite()
{
    return this->sprite;
}

sf::Keyboard::Key Word::getKeyLetter()
{
    // std::map<char, int> letter_code {
    //     {'х', 46},
    //     {'л', 10},
    //     {'е', 19},
    //     {'б', 49}
    // };

    // std::cout << this->current_letter << "AA" << this->letter_list[this->current_letter].getString().toAnsiString() << std::endl;
    return static_cast<sf::Keyboard::Key>(letter_code[this->letter_list[this->current_letter].getString()[0]]);
}
    // std::map<char, int> letter_code;
    // letter_code['х'] = 46;
    // letter_code['л'] = 10;
    // letter_code['е'] = 19;
    // letter_code['б'] = 49;

    // letter_code["х"] = 46;
    // letter_code["л"] = 10;
    // letter_code["е"] = 19;
    // letter_code["б"] = 49;
    // return sf::Keyboard::Key::A;
    // std::cout << current_letter << "-" << static_cast<std::string>(letter_list[2].getString()) << std::endl;
    // return sf::Keyboard(2);