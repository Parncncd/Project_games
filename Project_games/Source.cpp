#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<time.h>
#include<Windows.h>
#define windowWidth 320
#define windowHeight 512
#define doodleWidth 62
#define doodleHeight 60
using namespace sf;
struct point

	{ int x, y; };

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(320, 512), "POOPLE JUMP!");
	window.setFramerateLimit(60);
	sf::RectangleShape player(sf::Vector2f(doodleWidth, doodleHeight));
	sf::RectangleShape background(sf::Vector2f(windowWidth,windowHeight));
	Texture normPlatform, crackPlatform,bcg;
	Texture doodRight, doodLeft;
	
	Sprite sBackground(bcg), sNormPlatform(normPlatform), sRNormDood(doodRight),sLNormDood(doodLeft);
	sNormPlatform.setScale(76.0f, 2 * 28.0f / 3);
	//getTexturesFromfile
	bcg.loadFromFile("images/space-bck.png");
	doodRight.loadFromFile("images/space-right.png");
	doodLeft.loadFromFile("images/space-left.png");
	normPlatform.loadFromFile("images/normPlat_1.png");

	point plat[20];
	for (int i = 0; i <= 10; i++) {
		plat[i].x = rand() % windowWidth;
		plat[i].y = rand() % windowHeight;
	}

	player.setPosition(windowWidth/2, 4*windowHeight/5);
	//player.setSize(sf::Vector2f(30.0f,30.0f));

	sf::Texture playerTexture,backgroundTexture;
	backgroundTexture.loadFromFile("images/space-bck.png");
	playerTexture.loadFromFile("images/space-right.png");
	background.setTexture(&backgroundTexture);
	player.setTexture(&playerTexture);
	
		//game loop
	while (window.isOpen())
	{
		window.draw(sNormPlatform);
		sf::Event event;
		while (window.pollEvent(event))
		{ 
			//closing games
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)&&player.getPosition().x>=0.0f) {
			player.move(-1.0f, 0.0f);
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player.getPosition().x <=windowWidth-doodleWidth) {
			player.move(+1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			window.close();
		}
		if (player.getPosition().y >= windowHeight - doodleHeight) {
			player.setPosition(player.getPosition().x, windowHeight - doodleHeight);
		}
		
	// drawing platforms
		for (int i = 0; i <= 10; i++) {
			sNormPlatform.setPosition(plat[i].x, plat[i].y);
			window.draw(sNormPlatform);
		}
	
		window.clear();
		window.draw(background);
		window.draw(player);
		window.display();
	}
	

	return 0;
}