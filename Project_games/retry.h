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

		Color darkBlue;
		Color lightGrey;
		Color darkRed;
		Font font;


		Text gameOver;
		Text your;
		Text yourHighScore;
		Text yourName;
		Text presstochange;

		Text choices[max_items_retry];

		RectangleShape Border;
		RectangleShape arrow;
		Texture t;
		Texture tArrow;


};

