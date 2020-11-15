#include "Menu.h"
using namespace sf;

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("font/al-seana.ttf")) {
		
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Green);
	menu[0].setCharacterSize(72);
	menu[0].setString("PLAY");
	//menu[0].setOrigin(menu[0].getLocalBounds)
	menu[0].setPosition(width / 2, height / (max_items + 1) * 1);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::Green);
	menu[1].setCharacterSize(59);
	menu[1].setString("HOW TO PLAY");
	menu[1].setPosition(width / 2, height / (max_items + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::Green);
	menu[2].setCharacterSize(50);
	menu[2].setString("LEADER BOARD");
	menu[2].setPosition(width / 2, height / (max_items + 1) * 3);

	menu[3].setFont(font);
	menu[3].setFillColor(Color::Green);
	menu[3].setCharacterSize(50);
	menu[3].setString("QUIT");
	menu[3].setPosition(width / 2, height / (max_items + 1) * 4);
}
Menu::~Menu(){

}
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < max_items; i++) {
		window.draw(menu[i]);
	}
}
