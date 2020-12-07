#include "retry.h"


using namespace sf;

gameover::gameover(float width, float height) {

	if (!font.loadFromFile("font/al-seana.ttf")) {

	}



	t.setSmooth(true);

	choice.setTexture(&t);
	choice.setSize(Vector2f(533, 800));


	choices[0].setFont(font);
	choices[0].setFillColor(Color::White);
	choices[0].setCharacterSize(50);
	choices[0].setString("PLAY AGAIN");
	choices[0].setOrigin(choices[0].getLocalBounds().width / 2, choices[0].getLocalBounds().height / 2);
	choices[0].setPosition(width / 2, height / (max_items_retry + 1) * 1);


	choices[1].setFont(font);
	choices[1].setFillColor(Color::Black);
	choices[1].setCharacterSize(30);
	choices[1].setString("MAIN MENU");
	choices[1].setOrigin(choices[1].getLocalBounds().width / 2, choices[1].getLocalBounds().height / 2);
	choices[1].setPosition(width / 2, height / (max_items_retry + 1) * 2);

	
}
gameover::~gameover() {

}
void gameover::draw(RenderWindow& window) {
	//window.draw(choices);
	for (int i = 0; i < max_items_retry; i++) {
		window.draw(choices[i]);
	}

}

void gameover::moveUp2() {
	if (selectedItem2 - 1 >= 0) {
		choices[selectedItem2].setFillColor(Color::Black);
		selectedItem2--;
		choices[selectedItem2].setFillColor(Color::White);
	}
}
void gameover::moveDown2() {
	if (selectedItem2 + 1 < max_items_retry) {
		choices[selectedItem2].setFillColor(Color::Black);
		selectedItem2++;
		choices[selectedItem2].setFillColor(Color::White);
	}
}

