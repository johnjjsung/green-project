#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "character.hpp"

class game
{
public:
	game();
	void run();
	void over();
	int getScore();
	int getContam();
	int getGameSpeed();
	int getGameState();
	~game();
private:
	sf::RenderWindow window;
	sf::RectangleShape rectWindow;
	sf::Font font;
	sf::ContextSettings settings;
	sf::Texture textureMario;
	sf::Sprite spritePlayerChar;
	sf::Vector2i cursorPos;
	sf::Text txtCursorPos;
	std::ostringstream strCursorPos;
	character playerChar;

	int score;
	float gameSpeed;
	float contam;
	int gameState;	//Ready, Running, Paused, Over
};

