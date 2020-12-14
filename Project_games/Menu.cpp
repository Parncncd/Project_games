#include "Menu.h"

using namespace sf;

Menu::Menu(float width, float height) {
	
	if (!font.loadFromFile("font/al-seana.ttf")) {

	}
	if (true) {
		t.loadFromFile("images/space-bck.png");
		tKeyUpDown.loadFromFile("images/arrow_keyboard.png");
		tgamename.loadFromFile("images/GameName.png");
		tborder.loadFromFile("images/border.png");
	}
	t.setSmooth(true);
	background.setTexture(&t);
	background.setSize(Vector2f(533,800));

	tKeyUpDown.setSmooth(true);
	KeyUpDown.setTexture(&tKeyUpDown);
	KeyUpDown.setSize(Vector2f(tKeyUpDown.getSize().x, tKeyUpDown.getSize().y));
	KeyUpDown.setScale(0.1,0.1);
	KeyUpDown.setPosition(75, 630);

	tgamename.setSmooth(true);
	gamename.setTexture(&tgamename);
	gamename.setSize(Vector2f(tgamename.getSize().x, tgamename.getSize().y));
	gamename.setScale(0.5, 0.5);
	gamename.setPosition(155,40);

	tborder.setSmooth(true);
	border.setTexture(&tborder);
	border.setSize(Vector2f(tborder.getSize().x,tborder.getSize().y ));
	border.setScale(2.3, 2.3);
	border.setPosition(150,40);


	//setting Color
	darkBlue.b = 60;
	lightGrey.r = 224;
	lightGrey.g = 224;
	lightGrey.b = 224;

	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setCharacterSize(50);
	menu[0].setString("PLAY");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, (menu[0].getLocalBounds().height / 2)-50);
	menu[0].setPosition(width / 2, height / (max_items + 1) * 1);


	menu[1].setFont(font);
	menu[1].setFillColor(Color::Black);
	menu[1].setCharacterSize(30);
	menu[1].setString("HOW TO PLAY");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2,( menu[1].getLocalBounds().height / 2)-20);
	menu[1].setPosition(width / 2, height / (max_items + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::Black);
	menu[2].setCharacterSize(30);
	menu[2].setString("LEADER BOARD");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, (menu[2].getLocalBounds().height / 2)-20);
	menu[2].setPosition(width / 2, height / (max_items + 1) * 3);

	menu[3].setFont(font);
	menu[3].setFillColor(Color::Black);
	menu[3].setCharacterSize(30);
	menu[3].setString("QUIT");
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 2);

	menu[3].setPosition(width / 2, height / (max_items + 1) * 4);

	direction1.setFont(font);
	direction1.setString("PRESS ");
	direction1.setStyle(Uint32(Text::Bold));
	direction1.setFillColor(darkBlue);
	direction1.setCharacterSize(15);
	direction1.setPosition(300, 650);

	direction2.setFont(font);
	direction2.setString(" TO SELECT");
	direction2.setStyle(Uint32(Text::Bold));
	direction2.setFillColor(darkBlue);
	direction2.setCharacterSize(15);
	direction2.setPosition(400, 650);

	direction3.setFont(font);
	direction3.setString("PRESS");
	direction3.setStyle(Uint32(Text::Bold));
	direction3.setFillColor(darkBlue);
	direction3.setCharacterSize(15);
	direction3.setPosition(30, 650);

	direction4.setFont(font);
	direction4.setString(" TO MOVE UP OR DOWN");
	direction4.setStyle(Uint32(Text::Bold));
	direction4.setFillColor(darkBlue);
	direction4.setCharacterSize(15);
	direction4.setPosition(130, 650);

	enter_direction.setFont(font);
	enter_direction.setString(" ENTER ");
	enter_direction.setStyle(Uint32(Text::Bold));
	enter_direction.setFillColor(lightGrey);
	enter_direction.setCharacterSize(20);
	enter_direction.setPosition(340, 645);


}
Menu::~Menu() {

}
void Menu::draw(RenderWindow& window) {
	window.draw(background);
	window.draw(enter_direction);
	window.draw(direction1);
	window.draw(direction2);
	window.draw(direction3);
	window.draw(direction4);
	window.draw(KeyUpDown);
	window.draw(border);
	window.draw(gamename);
	
	for (int i = 0; i < max_items; i++) {
		window.draw(menu[i]);
	}
	
}

void Menu::moveUp() {
	if (selectedItem - 1 >= 0) {
		menu[selectedItem].setFillColor(Color::Black);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::White);
	}
}
void Menu::moveDown() {
	if (selectedItem + 1 < max_items) {
		menu[selectedItem].setFillColor(Color::Black);
		selectedItem++;
		menu[selectedItem].setFillColor(Color::White);
	}
}


