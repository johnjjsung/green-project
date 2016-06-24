#include "game.hpp"

game::game() :
	settings(),
	window(sf::VideoMode(800, 400), "SFML", sf::Style::Close, settings),
	rectWindow(sf::Vector2f(800, 400)),
	font(),
	textureMario(),
	spritePlayerChar(textureMario, sf::IntRect(211, 0, 12, 15)),
	playerChar(),
	cursorPos(),
	txtCursorPos(),
	strCursorPos()
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

}

void game::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(rectWindow);
		window.draw(spritePlayerChar);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			playerChar.Jump();
		}
		playerChar.Move();
		spritePlayerChar.setPosition(playerChar.getPosition());

		sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
		std::ostringstream strCursorPos;
		strCursorPos << "(" << cursorPos.x << ", " << cursorPos.y << ")";
		sf::Text txtCursorPos(strCursorPos.str(), font, 17);
		txtCursorPos.setColor(sf::Color::White);
		window.draw(txtCursorPos);

		window.display();
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

int game::getGameSpeed() {
	return gameSpeed;
}

int game::getGameState() {
	return gameState;
}

game::~game()
{
}
