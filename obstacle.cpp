#include "obstacle.hpp"

obstacle::obstacle():
	type(),
	selectedSprite(),
	width(),
	height(),
	position(sf::Vector2f(WindowWidth + width, GL - height)),
	restClock(),
	restTime(),
	dx(0),
	dy(0)
{
}

void obstacle::setSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
	position = sf::Vector2f(WindowWidth + width, GL - height + 15);
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
 
void obstacle::Rest() {
	position.x = WindowWidth + width;
	dx = 0;
	setRestTimer();
	restTime = sf::milliseconds((rand() % 10000) + 500);
}

void obstacle::startMoving(float speed) {
	dx = -speed;
}

void obstacle::Move() {
	position = sf::Vector2f(position.x + dx, position.y + dy);
	if (position.x < -width) {
		Rest();
	}
	if (restClock.getElapsedTime() > restTime) {
		startMoving(5);
	}
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

int obstacle::getSelectedSprite() {
	return selectedSprite;
}

int obstacle::getType() {
	return type;
}

obstacle::~obstacle()
{
}
