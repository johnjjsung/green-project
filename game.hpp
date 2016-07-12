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
	void checkCollision();
	void renderPlayerChar();
	void changeChar();
	void setSpritePosition();
	void renderMountains();
	void renderObstacles();
	~game();
private:
	sf::RenderWindow window;
	sf::RectangleShape rectSky;
	sf::RectangleShape rectGround;
	sf::Font font;
	sf::ContextSettings settings;
	sf::Texture texturePlayerChar;
	sf::Texture textureObstacles;
	sf::Texture textureMountains;

	sf::Sprite spriteMarioWalk1;
	sf::Sprite spriteMarioWalk2;
	sf::Sprite spriteMarioWalk3;
	sf::Sprite spriteMarioJump;

	sf::Sprite spriteQuoteWalk1;
	sf::Sprite spriteQuoteWalk2;
	sf::Sprite spriteQuoteWalk3;
	sf::Sprite spriteQuoteJump1;
	sf::Sprite spriteQuoteJump2;

	sf::Sprite spriteDinoWalk1;
	sf::Sprite spriteDinoWalk2;
	sf::Sprite spriteDinoJump;

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

	character marioWalk1;
	character marioWalk2;
	character marioWalk3;
	character marioJump;

	character quoteWalk1;
	character quoteWalk2;
	character quoteWalk3;
	character quoteJump1;
	character quoteJump2;
	
	character dinoWalk1;
	character dinoWalk2;
	character dinoJump;

	obstacle* arObstacles = new obstacle[6];
	mountain* arMountains = new mountain[12];

	sf::Clock upsClock;
	sf::Time accumulator;
	sf::Time ups;

	int lastObstacle;
	int score;
	int scoreCountdown;
	int highScore;
	int playerSpriteCountdown;
	float speed;
	int contam;
	int disabledObst;
	int state;	//Ready, Running, Over
	int countMountainTexture;
	int restartCountdown;
	bool firstCycleRan;
};

