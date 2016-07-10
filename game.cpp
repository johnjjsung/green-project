#include "game.hpp"

game::game() :
	settings(),
	window(sf::VideoMode(WindowWidth, WindowHeight), "SFML", sf::Style::Close, settings),
	rectWindow(sf::Vector2f(WindowWidth, WindowHeight)),
	font(),
	textureMario(),
	spritePlayerChar(textureMario, sf::IntRect(211, 0, 12, 15)),
	playerChar(),
	spriteTallObstacle1(textureObstacles, sf::IntRect(5, 4, 53, 125)),
	spriteTallObstacle2(textureObstacles, sf::IntRect(5, 4, 53, 125)),
	spriteMedObstacle1(textureObstacles, sf::IntRect(83, 40, 47, 89)),
	spriteMedObstacle2(textureObstacles, sf::IntRect(83, 40, 47, 89)),
	spriteWideObstacle1(textureObstacles, sf::IntRect(155, 100, 92, 29)),
	spriteWideObstacle2(textureObstacles, sf::IntRect(155, 100, 92, 29)),
	cursorPos(),
	txtCursorPos(),
	strCursorPos(),
	lastObstacle(),
	upsClock(),
	contam(0),
	disabledObst(42),
	accumulator(sf::Time::Zero),
	ups(sf::seconds(1.f / 60.f))
{
	settings.antialiasingLevel = 4;
	window.setVerticalSyncEnabled(true);
	rectWindow.setFillColor(sf::Color(120, 170, 255));
	if (!font.loadFromFile("ACaslonPro-Regular.otf")) {
		// error
	}
	if (!textureMario.loadFromFile("mario.png")) {
		// error
	}
	if (!textureObstacles.loadFromFile("obstacles.png")) {
		// error
	}
}

void game::run() {
	srand(time(NULL));
	lastObstacle = 0;
	aObstacles[0].setSize(53, 125);
	aObstacles[1].setSize(53, 125);
	aObstacles[2].setSize(47, 89);
	aObstacles[3].setSize(47, 89);
	aObstacles[4].setSize(92, 29);
	aObstacles[5].setSize(92, 29);
	for (int i = 0; i < 6; i++) {
		aObstacles[i].Rest();
	}


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		while (accumulator > ups) {
			accumulator -= ups;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				playerChar.Jump();
			}
			playerChar.Move();
			checkCollision();

			spritePlayerChar.setPosition(playerChar.getPosition());
			spriteTallObstacle1.setPosition(aObstacles[0].getPosition());
			spriteTallObstacle2.setPosition(aObstacles[1].getPosition());
			spriteMedObstacle1.setPosition(aObstacles[2].getPosition());
			spriteMedObstacle2.setPosition(aObstacles[3].getPosition());
			spriteWideObstacle1.setPosition(aObstacles[4].getPosition());
			spriteWideObstacle2.setPosition(aObstacles[5].getPosition());

			for (int i = 0; i < 6; i++) {
				aObstacles[i].Move();
				if (aObstacles[i].getRestClock().getElapsedTime() > aObstacles[i].getRestTime()) {
					if (aObstacles[lastObstacle].getPosition().x < 500 || aObstacles[lastObstacle].isResting()) {
						aObstacles[i].startMoving(8);
						lastObstacle = i;
					}
				}
			}

			sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
			std::ostringstream strCursorPos;
			strCursorPos << "(" << cursorPos.x << ", " << aObstacles[lastObstacle].getPosition().x << ")";
			sf::Text txtCursorPos(strCursorPos.str(), font, 17);
			txtCursorPos.setColor(sf::Color::White);
		}

		window.clear();
		window.draw(rectWindow);
		window.draw(spritePlayerChar);
		window.draw(spriteTallObstacle1);
		window.draw(spriteTallObstacle2);
		window.draw(spriteMedObstacle1);
		window.draw(spriteMedObstacle2);
		window.draw(spriteWideObstacle1);
		window.draw(spriteWideObstacle2);

		sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
		std::ostringstream strCursorPos;
		strCursorPos << "(" << contam << ", " << aObstacles[lastObstacle].getPosition().x << ")";
		sf::Text txtCursorPos(strCursorPos.str(), font, 17);
		txtCursorPos.setColor(sf::Color::White);
		window.draw(txtCursorPos);

		window.display();

		accumulator += upsClock.restart();
	}
}

void game::checkCollision() {
	for (int i = 0; i < 6; i++) {
		if (i != disabledObst) {
			if (playerChar.getPosition().x > aObstacles[i].getPosition().x && playerChar.getPosition().x < aObstacles[i].getPosition().x + aObstacles[i].getWidth()) {
				if (playerChar.getPosition().y + playerChar.getHeight() > aObstacles[i].getPosition().y) {
					playerChar.MoveIn();
					contam++;
					disabledObst = i;
				}
			}
		}
	}
}

void game::over() {

}

int game::getScore() {
	return score;
}

int game::getContam() {
	return contam;
}

int game::getSpeed() {
	return speed;
}

int game::getState() {
	return state;
}

game::~game()
{
	delete[] aObstacles;
}