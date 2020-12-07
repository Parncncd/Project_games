#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>	
#define max_items_retry 2
using namespace sf;

class gameover
{

	
	public: gameover(float width, float height);
		  ~gameover();
		  void draw(RenderWindow& window);

		  void moveUp2();
		  void moveDown2();
		  int getPressedItem2() { return selectedItem2; }
	private:
		int selectedItem2 = 0;
		Font font;
		Text choices[max_items_retry];
		RectangleShape choice;
		Texture t;


};

