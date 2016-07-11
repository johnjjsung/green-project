#pragma once
#include <SFML/Graphics.hpp>
#include "Header.hpp"

class mountain
{
public:
	mountain();
	void setRestTimer();
	void Rest();
	sf::Time getRestTime();
	sf::Clock getRestClock();
	bool isResting();
	void startMoving(float speed);
	void Move();
	sf::Vector2f getPosition();
	void setSize(int newWidth, int newHeight);
	int getWidth();
	int getHeight();
	~mountain();
private:
	sf::Vector2f position;
	float dx, dy;
	int width, height;
	sf::Time restTime;
	sf::Clock restClock;
	bool resting;
};

