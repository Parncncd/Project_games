#include <SFML/Graphics.hpp>
#include <time.h>
#include<Windows.h>

#define windowWidth 320
#define windowHeight 512
#define doodleWidth 62
#define doodleHeight 60
using namespace sf;

struct point
{
    int x, y;
};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(windowWidth, windowHeight), "POOPLE JUMP ><");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("images/space-bck.png");
    t2.loadFromFile("new-Normplat_1.png");
    t3.loadFromFile("images/space-right.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);
   
    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        if(plat[i].x)
        plat[i].x = rand() % windowWidth;
        plat[i].y = rand() % windowHeight;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) && sPers.getPosition().x <= windowWidth-doodleWidth)
            
            x += 3; 
            printf("%f\n",sPers.getPosition().x);
        if (Keyboard::isKeyPressed(Keyboard::Left) && sPers.getPosition().x >=0)
            x -= 3;
            printf("%f\n", sPers.getPosition().x);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                Beep(400, 200);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) 
                app.close();

        dy += 0.2;
        y += dy;
        if (y > 500)  dy = -10;

        if (y < h)
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > windowHeight) { plat[i].y = 0; plat[i].x = rand() % windowWidth; }
            }

        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    return 0;
}
