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
	Clock clock3;//clock in name
	RenderWindow window(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><",Style::Titlebar|Style::Close);
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

	//color
	Color myblue;
	myblue.r = 204;
	myblue.g = 221;
	myblue.b = 255;

	Color myDarkBlue;
	myDarkBlue.r = 77;
	myDarkBlue.g = 136;
	myDarkBlue.b = 255;
	Color darkBlue;
	darkBlue.b = 60;


	//cursor
	window.setMouseCursorVisible(true);
	Cursor clickCursor;
	clickCursor.loadFromSystem(Cursor::Hand);
	Cursor normalCursor;
	normalCursor.loadFromSystem(Cursor::Arrow);

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
	bool playagain = true;
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

	RectangleShape Textbox;
	Textbox.setSize(Vector2f(115, 30));
	Textbox.setFillColor(myblue);

	RectangleShape okBox;
	okBox.setSize(Vector2f(30, 30));
	okBox.setFillColor(Color::White);

	//go back to last page sprite
	Texture tGoback;
	tGoback.loadFromFile("images/go-back-left-arrow.png");
	RectangleShape goback;
	goback.setTexture(&tGoback);
	goback.setSize(Vector2f(40,40));



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
	scoreCounting.setStyle(Text::Bold);


	Text highJump;
	highJump.setFont(font);
	highJump.setFillColor(Color::Black);
	highJump.setCharacterSize(18);
	highJump.setPosition(15, 25);
	highJump.setStyle(Text::Bold);

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

	Text ok;
	ok.setFont(font);
	ok.setFillColor(Color::Black);
	ok.setCharacterSize(25);
	ok.setString("OK");

	Text scoreboardText;
	scoreboardText.setFont(font);
	scoreboardText.setFillColor(darkBlue);
	scoreboardText.setCharacterSize(40);
	scoreboardText.setString("LEADERBOARD");
	scoreboardText.setStyle(Text::Bold); 
	scoreboardText.setLetterSpacing(2.3);
	scoreboardText.setPosition(150, 40);

	//direction 
	Text direction1;//press 
	Text direction2;//to choose
	Text enter_direction;//enter
	Text direction3;//press
	Text direction4;//to move up/move down
	Texture tKeyUpDown;
	RectangleShape KeyUpDown;
	if (true) {

		tKeyUpDown.loadFromFile("images/arrow_keyboard.png");

	}

	tKeyUpDown.setSmooth(true);
	KeyUpDown.setTexture(&tKeyUpDown);
	KeyUpDown.setSize(Vector2f(tKeyUpDown.getSize().x, tKeyUpDown.getSize().y));
	KeyUpDown.setScale(0.1, 0.1);
	KeyUpDown.setPosition(75, 630);


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
	enter_direction.setFillColor(Color::White);
	enter_direction.setCharacterSize(20);
	enter_direction.setPosition(340, 645);









	

	//name 
	sf::Text name;
	name.setFont(font);
	name.setFillColor(sf::Color::Black);
	name.setPosition((windowWidth / 2) + 40, 380 - 75);
	name.setCharacterSize(30);
	sf::String nameplayer;

	//scoreboard
	sf::RectangleShape board;
	board.setSize(sf::Vector2f(700, 500));
	board.setFillColor(sf::Color::Black);
	board.setPosition(500, 450);
	board.setOrigin(board.getGlobalBounds().width / 2, board.getGlobalBounds().height / 2);

	sf::Text scoreboard;
	scoreboard.setFont(font);
	scoreboard.setString("SCOREBOARD");
	scoreboard.setFillColor(sf::Color::White);
	scoreboard.setCharacterSize(50);
	scoreboard.setPosition(380, 200);



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
	float debounce = 0;
	int score = 0;
	//int cnt = 0;
	float deltatime = 0.0f;
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
	bool changenameState = 0;
	bool enterForPlayAgain = 1;
	bool scoreBoardState = 0;
	bool leaderBoardReadFile = 0;
	bool leaderBoardWriteFile = 0;


	int bx = x;
	int by = y;

Main:
	int cnt = 0;
	Text hname, hscore;
	hscore.setFont(font);
	hscore.setCharacterSize(35);
	hscore.setFillColor(Color::White);
	hname.setFont(font);
	hname.setCharacterSize(35);
	hname.setFillColor(Color::White);

	vector<pair<int, string>> ScoreBoard;
	//start point
	player.setPosition((windowWidth - doodleWidth) / 2, windowHeight - normPlatHeight - doodleHeight);

	//RenderGame
	while (window.isOpen())
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			window.setMouseCursor(clickCursor);
		}
		else {
			window.setMouseCursor(normalCursor);
		}
		//cout << "pausestate: " << pauseState << " " << " ,y: " << y << " " << endl;
		Vector2i mousePosition = Mouse::getPosition(window);
		deltatime = clock3.restart().asSeconds();
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
			/*int i = 0;
			ifstream loadFile;
			loadFile.open("Highscore.txt");*/
			switch (e.type) {
			case Event::KeyReleased:
				switch (e.key.code) {
				case Keyboard::Up:
					if (menuState == 1 && retryState == 0) {
						jumpEffect.play();
						menu.moveUp();
					}
					break;

				case Keyboard::Down:
					if (menuState == 1 && retryState == 0) {
						jumpEffect.play();
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
							//leaderboard
							//read files
						/*	while (!loadFile.eof())
							{
								printf("tidja");
								string tempName;
								int tempScore;
								loadFile >> tempName >> tempScore;
								ScoreBoard.push_back({ tempScore, tempName });
								i++;
							}
							loadFile.close();

							sort(ScoreBoard.begin(), ScoreBoard.end(), greater<pair<int, string>>());*/
							chooseEffect.play();
							scoreBoardState = 1;
							std::cout << "Leaderboard has been pressed" << std::endl;

							break;
						case 2:
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

		//if (leaderBoardReadFile == 1) {
		//	//int i = 0;
		//	//ifstream loadFile;
		//	//loadFile.open("Highscore.txt");
		//	////read files
		//	//while (!loadFile.eof())
		//	//{
		//	//	string tempName;
		//	//	int tempScore;
		//	//	loadFile >> tempName >> tempScore;
		//	//	ScoreBoard.push_back({ tempScore, tempName });
		//	//	i++;
		//	//}
		//	//loadFile.close();

		//	//sort(ScoreBoard.begin(), ScoreBoard.end(), greater<pair<int, string>>());
		//	leaderBoardReadFile = 0;
		//}



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
			if (enemyState == 1 && pauseState == 0) {
				window.draw(enemy);
			}

			Time elapsed1 = clock1.getElapsedTime();
			Time elapsed2 = clock2.getElapsedTime();
			Time elapsed3 = clock3.getElapsedTime();
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
				pause.setPosition(0, 0);
			}

			//Gravity
			if (playerMoveState == 1 && y <= 3000) {
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
					pEnemy[0].x += 3.5;
					if (pEnemy[0].x >= windowWidth - enemy.getSize().x) {
						enemyGoRight = 0;
					}
				}
				if (enemyGoRight == 0) {
					pEnemy[0].x -= 3.5;
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
				scoreCounting.setCharacterSize(18);
				scoreCounting.setPosition(15, 0);
			}
			if (playerstate == 0 && (player.getPosition().y > windowHeight)) {
				menuState = 0;
				playAgainState = 1;
				retryState = 1;
				scoreCounting.setPosition((windowWidth / 2) - 5, (windowHeight / 3) + 14);
				scoreCounting.setCharacterSize(20);
				scoreCounting.setStyle(Text::Bold);
				window.draw(scoreCounting);

			}
			if (playerstate == 1 && pauseState == 0) {
				window.draw(topScoreCounting);
				window.draw(scoreCounting);
				window.draw(highJump);
			}


			if (retryState == 1) {
				
				

				cout << "Change name state : " << changenameState << endl;
				cout << debounce << endl;
				//cout << "Mouse::getPosition(window).x: " << Mouse::getPosition(window).x << "Mouse::getPosition(window).y: " << Mouse::getPosition(window).y << endl;

				if (Mouse::isButtonPressed(Mouse::Button::Left) && Mouse::getPosition(window).x >= 314 && Mouse::getPosition(window).x <= 415 && Mouse::getPosition(window).y >= 310 && Mouse::getPosition(window).y <= 326 && changenameState == 0) {
					cout << "			FUCKKKKKK				";
					changenameState = 1;

				}
				if (Mouse::isButtonPressed(Mouse::Button::Left) && Mouse::getPosition(window).x >= 445 && Mouse::getPosition(window).x <= 475 && Mouse::getPosition(window).y >= 310 && Mouse::getPosition(window).y <= 340 && changenameState == 1) {
					changenameState = 0;
				}
				if (changenameState == 1) {
					Textbox.setFillColor(myblue);
					if (e.type == sf::Event::TextEntered and debounce < clock2.getElapsedTime().asSeconds())
					{

						debounce = clock2.getElapsedTime().asSeconds() + 0.2;
						if (e.text.unicode >= 33 && e.text.unicode <= 126 && nameplayer.getSize() < 8 && e.text.unicode != 44)
						{
							nameplayer += e.text.unicode;

						}
						else if (e.text.unicode == 8)//backspace
						{
							nameplayer = nameplayer.substring(0, nameplayer.getSize() - 1);
						}
						else if (e.text.unicode == 32 && nameplayer.getSize() > 0)//spaceBar
						{

							changenameState = 0;
							enterForPlayAgain = 0;
							goto retry;
						}
						else if (Mouse::isButtonPressed(Mouse::Button::Left)) {

						}


					}
				}

				if (changenameState == 0 and debounce < clock2.getElapsedTime().asSeconds()) {
					Textbox.setFillColor(myDarkBlue);
					//if (elapsed3.asSeconds() > 0.1) {
						//clock3.restart();
						if (Keyboard::isKeyPressed(Keyboard::Enter) && (gameover.getPressedItem2() == 0 || gameover.getPressedItem2() == 1)) {
							//write score
							string name;
							name = nameplayer;
							ofstream highscore;
							highscore.open("Highscore.txt", ios::out | ios::app);
							highscore << "\n" << name << " " << score;
							highscore.close();
							playagain = true;
						}
					//}
				retry:
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
							leaderBoardWriteFile = 1;

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
							debounce = 0;

							////write
							//if (leaderBoardWriteFile == 1) {
							//highscore.open("Highscore.txt", ios::out | ios::app);
							//highscore << "\n" << namewithscore << " " << score ;
							//highscore.close();
							//}
							//leaderBoardWriteFile = 0;

							playerstate = 1;

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
							debounce = 0;


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
							debounce = 0;
							////write
							//highscore.open("Highscore.txt", ios::out | ios::app);
							//highscore << "\n" << namewithscore << " " << score;
							//highscore.close();


							playAgainState = 0;
							playerstate = 1;
							menuState = 1;


							break;

						}
						break;
					}

				}
				if (changenameState == 0 && playerstate == 1 && menuState != 1) {

					retryState = 0;
				}
				gameover.draw(window);


				name.setString(" " + nameplayer);

				Textbox.setPosition((windowWidth / 2) + 40, 380 - 70);
				okBox.setPosition((windowWidth / 2) + 40 + 140, 380 - 70);
				ok.setPosition((windowWidth / 2) + 40 + 140 + 3, 310);
				window.draw(okBox);
				window.draw(ok);
				window.draw(Textbox);
				window.draw(name);
				window.draw(direction1);
				window.draw(direction2);
				window.draw(direction3);
				window.draw(direction4);
				window.draw(KeyUpDown);
				window.draw(enter_direction);

			}

		}
		if (playagain == true) {
			if (Keyboard::isKeyPressed(Keyboard::Enter) && menu.getPressedItem() == 1) {
				int i = 0;
				ifstream loadFile;
				loadFile.open("Highscore.txt");
				while (!loadFile.eof())
				{
					printf("tidja");
					string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					ScoreBoard.push_back({ tempScore, tempName });
					i++;
				}
				loadFile.close();

				sort(ScoreBoard.begin(), ScoreBoard.end(), greater<pair<int, string>>());
				playagain = false;
			}
		}
		if (scoreBoardState == 1) {
			window.clear();
			window.draw(sBackground);
			window.draw(scoreboardText);
			goback.setPosition(5,5);
			window.draw(goback);
			cnt = 0;


			if (Mouse::isButtonPressed(Mouse::Button::Left) && Mouse::getPosition(window).x >= 5 && Mouse::getPosition(window).x <= 45 && Mouse::getPosition(window).y >= 5 && Mouse::getPosition(window).y <= 50 ) {
				
				scoreBoardState = 0;

			}
			for (vector<pair<int, string>>::iterator k = ScoreBoard.begin(); k != ScoreBoard.end(); k = k + 1)
			{
				++cnt;
				if (cnt > 5)
					break;
				cout << cnt << endl;
				hname.setPosition(100, 150 + (50 * cnt));
				hscore.setPosition(350, 150 + (50 * cnt));
				hname.setString(k->second);
				hscore.setString(to_string(k->first));
				window.draw(hname);
				window.draw(hscore);
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
	text.setStyle(Text::Bold);
	text.setPosition(x, y);
	text.setString(word);
	text.setCharacterSize(32);
	window.draw(text);
}