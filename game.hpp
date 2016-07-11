#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "character.hpp"
#include "obstacle.hpp"

class game
{
public:
	game();
	void run();
	void over();
	int getScore();
	int getContam();
	int getSpeed();
	int getState();
	void checkCollision();
	~game();
private:
	sf::RenderWindow window;
	sf::RectangleShape rectWindow;
	sf::Font font;
	sf::ContextSettings settings;
	sf::Texture textureMario;
	sf::Texture textureObstacles;
	sf::Sprite spritePlayerChar;
	sf::Sprite spriteTallObstacle1;
	sf::Sprite spriteTallObstacle2;
	sf::Sprite spriteMedObstacle1;
	sf::Sprite spriteMedObstacle2;
	sf::Sprite spriteWideObstacle1;
	sf::Sprite spriteWideObstacle2;

	sf::Vector2i cursorPos;
	sf::Text txtCursorPos;
	std::ostringstream strCursorPos;
	character playerChar;
	obstacle* aObstacles = new obstacle[6];

	sf::Clock upsClock;
	sf::Time accumulator;
	sf::Time ups;

	int lastObstacle;
	int score;
	int scoreCountdown;
	float speed;
	float contam;
	int disabledObst;
	int state;	//Ready, Running, Paused, Over
	bool firstObstStarted;
};

