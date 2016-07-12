#include "character.hpp"

character::character() :
	position(sf::Vector2f(80, GL - height)),
	dx(0),
	dy(0),
	width(29),
	height(30),
	jumping(0),
	jumpPower(10)
{
}

void character::Move() {
	position = sf::Vector2f(position.x + dx, position.y + dy);
	if (position.y + (dy + G) < GL - height) {
		dy += G;
	}
	else {
		position.y = GL - height;
		dy = 0;
		Land();
	}
}

void character::Jump() {
	if (jumping) {
		if (dy < 0) {
			if (jumpPower > 0) {
				jumpPower -= 1;
				dy -= 1;
			}
		}
	}
	else {
		dy -= 12;
		jumping = 1;
	}
}

void character::Land() {
	dy = 0;
	jumping = 0;
	jumpPower = 10;
}

sf::Vector2f character::getPosition() {
	return position;
}

void character::setPosition(int newx, int newy) {
	position = sf::Vector2f(newx, newy);
}

void character::setdy(float newdy) {
	dy = newdy;
}

float character::getdx() {
	return dx;
}

float character::getdy() {
	return dy;
}

void character::setSize(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;
}

float character::getWidth() {
	return width;
}

float character::getHeight() {
	return height;
}

int character::getSelectedSprite() {
	return selectedSprite;
}

bool character::isRunning() {
	return running;
}

bool character::isJumping() {
	return jumping;
}

character::~character()
{
}
