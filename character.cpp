#include "character.hpp"

character::character() :
	position(sf::Vector2f(80, GL - 15)),
	dx(0),
	dy(0),
	height(15),
	jumping(0),
	jumpPower(10)
{
}

void character::Move() {
	position = sf::Vector2f(position.x + dx, position.y + dy);
	if (position.y + (dy + G) < GL) {
		dy += G;
	}
	else {
		position.y = GL;
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

void character::MoveIn() {
	
}

sf::Vector2f character::getPosition() {
	return position;
}

float character::getdx() {
	return dx;
}

float character::getdy() {
	return dy;
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
