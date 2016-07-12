#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header.hpp"

class character
{
public:
	character();
	void Move();
	void Jump();
	void Land();
	sf::Vector2f getPosition();
	void setPosition(int newx, int newy);
	float getdx();
	float getdy();
	void setSize(int newWidth, int newHeight);
	float getWidth();
	float getHeight();
	int getSelectedSprite();
	bool isRunning();
	bool isJumping();
	~character();
private:
	sf::Vector2f position;
	float dx, dy;
	float width;
	float height;
	float jumpPower;
	int selectedSprite;
	bool running;
	bool jumping;
};

