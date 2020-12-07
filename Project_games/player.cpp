#include "Player.h"

Player::Player(sf::Vector2f position)
{
	Texture_dood.loadFromFile("images/doodleAnimation.png");
	Texture_dood.setSmooth(true);
	doodle.setTexture(Texture_dood);
	doodPosition.x = Texture_dood.getSize().x / 3;
	doodPosition.y = Texture_dood.getSize().y ;
	sf::Vector2f spawnPoint = { 250.f,350.f };
	doodle.setPosition(spawnPoint);
	
	//dy += 0.2;
	//y += dy;
}

Player::~Player()
{

}

void Player::Update()
{
	doodle.setTextureRect(sf::IntRect(doodPosition.x * 2, doodPosition.y * 0, doodPosition.x, doodPosition.y));
	doodle.setScale(0.7, 0.7);
	
}
void Player::Draw(sf::RenderWindow& window)
{
	window.draw(doodle);
}
void Player::move(float deltatime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && doodle.getPosition().x < (533-85))
	{
		x = 2.0;
		doodle.setTextureRect(sf::IntRect(doodPosition.x * 2, doodPosition.y * 0, doodPosition.x, doodPosition.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && doodle.getPosition().x > 0)
	{
		x = -2.0;
		doodle.setTextureRect(sf::IntRect(doodPosition.x * 0, doodPosition.y * 0, doodPosition.x, doodPosition.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && doodle.getPosition().y > 50)
	{
		y = -10.0;
		//doodle.setTextureRect(sf::IntRect(doodPosition.x * 1, doodPosition.y * 1, doodPosition.x, doodPosition.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
	{

		doodle.setTextureRect(sf::IntRect(doodPosition.x * 1, doodPosition.y * 0, doodPosition.x, doodPosition.y));
	}
	/*else {
		dy += 0.2;
		y += dy;
		
	}*/

	movement.x = x * speed * deltatime;
	movement.y = y * speed * deltatime;
	doodle.move(movement);
	x = 0;
	y = 0;
}
const sf::Vector2f Player::Posi_dood()
{
	return sf::Vector2f(doodle.getPosition());
}