#include <SFML/Graphics.hpp>
#include <time.h>
#include<Windows.h>
#include<SFML/Audio.hpp>
#include<sstream>
#include<iostream>

#define windowWidth 320
#define windowHeight 512
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
    Clock clock1,clock2;

    RenderWindow games(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
    games.setFramerateLimit(60);

    //Textures
    Texture t1, t2, t3,t4;
    t1.loadFromFile("images/space-bck.png");
    t2.loadFromFile("images/new-Normplat_1.png");
    t3.loadFromFile("images/space-right.png");
    t4.loadFromFile("images/enemy1.png");
    RectangleShape enemy,bullet;
    enemy.setSize(Vector2f(60,62));
    bullet.setSize(Vector2f(5, 10)); 
    enemy.setTexture(&t4);
    bullet.setFillColor(Color::White);
    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    
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

    //text
    Font font;
    font.loadFromFile("font/al-seana.ttf");
    Text scoreCounting,highJump;
    scoreCounting.setFont(font); 
    scoreCounting.setFillColor(Color::White); 
    scoreCounting.setCharacterSize(20); 
    scoreCounting.setPosition(15, 0); 
    highJump.setFont(font);
    highJump.setFillColor(Color::Yellow);
    highJump.setCharacterSize(20);
    highJump.setPosition(15, 25);

        //platform building
    point plat[20];
    point pEnemy[3];
    for (int i = 0; i < 2; i++) {
        pEnemy[i].x = rand() % 252;//252 is the value of windowWidth - platformWidth
    }
    for (int i = 0; i < 5; i++)
    {
        plat[i].x = rand() % 252 ;//252 is the value of windowWidth - platformWidth
        
        plat[i].y = rand() % (windowHeight/2);
    }

    for (int i = 5; i < 10; i++)
    {
   
        plat[i].x = rand() % 252;//252 is the value of windowWidth - platformWidth

        plat[i].y =( rand() % windowHeight/2)+(windowHeight/2);
    }

    //init values
    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    int score=0;
    int maxP = 10;
    int enemyScore = 15000;
    int platScore = 15000;
    bool enemyHitState = 0;
    bool mark = 0;
    bool fallingSoundState = 0;
    bool gamestate = 1;
    bool bulletState = 0;
    int itemStack=3;// จำนวนครั้งการใช้สกิลดีดตัวของตัวละคร
    bool bull_en_state = 0;

    int bx = x;
    int by = y;
    //start point
    sPers.setPosition((windowWidth - doodleWidth) / 2, windowHeight - normPlatHeight-doodleHeight);
    sPlat.setPosition((windowWidth - doodleWidth) / 2,windowHeight-normPlatHeight );
   
    //RenderGame
    while (games.isOpen())
    {
        
        Event e;
        while (games.pollEvent(e))
        {
            if (e.type == Event::Closed)
                games.close();
        }

        Time elapsed1 = clock1.getElapsedTime();
        Time elapsed2 = clock2.getElapsedTime();
        //Key input
        if (gamestate == 1) {
            if (Keyboard::isKeyPressed(Keyboard::Key::D) && sPers.getPosition().x <= windowWidth - doodleWidth) {
                x += 5;
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::A) && sPers.getPosition().x >= 0) {
                x -= 5;
            }
            if (elapsed1.asSeconds() > 0.3) {
                clock1.restart();
                if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
                    shootEffect.play();
                    bullet.setPosition(sPers.getPosition().x, sPers.getPosition().y - 5);
                    bulletState = 1;
                } 
            }
            if (elapsed2.asSeconds() > 0.7) {
                clock2.restart();
                if (Keyboard::isKeyPressed(Keyboard::Key::W) && sPers.getPosition().y >= 200
                    && gamestate == 1 && sPers.getPosition().y <= windowWidth + doodleWidth && itemStack > 0) {
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
                if (mark == 1) {
                    pEnemy[0].y = pEnemy[0].y - dy;
                }
                for (int i = 0; i < 10; i++)
                {
                    y = h;
                    plat[i].y = plat[i].y - dy;
                    
                    if (plat[i].y > windowHeight) {
                        plat[i].y = 0; 
                        plat[i].x = rand() % 252;
                    }
                    score -= dy;

                        //counting score on screen
                        std::stringstream ss;
                        ss << "score: " << score << "\n";
                        scoreCounting.setString(ss.str());
                }
            }
            if (score > platScore) {
                platScore += 15000;
                maxP--;
                printf(">>>>>>>>>  %d   <<<<<<<", maxP);

            }
        // if player step on platform, 
        for (int i = 0; i < maxP; i++) 
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
            && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)&&gamestate==1) {
               jumpEffect.play();
                   dy = -10;
            }
        sPers.setPosition(x, y);
        enemy.setPosition(pEnemy[0].x, pEnemy[0].y);
        games.draw(sBackground);
        if (gamestate == 1) {
            games.draw(scoreCounting);
            games.draw(highJump);
        }
       
        games.draw(sPers);
        if (mark==1) {
            games.draw(enemy);
        }
        //bullet moving
        if (bulletState == 1) {
            bullet.setPosition(sPers.getPosition().x+30, by);
            games.draw(bullet);
            by -= 30;
            
        }
        if (bullet.getPosition().y <= 0) {
            bulletState = 0;
            by = sPers.getPosition().y;
        }
        //bullet hitting enemy
        if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())&&bull_en_state==0) {
            bulletState = 0;
            mark = 0;
            bull_en_state = 1;//bull_en_state คือ สถานะการชนกันของbullet กับ enemy
        }
        //อันนี้คือลองเขียนว่า ถ้าbullet กับ enemy ทับกันแล้วให้ใช้skillเพิ่มได้1ครั้ง แต่ยังไม่สามารถแก้บัคที่ว่า เวลามันทับกันแล้ว skill left ไม่ได้เพิ่มแค่1
        if (bull_en_state == 1) {
            itemStack++;
            bull_en_state = 0;
        }
        std::stringstream skill;
        skill << "Skill left: " << itemStack << "\n";
        highJump.setString(skill.str());
        //closing game by pressing on keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
            games.close();

        for (int i = 0; i < maxP; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            games.draw(sPlat);
        }
      
        if (score >enemyScore&&sPers.getPosition().y>(windowWidth/2)) {
            int  a;
            if (score <= 20000) {
                a = 15000;
            }
            else if (20000 < score <= 40000) {
                a = 10000;
            }
            else if (40000 < score < 60000) {
                a = 7000;
            }
            else {
                a = 5000;
            }

            enemyScore +=a ;

            mark = 1;
            pEnemy[0].x = rand() % 252;
            pEnemy[0].y = 0;
            /*enemy.setPosition(pEnemy[0].x, pEnemy[0].y-dy);*/
        }
        //ending games

            //game over from hitting enemy
        //still can't fix the bug
        if (sPers.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            //pEnemy[0].y = pEnemy[0].y - 2*dy;
            enemyHitState = 1;
            gamestate = 0;
            hitEnemySound.play();
            dy = 1;
            dy += 0.3;
            if (dy > 0) {
                fallingSound.play();
            }
            //fallingSound.play();
            
            for (int i = 0; i < maxP; i++)
            {
                plat[i].y = plat[i].y - dy;
            }
            
        }
        //game over from hitting the bottom of the window
        else if (sPers.getPosition().y > windowHeight + doodleHeight) {
            gamestate = 0;
            if (enemyHitState == 0&&fallingSoundState==0) {
                fallingSound.play();
                fallingSoundState = 1;
            }

            for (int i = 0; i < maxP; i++)
            {
                plat[i].y = plat[i].y - dy;
            }
            pEnemy[0].y = pEnemy[0].y - dy;
        }
        if (sPers.getPosition().y > windowHeight + 2) {
            /*for (int h = 250; h >= 10; h-dy) {
                scoreCounting.setPosition(100, h);
            }*/
            scoreCounting.setPosition(100, 250);
            scoreCounting.setCharacterSize(30);
            games.draw(scoreCounting);
            
        }
        //games.draw(endingScore);
        games.display();
    }


    return 0;
}
