//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include<Windows.h>
//#include<SFML/Audio.hpp>
//#include<sstream>
//#include<iostream>
//#include"Menu.h"
//#include<vector>
//#include"player.h"
//
//
//#define windowWidth 533
//#define windowHeight 800
//#define doodleWidth 62
//#define doodleHeight 60
//#define normPlatWidth 68
//#define normPlatHeight 17
//using namespace sf;
//
//struct point
//{
//	int x, y;
//};
//int main()
//{
//
//	srand(time(0));
//	Clock clock1, clock2;
//
//	RenderWindow window(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
//	window.setFramerateLimit(60);
//
//	//Menu window
//	Menu menu(windowWidth, windowHeight);
//
//
//	//cursor
//	Cursor clickCursor;
//	clickCursor.loadFromSystem(Cursor::Hand);
//
//	//Textures
//	Texture t1, t2, playerTexture, t4;
//	t1.loadFromFile("images/bck.png");
//	t2.loadFromFile("images/new-Normplat_1.png");
//	playerTexture.loadFromFile("images/doodleAnimation.png");
//	t4.loadFromFile("images/enemy1.png");
//	RectangleShape  enemy;
//	enemy.setSize(Vector2f(60, 62)); 
//	enemy.setTexture(&t4);
//	
//	RectangleShape doodle;
//	doodle.setSize(Vector2f(60, 62));
//	
//	//get into player class
//	//Player player(&playerTexture, Vector2u(3, 1), 0.3f, 100.0f);
//	Player player(Vector2f(0.0f, 350.0f));
//
//	//doodle.setTexture(&t3);
//	RectangleShape  bullet;
//	bullet.setSize(Vector2f(5, 10));
//	RectangleShape backGround;
//	backGround.setSize(Vector2f(windowWidth, windowHeight));
//	backGround.setTexture(&t1);
//	std::vector<RectangleShape> enemies;
//
//	bullet.setFillColor(Color::White);
//	Sprite  sPlat(t2); //sPers(t3);
//
//	
//
//
//	//sounds 
//	SoundBuffer s1;
//	s1.loadFromFile("sound/laser.wav");
//	Sound shootEffect;
//	shootEffect.setBuffer(s1);
//	SoundBuffer s2;
//	s2.loadFromFile("sound/jump.wav");
//	Sound jumpEffect;
//	jumpEffect.setBuffer(s2);
//	SoundBuffer s3;
//	s3.loadFromFile("sound/monsterCrash.wav");
//	Sound hitEnemySound;
//	hitEnemySound.setBuffer(s3);
//	SoundBuffer s4;
//	s4.loadFromFile("sound/falling-sound-arcade.wav");
//	Sound fallingSound;
//	fallingSound.setBuffer(s4);
//	SoundBuffer s5;
//	s5.loadFromFile("sound/trampoline.wav");
//	Sound trampolineSound;
//	trampolineSound.setBuffer(s5);
//	SoundBuffer s6;
//	s6.loadFromFile("sound/chomp-monster.wav");
//	Sound killMonSound;
//	killMonSound.setBuffer(s6);
//
//	//text
//	Font font;
//	font.loadFromFile("font/al-seana.ttf");
//	Text scoreCounting, highJump;
//	scoreCounting.setFont(font);
//	scoreCounting.setFillColor(Color::White);
//	scoreCounting.setCharacterSize(20);
//	scoreCounting.setPosition(15, 0);
//	highJump.setFont(font);
//	highJump.setFillColor(Color::Yellow);
//	highJump.setCharacterSize(20);
//	highJump.setPosition(15, 25);
//
//	//platform building
//	point plat[20];
//
//
//	for (int i = 0; i < 5; i++)
//	{
//		plat[i].x = rand() % 252;//252 is the value of windowWidth - platformWidth
//
//		plat[i].y = rand() % (windowHeight / 2);
//	}
//
//	for (int i = 5; i < 10; i++)
//	{
//
//		plat[i].x = rand() % 252;//252 is the value of windowWidth - platformWidth
//
//		plat[i].y = (rand() % windowHeight / 2) + (windowHeight / 2);
//	}
//
//	//init values
//	int x = 100, y = 100, h = 200;
//	float dx = 0, dy = 0;
//	int score = 0;
//	int maxP = 10;
//	int enemyScore = 15000;
//	int platScore = 15000;
//	bool enemyHitState = 0;
//	bool mark = 0;
//	bool fallingSoundState = 0;
//	int gamestate = 0;// 0 : menu || 1: games || 2: ending
//	bool bulletState = 0;
//	bool playerState = 1;
//	int itemStack = 3;// ¨Ó¹Ç¹¤ÃÑé§¡ÒÃãªéÊ¡ÔÅ´Õ´µÑÇ¢Í§µÑÇÅÐ¤Ã
//	bool bull_en_state = 0;
//
//	int bx = x;
//	int by = y;
//
//	//about player 
//	float deltaTime = 0.0f;
//	Clock clock;
//
//
//
//	//RenderGame
//	while (window.isOpen())
//	{
//		deltaTime = clock.restart().asSeconds();
//		Event e;
//		while (window.pollEvent(e))
//		{
//			switch (e.type) {
//			case Event::KeyReleased:
//				switch (e.key.code) {
//				case Keyboard::Up:
//					menu.moveUp();
//					break;
//				case Keyboard::Down:
//					menu.moveDown();
//					break;
//				case Keyboard::Return:
//					switch (menu.getPressedItem()) {
//					case 0:
//						std::cout << "Play has been pressed" << std::endl;
//						gamestate = 1;
//						break;
//					case 1:
//						//leaderboard
//						std::cout << "Leaderboard has been pressed" << std::endl;
//						break;
//					case 2:
//						//how to play
//						std::cout << "How to play has been pressed" << std::endl;
//						break;
//					case 3:
//						std::cout << "Quit has been pressed" << std::endl;
//						window.close();
//						break;
//					}
//					break;
//				}
//				break;
//			case Event::Closed:
//				window.close();
//				break;
//			}
//
//		}
//
//		menu.draw(window);
//
//		if (gamestate == 1) {
//			if (y < h) {
//				dy += 0.2;
//				y += dy;
//				
//			}
//			
//			window.draw(backGround);
//			player.Update();
//			player.move(deltaTime);
//			player.Draw(window);
//		}
//
//
//		window.display();
//
//	}
//
//
//
//	return 0;
//
//}
