#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics/Color.hpp>
#include <time.h>
#include<Windows.h>
#include<sstream>
#include<iostream>
#include<fstream>
#include <string>
#include<utility>
#include<algorithm>
#include<vector>
#include"Menu.h"
#include"retry.h"
#include"random.h"

#define windowWidth 530
#define windowHeight 680
#define doodleWidth 62
#define doodleHeight 60
#define normPlatWidth 68
#define normPlatHeight 17

using namespace sf;
using namespace std;


struct point
{
	int x, y;
};
void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font);

int main()
{
	srand(time(0));
	Clock clock1;//clock of s
	Clock clock2;// clock of w
	RenderWindow window(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
	window.setFramerateLimit(60);
	window.setPosition(Vector2i(400, 0));

	Image icon;

	if (!icon.loadFromFile("images/settedIcon.png")) {

	}
	window.setIcon(30, 30, icon.getPixelsPtr());



	//Menu window
	Menu menu(windowWidth, windowHeight);



	//retry window
	gameover gameover(windowWidth, windowHeight);

	//random value
	Random random;


	//cursor
	window.setMouseCursorVisible(true);
	Cursor clickCursor;
	clickCursor.loadFromSystem(Cursor::Hand);

	//scoreboard [trying]
	FILE* fp;
	char temp[255];
	int sc[6];
	string name[6];
	vector <pair<int, string>> userScore;
	fp = fopen("./scoreBoard.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &sc[i]);
		userScore.push_back(make_pair(sc[i], name[i]));
		//cout << temp << " " << score;
	}

	userScore.push_back(make_pair(sc[5], name[5]));
	sort(userScore.begin(), userScore.end());
	fclose(fp);
	fopen("./scoreBoard.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		strcpy(temp, userScore[i].second.c_str());
		fprintf(fp, "%s %d\n", temp, userScore[i].first);
	}
	fclose(fp);

	//Textures
	Texture t1;//background Texture
	t1.loadFromFile("images/bck.png");
	Sprite sBackground(t1);

	Texture t2;//platformTexture
	t2.loadFromFile("images/new-Normplat_1.png");
	Sprite sPlat(t2);

	Texture t3;//doodle texture
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
	int enemySizeX = enemy.getSize().x;
	int enemySizeY = enemy.getSize().y;

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
	SoundBuffer s8;
	s8.loadFromFile("sound/VOLUME_collect.wav");
	Sound chooseEffect;
	chooseEffect.setBuffer(s8);


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

	Text pause;
	pause.setFont(font);
	pause.setFillColor(Color::Black);
	pause.setCharacterSize(50);
	pause.setString("PAUSE");
	pause.setOrigin(pause.getLocalBounds().width / 2, pause.getLocalBounds().height / 2);



	point pEnemy[2];
	for (int i = 0; i < 2; i++) {
		pEnemy[i].x = rand() % (windowWidth - enemySizeX);
	}
	pEnemy[0].y = 0;

	//platform building
	point plat[20];
	// set initial points of the platform


	for (int i = 0; i <= 10; i += 2) {

		//plat[i].x= random.generateRandom(0, windowWidth / 2);
		plat[i].x = rand() % (windowWidth / 2);

	}

	for (int i = 1; i <= 11; i += 2) {
		plat[i].x = rand() % ((windowWidth / 2) - (t2.getSize().x)) + ((windowWidth / 2));
	}
	plat[12].x = (windowWidth / 2) - (t2.getSize().x / 2);
	plat[0].y = random.generateRandom(73, 90);
	plat[1].y = random.generateRandom(107, 127);
	plat[2].y = random.generateRandom(144, 164);
	plat[3].y = random.generateRandom(204, 230);
	plat[4].y = random.generateRandom(260, 300);
	plat[5].y = random.generateRandom(330, 380);
	plat[6].y = random.generateRandom(410, 430);
	plat[7].y = random.generateRandom(455, 485);
	plat[8].y = random.generateRandom(510, 530);
	plat[9].y = random.generateRandom(547, 567);
	plat[10].y = random.generateRandom(590, 607);
	plat[11].y = random.generateRandom(620, 640);
	plat[12].y = windowHeight - t2.getSize().y - 2;





	//init values
	int h = (windowHeight / 2) - 50;
	int x = windowWidth / 2 - (doodleWidth / 2);
	int  y = h;
	float dx = 0, dy = 0;
	int score = 0;
	int maxP = 13;
	int enemyScore = (rand() % 500) + 1000;
	int platScore = 1500;
	bool enemyHitState = 0;
	bool enemyState = 0;
	bool fallingSoundState = 0;
	bool playerstate = 1;
	bool bulletState = 0;
	int itemStack = 3;
	bool bull_en_state = 0;
	bool gamestate = 0;
	bool retryState = 0;
	bool menuState = 1;
	bool enemyGoRight = 1;
	bool enemyMove = 1;
	bool playAgainState = 0;
	bool pauseState = 0;
	bool playerMoveState = 1;//control the player setting position, if player moves, this state will be 1

	int bx = x;
	int by = y;


	//start point
	player.setPosition((windowWidth - doodleWidth) / 2, windowHeight - normPlatHeight - doodleHeight);

	//RenderGame
	while (window.isOpen())
	{
		cout << "pausestate: " << pauseState << " " << " ,y: " << y << " " << endl;

		if (menuState == 1) {
			retryState = 0;
			menu.draw(window);
			gamestate = 0;
		}

		if (retryState == 1) {
			menuState = 0;

		}



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
							chooseEffect.play();
							std::cout << "Play has been pressed" << std::endl;
							gamestate = 1;
							menuState = 0;

							break;
						case 1:
							//how to play
							chooseEffect.play();
							std::cout << "How to play has been pressed" << std::endl;
							break;
						case 2:
							//leaderboard
							chooseEffect.play();

							std::cout << "Leaderboard has been pressed" << std::endl;

							break;
						case 3:
							std::cout << "Quit has been pressed" << std::endl;
							chooseEffect.play();

							window.close();
							break;
						}
					}



					break;
				case Keyboard::Escape:
					window.close();
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}

		}



		if (gamestate == 1) {

			window.draw(sBackground);

			for (int i = 0; i <= maxP && playerMoveState == 1; i++)
			{
				sPlat.setPosition(plat[i].x, plat[i].y);
				window.draw(sPlat);
			}

			//bullet moving
			if (bulletState == 1) {
				bullet.setPosition(player.getPosition().x + 35, by);
				window.draw(bullet);
				by -= 40;

			}
			if (enemyState == 1&&pauseState==0) {
				window.draw(enemy);
			}

			Time elapsed1 = clock1.getElapsedTime();
			Time elapsed2 = clock2.getElapsedTime();
			//Time elapsed3 = clock3.getElapsedTime();

			//Key input
			if (playerstate == 1) {

				if (Keyboard::isKeyPressed(Keyboard::Key::P) && pauseState == 0) {
					chooseEffect.play();
					pauseState = 1;
					playerMoveState = 0;
					playerstate = 0;
				}

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
				if (elapsed2.asSeconds() > 0.3) {
					clock2.restart();
					if (Keyboard::isKeyPressed(Keyboard::Key::W) && player.getPosition().y >= 200
						&& playerstate == 1 && player.getPosition().y <= windowWidth + doodleWidth && itemStack > 0) {
						trampolineSound.play();
						itemStack--;
						dy = -15;
					}
				}
			}
			if (pauseState == 1) {
				enemyMove = 0;
				pause.setPosition(windowWidth / 2, windowHeight / 2);
				window.draw(pause);
				if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
					chooseEffect.play();
					enemyMove = 1;
					playerstate = 1;
					playerMoveState = 1;
					pauseState = 0;
				}
			}
			else {
				pause.setPosition(0,0);
			}

			//Gravity
			if (playerMoveState == 1&&y<=3000) {
				dy += 0.2;// dy is used like an acceleration. When +, player moves down, when -, player moves up 
				y += dy;// changing y value of player by plus dy. This is to make player move down
			}


			//create new platform when doodle step on higher platform

			if (y < h) {
				if (enemyState == 1) {
					pEnemy[0].y = pEnemy[0].y - 1.5 * dy;
				}
				for (int i = 0; i <= maxP; i++)
				{
					y = h;
					plat[i].y = plat[i].y - 1.5 * dy;
					if (score > platScore && plat[maxP].y <= 0) {
						if (score <= 5500) {
							platScore += 1500;
						}
						else {
							platScore += 1000;

						}


						maxP--;
						printf(">>>>>>>>>  %d   <<<<<<<\n", maxP);

					}
					if (plat[i].y > windowHeight) {
						plat[i].y = 0;
						if (i % 2 == 0) {
							plat[i].x = random.generateRandom(0, windowWidth / 2);
						}
						else {
							plat[i].x = random.generateRandom((windowWidth / 2) + normPlatWidth, windowWidth - normPlatWidth);
						}
					}


				}

				score -= dy;//score counting
			}

			//counting score on screen
			std::stringstream ss;
			ss << "SCORE: " << score << "\n";
			scoreCounting.setString(ss.str());

			//player step(jump) on mon
			if ((x + doodleWidth - 10 > enemy.getPosition().x) && (x + 10 < enemy.getPosition().x + enemy.getSize().x)
				&& (y + doodleHeight > enemy.getPosition().y) && (y + doodleHeight < enemy.getPosition().y + enemy.getSize().y) && (dy > 0) && playerstate == 1 && enemyState == 1) {

				stepOnMonSound.play();
				dy = -15;
				pEnemy[0].y += 1000;
				pEnemy[0].x += windowWidth;


			}

			if (pEnemy[0].y > windowHeight) {
				pEnemy[0].x = random.generateRandom(0, windowWidth - enemySizeX);
				pEnemy[0].y = 0;
				enemyState = 0;
			}


			// if player step on platform, 
			for (int i = 0; i <= maxP; i++)
				if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
					&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0) && playerstate == 1) {
					jumpEffect.play();
					dy = -10;
					/*enemyState = 0;
					enemy.setPosition(windowWidth + 500, y);*/
				}
			if (playerMoveState == 1) {

				player.setPosition(x, y);

			}
			else {
				player.setPosition(player.getPosition().x, player.getPosition().y);
			}


			if (enemy.getPosition().y >= -1 && enemy.getPosition().y <= windowHeight) {

				enemy.setPosition(pEnemy[0].x, pEnemy[0].y);
			}

			if (enemyState == 1 && playerMoveState == 1) {
				enemy.setPosition(pEnemy[0].x, pEnemy[0].y);
			}

			if (playerstate == 0) {
				enemyMove = 0;
			}
			else if (playerstate == 1 && playerMoveState == 1) {
				enemyMove = 1;
			}

			if (enemyState == 1 && enemyMove == 1)
			{
				if (enemyGoRight == 1) {
					pEnemy[0].x += 3;
					if (pEnemy[0].x >= windowWidth - enemy.getSize().x) {
						enemyGoRight = 0;
					}
				}
				if (enemyGoRight == 0) {
					pEnemy[0].x -= 3;
					if (pEnemy[0].x <= 0) {
						enemyGoRight = 1;
					}
				}
			}
			if (pauseState != 1) {

			window.draw(player);
			}


			if (bullet.getPosition().y <= 0) {
				bulletState = 0;
				by = player.getPosition().y;
			}
			//bullet hitting enemy
			if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()) && bull_en_state == 0 && enemyState == 1 && bulletState == 1) {
				//enemy.setPosition(windowWidth + 50, windowHeight - 100);
				pEnemy[0].x = 1000;
				pEnemy[0].y = y;
				bull_en_state = 1;
			}

			if (bull_en_state == 1 && enemyState == 1) {
				itemStack++;
				killMonSound.play();
				enemyState = 0;
				bulletState = 0;
				bull_en_state = 0;
			}
			std::stringstream skill;
			skill << "SKILL LEFT: " << itemStack << "\n";
			highJump.setString(skill.str());


			if (score > enemyScore && player.getPosition().y > (windowWidth / 2) && playerstate == 1) {
				int  a;
				if (score <= 5000) {
					a = 2000;
				}
				else if (5000 < score <= 10000) {
					a = 1800;
				}
				else if (10000 < score < 20000) {
					a = 1500;
				}
				else {
					a = 1000;
				}

				enemyScore += a;

				enemyState = 1;
				pEnemy[0].x = rand() % (windowWidth - doodleWidth);
				pEnemy[0].y = 0;
				/*enemy.setPosition(pEnemy[0].x, pEnemy[0].y-dy);*/
			}

			//ending games

			if ((x + doodleWidth - 10 > enemy.getPosition().x) && (x + 10 < enemy.getPosition().x + enemy.getSize().x)
				&& (y + doodleHeight > enemy.getPosition().y) && (y + doodleHeight < enemy.getPosition().y + enemy.getSize().y) && (dy < 0) && playerstate == 1) //game over from hitting enemy
			{
				enemyHitState = 1;
				enemyMove = 0;

				hitEnemySound.play();
				dy = 1;
				dy += 0.3;
				if (dy > 0) {
					fallingSound.play();
				}

				for (int i = 0; i <= maxP; i++)
				{
					plat[i].y = plat[i].y - 1.5 * dy;
				}
				pEnemy[0].y = pEnemy[0].y - 1.5 * dy;


				playerstate = 0;
			}

			//game over from hitting the bottom of the window
			else if (player.getPosition().y > windowHeight) {

				if (enemyHitState == 0 && fallingSoundState == 0) {
					fallingSound.play();
					fallingSoundState = 1;
				}

				for (int i = 0; i <= maxP; i++)
				{
					plat[i].y = plat[i].y - 1.5 * dy;
				}
				pEnemy[0].y = pEnemy[0].y - 1.5 * dy;
				enemyMove = 0;
				enemyState = 0;
				playerstate = 0;
			}
			if (player.getPosition().y > windowHeight) {

				playerstate = 0;
			}
			else {
				scoreCounting.setCharacterSize(20);
				scoreCounting.setPosition(15, 0);
			}
			if (playerstate == 0 && (player.getPosition().y > windowHeight)) {
				menuState = 0;
				playAgainState = 1;
				retryState = 1;
				scoreCounting.setPosition((windowWidth / 2) - 50, (windowHeight / 2) - 20);
				scoreCounting.setCharacterSize(30);
				window.draw(scoreCounting);
				showHighScore(10, 10, "HIGHSCORE", window, &font);
				showHighScore(10, 40, userScore[5].second, window, &font);
				showHighScore(100, 40, to_string(userScore[5].first), window, &font);
			}
			if (playerstate == 1&&pauseState==0) {
				window.draw(topScoreCounting);
				window.draw(scoreCounting);
				window.draw(highJump);
			}


			if (retryState == 1/* && menuState == 0 && playerstate == 0 && playAgainState == 1*/) {


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
						chooseEffect.play();


						scoreCounting.setCharacterSize(20);
						scoreCounting.setPosition(15, 0);

						score = 0;
						maxP = 13;
						enemyScore = (rand() % 500) + 1000;
						platScore = 1500;
						enemyHitState = 0;
						enemyState = 0;
						fallingSoundState = 0;

						bulletState = 0;
						itemStack = 3;
						bull_en_state = 0;

						enemyGoRight = 1;
						enemyMove = 0;

						// set initial points of the platform


						for (int i = 0; i <= 10; i += 2) {

							plat[i].x = rand() % (windowWidth / 2);

						}

						for (int i = 1; i <= 11; i += 2) {
							plat[i].x = rand() % ((windowWidth / 2) - (t2.getSize().x)) + ((windowWidth / 2));
						}
						plat[12].x = (windowWidth / 2) - (t2.getSize().x / 2);
						plat[0].y = random.generateRandom(73, 90);
						plat[1].y = random.generateRandom(107, 127);
						plat[2].y = random.generateRandom(144, 164);
						plat[3].y = random.generateRandom(204, 230);
						plat[4].y = random.generateRandom(260, 300);
						plat[5].y = random.generateRandom(330, 380);
						plat[6].y = random.generateRandom(410, 430);
						plat[7].y = random.generateRandom(455, 485);
						plat[8].y = random.generateRandom(510, 530);
						plat[9].y = random.generateRandom(547, 567);
						plat[10].y = random.generateRandom(590, 607);
						plat[11].y = random.generateRandom(620, 640);
						plat[12].y = windowHeight - t2.getSize().y - 2;

						pEnemy[0].x = rand() % (windowWidth - enemySizeX);
						pEnemy[0].y = 0;

						x = windowWidth / 2 - (doodleWidth / 2);
						y = h;
						playerstate = 1;
						retryState = 0;
						playAgainState = 0;
						break;
					case 1:
						chooseEffect.play();

						std::cout << "main menu has been pressed " << std::endl;
						scoreCounting.setCharacterSize(20);
						scoreCounting.setPosition(15, 0);


						score = 0;
						maxP = 13;
						enemyScore = (rand() % 500) + 1000;
						platScore = 1500;
						enemyHitState = 0;
						enemyState = 0;
						fallingSoundState = 0;

						bulletState = 0;
						itemStack = 3;
						bull_en_state = 0;

						//menuState = 1;
						enemyGoRight = 1;
						enemyMove = 0;
						pEnemy[0].x = rand() % (windowWidth - enemySizeX);
						pEnemy[0].y = 0;
						// set initial points of the platform


						for (int i = 0; i <= 10; i += 2) {

							plat[i].x = rand() % (windowWidth / 2);

						}

						for (int i = 1; i <= 11; i += 2) {
							plat[i].x = rand() % ((windowWidth / 2) - (t2.getSize().x)) + ((windowWidth / 2));
						}
						plat[12].x = (windowWidth / 2) - (t2.getSize().x / 2);
						plat[0].y = random.generateRandom(73, 90);
						plat[1].y = random.generateRandom(107, 127);
						plat[2].y = random.generateRandom(144, 164);
						plat[3].y = random.generateRandom(204, 230);
						plat[4].y = random.generateRandom(260, 300);
						plat[5].y = random.generateRandom(330, 380);
						plat[6].y = random.generateRandom(410, 430);
						plat[7].y = random.generateRandom(455, 485);
						plat[8].y = random.generateRandom(510, 530);
						plat[9].y = random.generateRandom(547, 567);
						plat[10].y = random.generateRandom(590, 607);
						plat[11].y = random.generateRandom(620, 640);
						plat[12].y = windowHeight - t2.getSize().y - 2;


						x = windowWidth / 2 - (doodleWidth / 2);
						y = h;
						playAgainState = 0;
						playerstate = 1;
						menuState = 1;
						/*retryState = 0;
						gamestate = 0;*/


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

void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}