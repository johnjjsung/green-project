#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
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
	void renderPlayerChar();
	~game();
private:
	sf::RenderWindow window;
	sf::RectangleShape rectSky;
	sf::RectangleShape rectGround;
	sf::Font font;
	sf::ContextSettings settings;
	sf::Texture textuerPlayerChar;
	sf::Texture textureObstacles;
	sf::Texture textureMountains;

	sf::Sprite spriteMarioWalk1;
	sf::Sprite spriteMarioWalk2;
	sf::Sprite spriteMarioWalk3;
	sf::Sprite spriteMarioJump;

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
	character marioWalk1;
	character marioWalk2;
	character marioWalk3;
	character marioJump;
	obstacle* arObstacles = new obstacle[6];
	mountain* arMountains = new mountain[12];

	sf::Clock upsClock;
	sf::Time accumulator;
	sf::Time ups;

	int lastObstacle;
	int score;
	int scoreCountdown;
	int playerSpriteCountdown;
	float speed;
	float contam;
	int disabledObst;
	int state;	//Ready, Running, Over
	int countMountainTexture;
};

