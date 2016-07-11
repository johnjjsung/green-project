#include "mountain.hpp"


mountain::mountain() :
	width(),
	height(),
	position(sf::Vector2f(WindowWidth + width, GL - height)),
	restClock(),
	restTime(),
	dx(0),
	dy(0)
{
}

void mountain::setRestTimer() {
	restClock.restart();
}

void mountain::Rest() {
	position.x = WindowWidth + width;
	dx = 0;
	setRestTimer();
	restTime = sf::milliseconds((rand() % 8000) + 500);
	resting = true;
}

sf::Time mountain::getRestTime() {
	return restTime;
}

sf::Clock mountain::getRestClock() {
	return restClock;
}

bool mountain::isResting() {
	return resting;
}

void mountain::startMoving(float speed) {
	dx = -speed;
	resting = false;
}

void mountain::Move() {
	position = sf::Vector2f(position.x + dx, position.y + dy);
	if (position.x < -width) {
		Rest();
	}
}

sf::Vector2f mountain::getPosition() {
	return position;
}

void mountain::setSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
	position = sf::Vector2f(WindowWidth + width, GL - height);
}

int mountain::getWidth() {
	return width;
}

int mountain::getHeight() {
	return height;
}

mountain::~mountain()
{
}
