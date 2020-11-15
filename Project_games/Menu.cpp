#include "Menu.h"
using namespace sf;

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("font/al-seana.ttf")) {
		
	}
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Green);
	menu[0].setCharacterSize(72);
	menu[0].setString("PLAY");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(width / 2, height / (max_items + 1) * 1);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::Black);
	menu[1].setCharacterSize(50);
	menu[1].setString("HOW TO PLAY");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(width / 2, height / (max_items + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::Black);
	menu[2].setCharacterSize(50);
	menu[2].setString("LEADER BOARD");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(width / 2, height / (max_items + 1) * 3);

	menu[3].setFont(font);
	menu[3].setFillColor(Color::Black);
	menu[3].setCharacterSize(50);
	menu[3].setString("QUIT");
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 2);
	menu[3].setPosition(width / 2, height / (max_items + 1) * 4);
}
Menu::~Menu(){

}
void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < max_items; i++) {
		window.draw(menu[i]);
	}
}
void Menu::moveUp() {
	if (selectedItem - 1 >= 0) {
		menu[selectedItem].setFillColor(Color::Black);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::Green);
	}
}
void Menu::moveDown() {
	if (selectedItem + 1 <=max_items ) {
		menu[selectedItem].setFillColor(Color::Black);//เปลี่ยนสีตัวเลือกที่เลือกอยู่ให้เป็นสีดำ จากสีเขียว
		selectedItem++;//เลื่อนไปตัวเลือกถัดไป
		menu[selectedItem].setFillColor(Color::Green);
	}
}

