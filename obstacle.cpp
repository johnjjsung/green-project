#include "obstacle.hpp"

obstacle::obstacle():
	width(),
	height(),
	position(sf::Vector2f(WindowWidth + width, GL - height)),
	restClock(),
	restTime(),
	restTimeBase(8000),
	dx(0),
	dy(0)
{
}

void obstacle::setSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
	position = sf::Vector2f(WindowWidth + width, GL - height);
}

int obstacle::getWidth() {
	return width;
}

int obstacle::getHeight() {
	return height;
}

void obstacle::setRestTimer() {
	restClock.restart();
}
 
void obstacle::setRestTimeBase(int newRestTimeBase) {
	restTimeBase = newRestTimeBase;
}

void obstacle::Rest() {
	position.x = WindowWidth + width;
	dx = 0;
	setRestTimer();
	restTime = sf::milliseconds((rand() % restTimeBase) + 500);
	resting = true;
}

bool obstacle::isResting() {
	return resting;
}

void obstacle::startMoving(float speed) {
	dx = -speed;
	resting = false;
}

void obstacle::Move() {
	position = sf::Vector2f(position.x + dx, position.y + dy);
	if (position.x < -width) {
		Rest();
	}
	//if (restClock.getElapsedTime() > restTime) {
	//	startMoving(5);
	//}
}

sf::Vector2f obstacle::getPosition() {
	return position;
}

float obstacle::getdx() {
	return dx;
}

float obstacle::getdy() {
	return dy;
}

sf::Time obstacle::getRestTime() {
	return restTime;
}

sf::Clock obstacle::getRestClock() {
	return restClock;
}

obstacle::~obstacle()
{
}