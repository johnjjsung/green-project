#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "character.hpp"
#include "obstacle.hpp"
#include "mountain.hpp"

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
	sf::RectangleShape rectSky;
	sf::RectangleShape rectGround;
	sf::Font font;
	sf::ContextSettings settings;
	sf::Texture textureMario;
	sf::Texture textureObstacles;
	sf::Texture textureMountains;

	sf::Sprite spritePlayerChar;

	sf::Sprite spriteTallObstacle1;
	sf::Sprite spriteTallObstacle2;
	sf::Sprite spriteMedObstacle1;
	sf::Sprite spriteMedObstacle2;
	sf::Sprite spriteWideObstacle1;
	sf::Sprite spriteWideObstacle2;

	sf::Sprite spriteMountain1;
	sf::Sprite spriteMountain2;
	sf::Sprite spriteMountain3;
	sf::Sprite spriteMountain4;
	sf::Sprite spriteMountain1_contam1;
	sf::Sprite spriteMountain2_contam1;
	sf::Sprite spriteMountain3_contam1;
	sf::Sprite spriteMountain4_contam1;
	sf::Sprite spriteMountain1_contam2;
	sf::Sprite spriteMountain2_contam2;
	sf::Sprite spriteMountain3_contam2;
	sf::Sprite spriteMountain4_contam2;

	sf::Text txtScore;
	std::ostringstream strScore;
	character playerChar;
	obstacle* arObstacles = new obstacle[6];
	mountain* arMountains = new mountain[12];

	sf::Clock upsClock;
	sf::Time accumulator;
	sf::Time ups;

	int lastObstacle;
	int score;
	int scoreCountdown;
	float speed;
	float contam;
	int disabledObst;
	int state;	//Ready, Running, Over
	int countMountainTexture;
};

