#include <SFML/Graphics.hpp>
#include <time.h>
#include<Windows.h>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iostream>
#include"Menu.h"
#include"retry.h"

#define windowWidth 533
#define windowHeight 680
#define doodleWidth 62
#define doodleHeight 60
#define normPlatWidth 68
#define normPlatHeight 17
using namespace sf;

struct point
{
	int x, y;
};
int main()
{
	srand(time(0));
	Clock clock1, clock2;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
	window.setFramerateLimit(60);

	window.setMouseCursorVisible(false);

	//Menu window
	Menu menu(windowWidth, windowHeight);

	//retry window
	gameover gameover(windowWidth, windowHeight);


	//cursor
	Cursor clickCursor;
	clickCursor.loadFromSystem(Cursor::Hand);


	//Textures
	Texture t1;
	t1.loadFromFile("images/bck.png");
	Sprite sBackground(t1);

	Texture t2;
	t2.loadFromFile("images/new-Normplat_1.png");
	Sprite sPlat(t2);

	Texture t3;
	t3.loadFromFile("images/doodleAnimation.png");
	t3.setSmooth(true);
	Sprite player(t3);
	player.setScale(0.6, 0.6);
	int doodX = t3.getSize().x / 3;
	int doodY = t3.getSize().y;
	player.setTextureRect(IntRect(doodX * 2, doodY * 0, doodX, doodY));

	Texture t4;
	t4.loadFromFile("images/enemy1.png");
	t4.setSmooth(true);
	RectangleShape enemy;
	enemy.setSize(Vector2f(60, 62));
	enemy.setTexture(&t4);
	int enemyX = enemy.getSize().x;
	int enemyY = enemy.getSize().y;

	Texture t5;

	t5.loadFromFile("images/topscore.png");
	t5.setSmooth(true);

	RectangleShape topScoreCounting;//bar show on the top of the window, behind the score-counting
	topScoreCounting.setTexture(&t5);
	topScoreCounting.setSize(Vector2f(windowWidth, 70));
	topScoreCounting.setPosition(0, 0);

	RectangleShape bullet;
	bullet.setSize(Vector2f(5, 10));
	bullet.setFillColor(Color::White);

	//sounds 
	SoundBuffer s1;
	s1.loadFromFile("sound/laser.wav");
	Sound shootEffect;
	shootEffect.setBuffer(s1);
	SoundBuffer s2;
	s2.loadFromFile("sound/jump.wav");
	Sound jumpEffect;
	jumpEffect.setBuffer(s2);
	SoundBuffer s3;
	s3.loadFromFile("sound/monsterCrash.wav");
	Sound hitEnemySound;
	hitEnemySound.setBuffer(s3);
	SoundBuffer s4;
	s4.loadFromFile("sound/falling-sound-arcade.wav");
	Sound fallingSound;
	fallingSound.setBuffer(s4);
	SoundBuffer s5;
	s5.loadFromFile("sound/trampoline.wav");
	Sound trampolineSound;
	trampolineSound.setBuffer(s5);
	SoundBuffer s6;
	s6.loadFromFile("sound/chomp-monster.wav");
	Sound killMonSound;
	killMonSound.setBuffer(s6);
	SoundBuffer s7;
	s7.loadFromFile("sound/jumponmonster.wav");
	Sound stepOnMonSound;
	stepOnMonSound.setBuffer(s7);

	//text
	Font font;
	font.loadFromFile("font/al-seana.ttf");

	Text scoreCounting;
	scoreCounting.setFont(font);
	scoreCounting.setFillColor(Color::Black);
	scoreCounting.setCharacterSize(20);
	scoreCounting.setPosition(15, 0);

	Text highJump;
	highJump.setFont(font);
	highJump.setFillColor(Color::Black);
	highJump.setCharacterSize(20);
	highJump.setPosition(15, 25);
	
	Text menuDirection;
	menuDirection.setFont(font);
	menuDirection.setFillColor(Color::Black);
	menuDirection.setCharacterSize(35);
	menuDirection.setPosition(20, 20);

	//platform building
	point plat[20];

	point pEnemy[3];
	for (int i = 0; i < 2; i++) {
		pEnemy[i].x = rand() % (windowWidth - enemyX);
	}
	for (int i = 0; i < 5; i++)
	{
		plat[i].x = rand() % (windowWidth - normPlatWidth);

		plat[i].y = rand() % (windowHeight / 2);
	}

	for (int i = 5; i < 10; i++)
	{

		plat[i].x = rand() % (windowWidth - normPlatWidth);

		plat[i].y = (rand() % windowHeight / 2) + (windowHeight / 2);
	}

	//init values
	int x = 200, y = 200, h = windowHeight / 4;
	float dx = 0, dy = 0;
	int score = 0;
	int maxP = 10;
	int enemyScore = 10000;
	int platScore = 20000;
	bool enemyHitState = 0;
	bool enemyState = 0;
	bool fallingSoundState = 0;
	bool playerstate = 1;
	bool bulletState = 0;
	int itemStack = 2;
	bool bull_en_state = 0;
	bool gamestate = 0;//0 : menu || 1: games || 2: ending
	bool retryState = 0;
	bool menuState = 1;
	bool enemyGoRight = 1;
	bool enemyMove = 1;

	int bx = x;
	int by = y;

	float deltaTime = 0.0f;
	Clock clock;

	//start point
	player.setPosition((windowWidth - doodleWidth) / 2, windowHeight - normPlatHeight - doodleHeight);

	//RenderGame
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type) {
			case Event::KeyReleased:
				switch (e.key.code) {
				case Keyboard::Up:
					if (menuState == 1 && retryState == 0) {
						menu.moveUp();
					}
					break;

				case Keyboard::Down:
					if (menuState == 1 && retryState == 0) {
						menu.moveDown();
					}

					break;

				case Keyboard::Return:
					if (menuState == 1 && retryState == 0) {
						switch (menu.getPressedItem()) {
						case 0:
							std::cout << "Play has been pressed" << std::endl;
							gamestate = 1;
							menuState = 0;

							break;
						case 1:
							//how to play

							std::cout << "How to play has been pressed" << std::endl;
							break;
						case 2:
							//leaderboard
							std::cout << "Leaderboard has been pressed" << std::endl;

							break;
						case 3:
							std::cout << "Quit has been pressed" << std::endl;
							window.close();
							break;
						}
					}

					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}

		}

		if (menuState == 1) {
			retryState = 0;
			menu.draw(window);
		}


		if (gamestate == 1) {

			Time elapsed1 = clock1.getElapsedTime();
			Time elapsed2 = clock2.getElapsedTime();
			//Key input
			if (playerstate == 1) {
				if (Keyboard::isKeyPressed(Keyboard::Key::D) && player.getPosition().x <= windowWidth - doodleWidth) {
					x += 5;
					player.setTextureRect(IntRect(doodX * 2, doodY * 0, doodX, doodY));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::A) && player.getPosition().x >= 0) {
					x -= 5;
					player.setTextureRect(IntRect(doodX * 0, doodY * 0, doodX, doodY));
				}
				if (elapsed1.asSeconds() > 0.3) {
					clock1.restart();
					if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
						player.setTextureRect(IntRect(doodX * 1, doodY * 0, doodX, doodY));
						shootEffect.play();
						bullet.setPosition(player.getPosition().x, player.getPosition().y - 5);
						bulletState = 1;
					}
				}
				if (elapsed2.asSeconds() > 0.7) {
					clock2.restart();
					if (Keyboard::isKeyPressed(Keyboard::Key::W) && player.getPosition().y >= 200
						&& playerstate == 1 && player.getPosition().y <= windowWidth + doodleWidth && itemStack > 0) {
						trampolineSound.play();
						itemStack--;
						dy = -15;
					}
				}
			}
			//Gravity

			dy += 0.2;// dy is used like an acceleration. When +, player moves down, when -, player moves up 
			y += dy;// changing y value of player by plus dy. This is to make player move down

		//create new platform when doodle step on higher platform
		//score counting
			if (y < h) {
				if (enemyState == 1) {
					pEnemy[0].y = pEnemy[0].y - dy;
				}
				for (int i = 0; i < 10; i++)
				{
					y = h;
					plat[i].y = plat[i].y - dy;

					if (plat[i].y > windowHeight) {
						plat[i].y = 0;
						plat[i].x = rand() % (windowWidth - doodleWidth);
					}
					//bug!!!!!
					score -= dy;
				}

			}

			//counting score on screen
			std::stringstream ss;
			ss << "score: " << score << "\n";
			scoreCounting.setString(ss.str());

			//player step(jump) on mon
			if ((x + doodleWidth - 10 > enemy.getPosition().x) && (x + 10 < enemy.getPosition().x + enemy.getSize().x)
				&& (y + doodleHeight > enemy.getPosition().y) && (y + doodleHeight < enemy.getPosition().y + enemy.getSize().y) && (dy > 0) && playerstate == 1) {

				stepOnMonSound.play();
				dy = -15;
				pEnemy[0].y += 500;
				if (pEnemy[0].y > windowHeight) {

					pEnemy[0].x += 900;
				}
			}
			if (enemy.getPosition().y > windowHeight) {
				enemy.setPosition(windowWidth + 200, y);
			}
			if (score > platScore) {
				platScore += 20000;
				maxP--;
				printf(">>>>>>>>>  %d   <<<<<<<", maxP);

			}
			// if player step on platform, 
			for (int i = 0; i < maxP; i++)
				if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
					&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0) && playerstate == 1) {
					jumpEffect.play();
					dy = -10;
					/*enemyState = 0;
					enemy.setPosition(windowWidth + 500, y);*/
				}
			player.setPosition(x, y);

			if (enemyState == 1) {
				enemy.setPosition(pEnemy[0].x, pEnemy[0].y);
			}
			/*if (enemyState == 1) {
				if (pEnemy[0].x >= 0) {
					pEnemy[0].x -= 1;
				}
				if (enemy.getPosition().x == 0) {
					enemyGoRight = 1;
					pEnemy[0].x = 1;
				}
				if (pEnemy[0].x < windowWidth - enemy.getSize().x) {
					pEnemy[0].x += 1;
				}

			}*/
			if (playerstate == 0) {
				enemyMove = 0;
			}
			else {
				enemyMove = 1;
			}

				if (enemyState == 1 && enemyMove == 1) 
				{
					if (enemyGoRight == 1) {
						pEnemy[0].x += 5;
						if (pEnemy[0].x >= windowWidth - enemy.getSize().x) {
							enemyGoRight = 0;
						}
					}
					if (enemyGoRight == 0) {
						pEnemy[0].x -= 5;
						if (pEnemy[0].x <= 0) {
							enemyGoRight = 1;
						}
					}
				}
				window.draw(sBackground);


				window.draw(player);
				if (enemyState == 1) {
					window.draw(enemy);
				}
				//bullet moving
				if (bulletState == 1) {
					bullet.setPosition(player.getPosition().x + 30, by);
					window.draw(bullet);
					by -= 30;

				}
				if (bullet.getPosition().y <= 0) {
					bulletState = 0;
					by = player.getPosition().y;
				}
				//bullet hitting enemy
				if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()) && bull_en_state == 0) {
					enemy.setPosition(windowWidth + 50, windowHeight - 100);
					bulletState = 0;
					enemyState = 0;
					bull_en_state = 1;
				}

				if (bull_en_state == 1) {
					itemStack++;
					bull_en_state = 0;
				}
				std::stringstream skill;
				skill << "Skill left: " << itemStack << "\n";
				highJump.setString(skill.str());
				//closing game by pressing on keyboard
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
					window.close();

				for (int i = 0; i < maxP; i++)
				{
					sPlat.setPosition(plat[i].x, plat[i].y);
					window.draw(sPlat);
				}

				if (score > enemyScore && player.getPosition().y > (windowWidth / 2)) {
					int  a;
					if (score <= 20000) {
						a = 7000;
					}
					else if (20000 < score <= 40000) {
						a = 5000;
					}
					else if (40000 < score < 80000) {
						a = 4000;
					}
					else {
						a = 3000;
					}

					enemyScore += a;

					enemyState = 1;
					pEnemy[0].x = rand() % (windowWidth - doodleWidth);
					pEnemy[0].y = 0;
					/*enemy.setPosition(pEnemy[0].x, pEnemy[0].y-dy);*/
				}

				//ending games

					//game over from hitting enemy


				if ((x + doodleWidth - 10 > enemy.getPosition().x) && (x + 10 < enemy.getPosition().x + enemy.getSize().x)
					&& (y + doodleHeight > enemy.getPosition().y) && (y + doodleHeight < enemy.getPosition().y + enemy.getSize().y) && (dy < 0) && playerstate == 1) {
					enemyHitState = 1;
					playerstate = 0;
					hitEnemySound.play();
					dy = 1;
					dy += 0.3;
					if (dy > 0) {
						fallingSound.play();
					}
					fallingSound.play();

					for (int i = 0; i < maxP; i++)
					{
						plat[i].y = plat[i].y - dy;
					}
					pEnemy[0].y = pEnemy[0].y - dy;
				}

				//game over from hitting the bottom of the window
				else if (player.getPosition().y > windowHeight) {
					enemyMove = 0;
					playerstate = 0;

					if (enemyHitState == 0 && fallingSoundState == 0) {
						fallingSound.play();
						fallingSoundState = 1;
					}

					for (int i = 0; i < maxP; i++)
					{
						plat[i].y = plat[i].y - dy;
					}
					pEnemy[0].y = pEnemy[0].y - dy;
				}
				if (player.getPosition().y > windowHeight) {

					scoreCounting.setPosition((windowWidth / 2) - 50, (windowHeight / 2) - 20);
					scoreCounting.setCharacterSize(30);
					window.draw(scoreCounting);
					playerstate = 0;
				}
				else {
					scoreCounting.setCharacterSize(20);
					scoreCounting.setPosition(15, 0);
				}
				if (playerstate == 0) {
					retryState = 1;
				}
				if (playerstate == 1) {
					window.draw(topScoreCounting);
					window.draw(scoreCounting);
					window.draw(highJump);
				}


				if (retryState == 1 && menuState == 0) {
					gameover.draw(window);
					switch (e.key.code) {
					case Keyboard::Up:
						gameover.moveUp2();
						break;
					case Keyboard::Down:
						gameover.moveDown2();
						break;
					case Keyboard::Return:
						switch (gameover.getPressedItem2()) {
						case 0:
							std::cout << "Play again has been pressed" << std::endl;
							player.setPosition((windowWidth / 2) - 35, windowHeight - 200);
							enemyScore = 15000;
							platScore = 15000;
							itemStack = 3;
							score = 0;
							maxP = 10;

							for (int i = 0; i < maxP; i++)
							{
								sPlat.setPosition(plat[i].x, plat[i].y);
								window.draw(sPlat);
							}


							player.setPosition((windowWidth / 2) - 40, (windowHeight / 2) + 50);
							std::cout << "x: " << player.getPosition().x << std::endl << "y: " << player.getPosition().y << std::endl;

							playerstate = 1;
							retryState = 0;
							break;
						case 1:

							std::cout << "main menu has been pressed " << std::endl << " TEST " << std::endl;
							//std::cout << menuState << retryState<< playerstate << std::endl;

							menuState = 1;
							gamestate = 0;

							break;

						}
						break;
					}

				}

			}

			window.display();
		}


		return 0;
	}

