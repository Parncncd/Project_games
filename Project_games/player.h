#pragma once
#include <SFML\Graphics.hpp>

class Player
{
public:
	sf::Sprite doodle;

	Player(sf::Vector2f position);
	~Player();

	void Update();
	void Draw(sf::RenderWindow& window);
	void move(float deltatime);

	const sf::Vector2f Posi_dood();
	const sf::Vector2f position() { return doodle.getPosition(); };

	float x = 0;
	float y = 0;
	float dy;


private:
	sf::Texture Texture_dood;
	sf::Vector2f doodPosition;
	float speed = 200;
	sf::Vector2f movement;
};