#include "StartMenu.h"


void StartMenu::setInitText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
{
	text.setFont(font);
	text.setFillColor(menu_text_color);
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(border_color);
}

StartMenu::StartMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<sf::String>& name)
	:x(menux), y(menuy), step(step), max_item(static_cast<int>(name.size())), size_font(sizeFont), item_list(name.size()), mywindow(window)
{
	if (!font.loadFromFile("font/Vollkorn-SemiBoldItalic.ttf")) exit(32);

	for (int i = 0, ypos = static_cast<int>(y); i < max_item; i++, ypos += step)
		setInitText(item_list[i], name[i], x, static_cast<float>(ypos));
	selected_item = 0;
	item_list[selected_item].setFillColor(chose_text_color);
}

StartMenu::~StartMenu()
{

}

void StartMenu::MoveUp()
{
	selected_item--;

	if (selected_item >= 0) {
		item_list[selected_item].setFillColor(chose_text_color);
		item_list[selected_item + 1].setFillColor(menu_text_color);
	}
	else
	{
		item_list[0].setFillColor(menu_text_color);
		selected_item = max_item - 1;
		item_list[selected_item].setFillColor(chose_text_color);
	}
}

void StartMenu::MoveDown()
{
	selected_item++;

	if (selected_item < max_item) {
		item_list[selected_item - 1].setFillColor(menu_text_color);
		item_list[selected_item].setFillColor(chose_text_color);
	}
	else
	{
		item_list[max_item - 1].setFillColor(menu_text_color);
		selected_item = 0;
		item_list[selected_item].setFillColor(chose_text_color);
	}

}

void StartMenu::draw()
{
	for (int i = 0; i < max_item; i++) mywindow.draw(item_list[i]);
}

void StartMenu::setColorTextMenu(sf::Color menColor, sf::Color ChoColor, sf::Color BordColor)
{
	menu_text_color = menColor;
	chose_text_color = ChoColor;
	border_color = BordColor;

	for (int i = 0; i < max_item; i++) {
		item_list[i].setFillColor(menu_text_color);
		item_list[i].setOutlineColor(border_color);
	}

	item_list[selected_item].setFillColor(chose_text_color);
}