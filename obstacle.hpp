#pragma once
#include <SFML/Graphics.hpp>
#include "character.hpp"

class obstacle
{
public:
	obstacle();
	void setRestTimer();
	void Rest();
	void startMoving(float speed);
	void Move();
	void setSize(int newWidth, int newHeight);
	int getWidth();
	int getHeight();
	sf::Vector2f getPosition();
	float getdx();
	float getdy();
	int getSelectedSprite();
	int getType();
	sf::Time getRestTime();
	sf::Clock getRestClock();
	void setRestTimeBase(int newRestTimeBase);
	bool isResting();
	~obstacle();
private:
	sf::Vector2f position;
	float dx, dy;
	int selectedSprite;
	int type;	//Building type
	int width, height;
	sf::Time restTime;
	sf::Clock restClock;
	bool resting;
	int restTimeBase;
};