#pragma once
#include<SFML/Graphics.hpp>
#define max_items 4
using namespace sf;
class Menu
{
public: Menu(float width,float height);
	  ~Menu();
	  void draw(RenderWindow& window);
	  void moveUp();
	  void moveDown();
private: 
	int selectedItem=0;
	Font font;
	Text menu[max_items];

};

