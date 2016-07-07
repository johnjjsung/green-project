#include "game.hpp"

game::game() :
	settings(),
	window(sf::VideoMode(WindowWidth, WindowHeight), "SFML", sf::Style::Close, settings),
	rectWindow(sf::Vector2f(WindowWidth, WindowHeight)),
	font(),
	textureMario(),
	spritePlayerChar(textureMario, sf::IntRect(211, 0, 12, 15)),
	playerChar(),
	spriteTallObstacle(textureObstacles, sf::IntRect(5, 4, 53, 125)),
	spriteMedObstacle(textureObstacles, sf::IntRect(83, 40, 47, 89)),
	spriteWideObstacle(textureObstacles, sf::IntRect(155, 100, 92, 29)),
	tallObstacle1(),
	tallObstacle2(),
	medObstacle1(),
	medObstacle2(),
	wideObstacle1(),
	wideObstacle2(),
	cursorPos(),
	txtCursorPos(),
	strCursorPos(),
	upsClock(),
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

	tallObstacle1.setSize(53, 125);
	tallObstacle2.setSize(53, 125);
	medObstacle1.setSize(47, 89);
	medObstacle2.setSize(47, 89);
	wideObstacle1.setSize(92, 29);
	wideObstacle2.setSize(92, 29);
	tallObstacle1.Rest();
	tallObstacle2.Rest();
	medObstacle1.Rest();
	medObstacle2.Rest();
	wideObstacle1.Rest();
	wideObstacle2.Rest();

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

			spritePlayerChar.setPosition(playerChar.getPosition());
			spriteTallObstacle.setPosition(tallObstacle1.getPosition());
			spriteTallObstacle.setPosition(tallObstacle2.getPosition());
			spriteMedObstacle.setPosition(medObstacle1.getPosition());
			spriteMedObstacle.setPosition(medObstacle2.getPosition());
			spriteWideObstacle.setPosition(wideObstacle1.getPosition());
			spriteWideObstacle.setPosition(wideObstacle2.getPosition());

			tallObstacle1.Move();
			tallObstacle2.Move();
			medObstacle1.Move();
			medObstacle2.Move();
			wideObstacle1.Move();
			wideObstacle2.Move();

			sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
			std::ostringstream strCursorPos;
			strCursorPos << "(" << cursorPos.x << ", " << cursorPos.y << ")";
			sf::Text txtCursorPos(strCursorPos.str(), font, 17);
			txtCursorPos.setColor(sf::Color::White);
		}

		window.clear();
		window.draw(rectWindow);
		window.draw(spritePlayerChar);
		window.draw(spriteTallObstacle);
		window.draw(spriteMedObstacle);
		window.draw(spriteWideObstacle);
		window.draw(txtCursorPos);

		window.display();

		accumulator += upsClock.restart();
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
}
