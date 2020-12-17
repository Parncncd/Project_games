#include "retry.h"
using namespace sf;

gameover::gameover(float width, float height) {

	//setting Color
	darkBlue.b = 60;
	lightGrey.r = 80;
	lightGrey.g = 80;
	lightGrey.b = 90;
	darkRed.r = 92;

	if (!font.loadFromFile("font/al-seana.ttf")) {

	}
	if (true) {
		t.loadFromFile("images/border.png");
		tArrow.loadFromFile("images/arrowToPress.png");
	}
	t.setSmooth(true);
	tArrow.setSmooth(true);

	Border.setTexture(&t);
	Border.setPosition(135, 40);
	Border.setSize(Vector2f(t.getSize().x, t.getSize().y));
	Border.setScale(1.3, 1.3);

	arrow.setTexture(&tArrow);
	arrow.setPosition((width / 2)+80 , 350);
	arrow.setSize(Vector2f(tArrow.getSize().x, tArrow.getSize().y));
	arrow.setScale(0.3, 0.3);

	gameOver.setFont(font);
	gameOver.setFillColor(darkRed);
	gameOver.setCharacterSize(50);
	gameOver.setString("GAME OVER");
	//gameOver.setOrigin();
	gameOver.setPosition(175, 50);
	gameOver.setStyle(Text::Bold);


	your.setFont(font);
	your.setFillColor(Color::Black);
	your.setCharacterSize(31);
	your.setString("your");
	your.setPosition((width/3)+15, (height / 3) );
	your.setStyle(Text::Bold);

	yourName.setFont(font);
	yourName.setFillColor(Color::Black);
	yourName.setCharacterSize(30);
	yourName.setString("your name: ");
	yourName.setPosition((width/2)-85, 380-75);
	yourName.setStyle(Text::Bold);

	presstochange.setFont(font);
	presstochange.setFillColor(darkRed);
	presstochange.setCharacterSize(20);
	presstochange.setString("press to change");
	presstochange.setPosition((width / 2)+120 , 365);


	choices[0].setFont(font);
	choices[0].setFillColor(Color::White);
	choices[0].setCharacterSize(40);
	choices[0].setString("PLAY  AGAIN");
	choices[0].setLetterSpacing(2.5);
	choices[0].setOrigin(choices[0].getLocalBounds().width / 2, choices[0].getLocalBounds().height / 2);
	choices[0].setPosition(width / 2, ((7*height)/9)-70);


	choices[1].setFont(font);
	choices[1].setFillColor(darkBlue);
	choices[1].setCharacterSize(40);
	choices[1].setLetterSpacing(2.5);
	choices[1].setString("MAIN  MENU");
	choices[1].setOrigin(choices[1].getLocalBounds().width / 2, choices[1].getLocalBounds().height / 2);
	choices[1].setPosition(width / 2,50+((7 * height) / 9));

	
}
gameover::~gameover() {
}
void gameover::draw(RenderWindow& window) {

	window.draw(Border);
	window.draw(gameOver);
	window.draw(your);
	window.draw(yourHighScore);
	window.draw(yourName);
	window.draw(arrow);
	window.draw(presstochange);
	for (int i = 0; i < max_items_retry; i++) {
		window.draw(choices[i]);
	}
}

void gameover::moveUp2() {
	if (selectedItem2 - 1 >= 0) {
		choices[selectedItem2].setFillColor(darkBlue);
		selectedItem2--;
		choices[selectedItem2].setFillColor(Color::White);
	}
}
void gameover::moveDown2() {
	if (selectedItem2 + 1 < max_items_retry) {
		choices[selectedItem2].setFillColor(darkBlue);
		selectedItem2++;
		choices[selectedItem2].setFillColor(Color::White);
	}
}

