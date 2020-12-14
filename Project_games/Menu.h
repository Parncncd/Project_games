#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/Color.hpp>
#include<iostream>
#define max_items 4
using namespace sf;
class Menu
{
public: Menu(float width, float height);
	  ~Menu();
	  void draw(RenderWindow& window);

	  void moveUp();
	  void moveDown();
	  int getPressedItem() { return selectedItem; }
private:
	int selectedItem = 0;
	Font font;
	Text menu[max_items];
	Text direction1;//press 
	Text direction2;//to choose
	Text enter_direction;//enter
	Text direction3;//press
	Text direction4;//to move up/move down
	Color darkBlue;
	Color lightGrey;

	RectangleShape background;
	RectangleShape KeyUpDown;
	RectangleShape gamename;
	RectangleShape border;

	Texture t;
	Texture tKeyUpDown;
	Texture tgamename;
	Texture tborder;
};

