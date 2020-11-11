#include <SFML/Graphics.hpp>
#include <time.h>
#include<Windows.h>
#include<SFML/Audio.hpp>

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
    Clock clock1;

    RenderWindow games(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
    games.setFramerateLimit(60);

    Texture t1, t2, t3,t4;
    t1.loadFromFile("images/space-bck.png");
    t2.loadFromFile("images/new-Normplat_1.png");
    t3.loadFromFile("images/space-right.png");
    t4.loadFromFile("images/enemy1.png");
    
    RectangleShape enemy;
    enemy.setSize(Vector2f(60,62));
    enemy.setTexture(&t4);
    Sprite sBackground(t1), sPlat(t2), sPers(t3),sEnemy(t4);
    




    //sounds 
    sf::SoundBuffer soundEffect;
    soundEffect.loadFromFile("sound/VOLUME_pistol_shoot.wav");
    sf::Sound shootEffect;
    shootEffect.setBuffer(soundEffect);
    sf::SoundBuffer jumpingSound;
    jumpingSound.loadFromFile("sound/jump.wav");
    sf::Sound jumpEffect;
    jumpEffect.setBuffer(jumpingSound);
    
        //platform building
    point plat[20];

    for (int i = 0; i < 10; i++)
    {
      /*  if(plat[i].x)*/
        plat[i].x = rand() % 252 ;//252 is the value of windowWidth - platformWidth
        plat[i].y = rand() % windowHeight;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;
    int score=0;
    
    //start point
    sPers.setPosition((windowWidth - doodleWidth) / 2, windowHeight - normPlatHeight-doodleHeight);
    sPlat.setPosition((windowWidth - doodleWidth) / 2,windowHeight-normPlatHeight );
    while (games.isOpen())
    {
        Event e;
        while (games.pollEvent(e))
        {
            if (e.type == Event::Closed)
                games.close();
        }

        Time elapsed1 = clock1.getElapsedTime();
     
        
        //Key input
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            x += 3;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Key::A) ) {
            x -= 3;
        }
       /* if (sPers.getPosition().x >= 0 && sPers.getPosition().x <= games.getSize().x)
        {
            sPers.setPosition(x, y);
        }
        else if (sPers.getPosition().x > games.getSize().x)
        {
            sPers.setPosition(0, y);
        }
        else if (sPers.getPosition().x < 0)
        {
            sPers.setPosition(280, y);
        }*/

        
        if (elapsed1.asSeconds() > 0.3) {
            clock1.restart();
            if (/*sf::Mouse::isButtonPressed(sf::Mouse::Left)*/Keyboard::isKeyPressed(Keyboard::Key::S)) {
                shootEffect.play(); 
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) 
                games.close();

       //jumping
        dy += 0.2;// dy is used like an acceleration. When +, player moves down, when -, player moves up 
        y += dy;// changing y value of player by plus dy. This is to make player move down
        //if (y > 500) {
        //    dy = -10;// checking if the player step on bottom of window or not, if he steps on the bottom he goes up
        //    score++;
        //}
            
        //ending games
        if (sPers.getPosition().y > windowHeight+doodleHeight) {
            games.close();
        }
            
        
        //create new platform when doodle step on higher platform
        if (y < h)          
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > windowHeight) {
                    plat[i].y = 0; plat[i].x = rand() % 252; }
            }
        // if player step on platform, 
        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
            && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) {
               jumpEffect.play();
                dy = -10;
                score++;
                printf("%d\n", score);
            }
        sPers.setPosition(x, y);
        sEnemy.setPosition(100, 100);
       
        games.draw(sBackground);
        games.draw(sPers);

        for (int i = 0; i < 10; i++)
        {

            sPlat.setPosition(plat[i].x, plat[i].y);
            games.draw(sPlat);
        }
        games.draw(enemy);
        games.display();
    }

    return 0;
}
