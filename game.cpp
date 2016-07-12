#include "game.hpp"
#include <math.h>

game::game() :
	settings(),
	window(sf::VideoMode(WindowWidth, WindowHeight), "Green Project", sf::Style::Close, settings),
	rectSky(sf::Vector2f(WindowWidth, GL)),
	rectGround(sf::Vector2f(WindowWidth, WindowHeight - GL)),
	font(),
	spriteMarioWalk1(texturePlayerChar, sf::IntRect(2, 2, 29, 30)),
	spriteMarioWalk2(texturePlayerChar, sf::IntRect(39, 5, 25, 33)),
	spriteMarioWalk3(texturePlayerChar, sf::IntRect(71, 5, 33, 33)),
	spriteMarioJump(texturePlayerChar, sf::IntRect(114, 5, 36, 33)),

	spriteQuoteWalk1(texturePlayerChar, sf::IntRect(3, 52, 27, 30)),
	spriteQuoteWalk2(texturePlayerChar, sf::IntRect(36, 53, 27, 29)),
	spriteQuoteWalk3(texturePlayerChar, sf::IntRect(70, 52, 27, 30)),
	spriteQuoteJump1(texturePlayerChar, sf::IntRect(70, 52, 27, 30)),
	spriteQuoteJump2(texturePlayerChar, sf::IntRect(3, 52, 27, 30)),

	spriteDinoWalk1(texturePlayerChar, sf::IntRect(6, 98, 39, 42)),
	spriteDinoWalk2(texturePlayerChar, sf::IntRect(58, 98, 39, 42)),
	spriteDinoJump(texturePlayerChar, sf::IntRect(108, 99, 39, 42)),

	spriteTallObstacle1(textureObstacles, sf::IntRect(5, 4, 53, 125)),
	spriteTallObstacle2(textureObstacles, sf::IntRect(5, 4, 53, 125)),
	spriteMedObstacle1(textureObstacles, sf::IntRect(83, 40, 47, 89)),
	spriteMedObstacle2(textureObstacles, sf::IntRect(83, 40, 47, 89)),
	spriteWideObstacle1(textureObstacles, sf::IntRect(155, 100, 92, 29)),
	spriteWideObstacle2(textureObstacles, sf::IntRect(155, 100, 92, 29)),

	spriteMountain1(textureMountains, sf::IntRect(0, 0, 202, 87)),
	spriteMountain2(textureMountains, sf::IntRect(222, 0, 307, 87)),
	spriteMountain3(textureMountains, sf::IntRect(10, 171, 155, 55)),
	spriteMountain4(textureMountains, sf::IntRect(205, 190, 220, 36)),

	spriteMountain1_contam1(textureMountains, sf::IntRect(0, 321, 202, 83)),
	spriteMountain2_contam1(textureMountains, sf::IntRect(222, 359, 308, 45)),
	spriteMountain3_contam1(textureMountains, sf::IntRect(10, 488, 155, 55)),
	spriteMountain4_contam1(textureMountains, sf::IntRect(205, 508, 220, 35)),

	spriteMountain1_contam2(textureMountains, sf::IntRect(0, 647, 202, 83)),
	spriteMountain2_contam2(textureMountains, sf::IntRect(222, 666, 308, 64)),
	spriteMountain3_contam2(textureMountains, sf::IntRect(10, 814, 155, 55)),
	spriteMountain4_contam2(textureMountains, sf::IntRect(205, 823, 220, 46)),

	playerSpriteCountdown(18),
	upsClock(),
	accumulator(sf::Time::Zero),
	ups(sf::seconds(1.f / 60.f)),
	state(0),
	highScore(0)
{
	settings.antialiasingLevel = 4;
	window.setVerticalSyncEnabled(true);
	rectSky.setFillColor(sf::Color(120, 170, 255));
	rectGround.setPosition(sf::Vector2f(0, GL));
	rectGround.setFillColor(sf::Color(134, 89, 45));

	if (!font.loadFromFile("pixelmix_bold.ttf")) {
		// error
	}
	if (!texturePlayerChar.loadFromFile("sprites/player.png")) {
		// error
	}
	if (!textureObstacles.loadFromFile("sprites/obstacles.png")) {
		// error
	}
	if (!textureMountains.loadFromFile("sprites/mountains.png")) {
		// error
	}
}

void game::run() {
	srand(time(NULL));

	firstCycleRan = false;

	speed = 5;
	score = 0;
	contam = 0;
	scoreCountdown = 10;
	restartCountdown = 100;
	disabledObst = 42;
	lastObstacle = 0;

	arObstacles[0].setSize(53, 125);
	arObstacles[1].setSize(53, 125);
	arObstacles[2].setSize(47, 89);
	arObstacles[3].setSize(47, 89);
	arObstacles[4].setSize(92, 29);
	arObstacles[5].setSize(92, 29);
	for (int i = 0; i < 6; i++) {
		arObstacles[i].Rest();
	}

	arMountains[0].setSize(202, 87);
	arMountains[1].setSize(307, 87);
	arMountains[2].setSize(155, 55);
	arMountains[3].setSize(220, 36);
	arMountains[4].setSize(202, 83);
	arMountains[5].setSize(308, 45);
	arMountains[6].setSize(155, 55);
	arMountains[7].setSize(220, 35);
	arMountains[8].setSize(202, 83);
	arMountains[9].setSize(308, 64);
	arMountains[10].setSize(155, 55);
	arMountains[11].setSize(220, 46);
	for (int i = 0; i < 12; i++) {
		arMountains[i].Rest();
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

			if (state == 1) {
					speed = 6 + score / 100;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					marioWalk1.Jump();
					quoteWalk1.Jump();
					dinoWalk1.Jump();
				}

				switch (contam) {
				case 0:
					marioWalk1.Move();
					marioWalk2.setPosition(marioWalk1.getPosition().x + 4, marioWalk1.getPosition().y - 3);
					marioWalk3.setPosition(marioWalk1.getPosition().x - 3, marioWalk1.getPosition().y - 3);
					marioJump.setPosition(marioWalk1.getPosition().x, marioWalk1.getPosition().y);
					break;
				case 1:
					quoteWalk1.Move();
					quoteWalk2.setPosition(quoteWalk1.getPosition().x, quoteWalk1.getPosition().y);
					quoteWalk3.setPosition(quoteWalk1.getPosition().x, quoteWalk1.getPosition().y + 1);
					quoteJump1.setPosition(quoteWalk1.getPosition().x, quoteWalk1.getPosition().y);
					quoteJump2.setPosition(quoteWalk1.getPosition().x, quoteWalk1.getPosition().y);
					break;
				case 2:
					dinoWalk1.Move();
					dinoWalk2.setPosition(dinoWalk1.getPosition().x, dinoWalk1.getPosition().y);
					dinoJump.setPosition(dinoWalk1.getPosition().x, dinoWalk1.getPosition().y);
					break;
				}

				checkCollision();
				if (contam >= 3) {
					over();
				}

				spriteMarioWalk1.setPosition(marioWalk1.getPosition());
				spriteMarioWalk2.setPosition(marioWalk2.getPosition());
				spriteMarioWalk3.setPosition(marioWalk3.getPosition());
				spriteMarioJump.setPosition(marioJump.getPosition());

				spriteQuoteWalk1.setPosition(quoteWalk1.getPosition());
				spriteQuoteWalk2.setPosition(quoteWalk2.getPosition());
				spriteQuoteWalk3.setPosition(quoteWalk3.getPosition());
				spriteQuoteJump1.setPosition(quoteJump1.getPosition());
				spriteQuoteJump2.setPosition(quoteJump2.getPosition());

				spriteDinoWalk1.setPosition(dinoWalk1.getPosition());
				spriteDinoWalk2.setPosition(dinoWalk2.getPosition());
				spriteDinoJump.setPosition(dinoJump.getPosition());

				setSpritePosition();

				for (int i = 0; i < 6; i++) {
					arObstacles[i].Move();
					arObstacles[i].setRestTimeBase(8000 - (speed * 1.5));
					if (arObstacles[i].getRestClock().getElapsedTime() > arObstacles[i].getRestTime()) {
						if (arObstacles[lastObstacle].getPosition().x < 500 - (speed * 6) || arObstacles[lastObstacle].isResting()) {
							if ((lastObstacle == 1 || 2) && (i == 1 || 2)) {
								if (arObstacles[lastObstacle].getPosition().x < 500 - (speed * 10) || arObstacles[lastObstacle].isResting()) {
									arObstacles[i].startMoving(speed);
									lastObstacle = i;
								}
							}
							arObstacles[i].startMoving(speed);
							lastObstacle = i;
						}
					}
				}

				for (int i = 0; i < 12; i++) {
					arMountains[i].Move();
				}

				if (contam < 3) {
					for (int i = contam * 4; i < (contam * 4) + 4; i++) {
						if (arMountains[i].getRestClock().getElapsedTime() > arMountains[i].getRestTime()) {
							arMountains[i].startMoving(speed / 10);
						}
					}
				}

				if (scoreCountdown == 0) {
					score++;
					scoreCountdown = 10;
				}
				scoreCountdown--;

				if (contam < 2) {
					if (playerSpriteCountdown == 0) {
						playerSpriteCountdown = 18;
					}
					playerSpriteCountdown--;
					if (playerSpriteCountdown == 0) {
						playerSpriteCountdown = 17;
					}
				}
				else {
					if (playerSpriteCountdown == 0) {
						playerSpriteCountdown = 10;
					}
					playerSpriteCountdown--;
					if (playerSpriteCountdown == 0) {
						playerSpriteCountdown = 9;
					}
				}
			}
			if (state == 2) {
				if (restartCountdown > 0) {
					restartCountdown--;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					if (restartCountdown <= 0) {
						state = 1;
						run();
					}
				}
			}
			if (state == 0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					state = 1;
					run();
				}
			}
		}

		window.clear();
		window.draw(rectSky);
		window.draw(rectGround);

		if (state != 0 && firstCycleRan == true) {
			renderMountains();
			renderObstacles();
			renderPlayerChar();
		}
		std::ostringstream strScore;
		strScore << score;
		sf::Text txtScore(strScore.str(), font, 15);
		txtScore.setPosition(sf::Vector2f(WindowWidth - 60, 5));

		std::ostringstream strHighScore;
		strHighScore << "High " << highScore;
		sf::Text txtHighScore(strHighScore.str(), font, 15);
		txtHighScore.setPosition(sf::Vector2f(WindowWidth - 200, 5));

		window.draw(txtScore);
		window.draw(txtHighScore);

		if (state == 2) {
			sf::Text txtGameOver("Game Over.", font, 15);
			sf::Text txtRestart("Press Spacebar to restart.", font, 15);
			txtGameOver.setPosition(sf::Vector2f(340, 100));
			txtRestart.setPosition(sf::Vector2f(260, 120));
			window.draw(txtGameOver);
			window.draw(txtRestart);
		}

		if (state == 0) {
			sf::Text txtStart("Press Spacebar to start.", font, 15);
			txtStart.setPosition(sf::Vector2f(267, 120));
			window.draw(txtStart);
		}

		window.display();

		accumulator += upsClock.restart();
		firstCycleRan = true;
	}
}

void game::checkCollision() {
	switch (contam) {
	case 0:
		for (int i = 0; i < 6; i++) {
			if (i != disabledObst) {
				if (marioWalk1.getPosition().x + marioWalk1.getWidth() > arObstacles[i].getPosition().x && marioWalk1.getPosition().x < arObstacles[i].getPosition().x + arObstacles[i].getWidth()) {
					if (marioWalk1.getPosition().y + marioWalk1.getHeight() > arObstacles[i].getPosition().y) {
						contam++;
						disabledObst = i;

						if (contam < 3) {
							for (int j = contam * 4; j < (contam * 4) + 4; j++) {
								arMountains[j].Rest();
							}
							changeChar();
						}
					}
				}
			}
		}
		break;
	case 1:
		for (int i = 0; i < 6; i++) {
			if (i != disabledObst) {
				if (quoteWalk1.getPosition().x + quoteWalk1.getWidth() > arObstacles[i].getPosition().x && quoteWalk1.getPosition().x < arObstacles[i].getPosition().x + arObstacles[i].getWidth()) {
					if (quoteWalk1.getPosition().y + quoteWalk1.getHeight() > arObstacles[i].getPosition().y) {
						contam++;
						disabledObst = i;

						if (contam < 3) {
							for (int j = contam * 4; j < (contam * 4) + 4; j++) {
								arMountains[j].Rest();
							}
							changeChar();
						}
					}
				}
			}
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++) {
			if (i != disabledObst) {
				if (dinoWalk1.getPosition().x + dinoWalk1.getWidth() > arObstacles[i].getPosition().x && dinoWalk1.getPosition().x < arObstacles[i].getPosition().x + arObstacles[i].getWidth()) {
					if (dinoWalk1.getPosition().y + dinoWalk1.getHeight() > arObstacles[i].getPosition().y) {
						contam++;
						disabledObst = i;

						if (contam < 3) {
							for (int j = contam * 4; j < (contam * 4) + 4; j++) {
								arMountains[j].Rest();
							}
							changeChar();
						}
					}
				}
			}
		}
		break;
	}
}

void game::changeChar() {
	if (contam == 1) {
		quoteWalk1.setSize(27, 30);
		quoteWalk2.setSize(27, 29);
		quoteWalk3.setSize(27, 30);
		quoteJump1.setSize(27, 30);
		quoteJump2.setSize(27, 30);

		quoteWalk1.setPosition(marioWalk1.getPosition().x, marioWalk1.getPosition().y);
		quoteWalk1.setdy(marioWalk1.getdy());
	}
	else if (contam == 2) {
		dinoWalk1.setSize(39, 42);
		dinoWalk2.setSize(39, 42);
		dinoJump.setSize(39, 42);

		dinoWalk1.setPosition(quoteWalk1.getPosition().x - 6, quoteWalk1.getPosition().y - 12);
		dinoWalk1.setdy(quoteWalk1.getdy());

		playerSpriteCountdown = 10;
	}
}

void game::renderPlayerChar() {
	switch (contam) {
	case 0:
		if (!marioWalk1.isJumping()) {
			if (playerSpriteCountdown < 18 && playerSpriteCountdown >= 14) {
				window.draw(spriteMarioWalk1);
			}
			else if (playerSpriteCountdown < 14 && playerSpriteCountdown >= 10) {
				window.draw(spriteMarioWalk2);
			}
			else if (playerSpriteCountdown < 10 && playerSpriteCountdown >= 6) {
				window.draw(spriteMarioWalk3);
			}
			else if (playerSpriteCountdown < 6 && playerSpriteCountdown > 0) {
				window.draw(spriteMarioWalk2);
			}
		}
		else {
			window.draw(spriteMarioJump);
		}
		break;
	case 1:
		if (!quoteWalk1.isJumping()) {
			if (playerSpriteCountdown < 18 && playerSpriteCountdown >= 14) {
				window.draw(spriteQuoteWalk1);
			}
			else if (playerSpriteCountdown < 14 && playerSpriteCountdown >= 10) {
				window.draw(spriteQuoteWalk2);
			}
			else if (playerSpriteCountdown < 10 && playerSpriteCountdown >= 6) {
				window.draw(spriteQuoteWalk3);
			}
			else if (playerSpriteCountdown < 6 && playerSpriteCountdown > 0) {
				window.draw(spriteQuoteWalk2);
			}
		}
		else {
			if (quoteWalk1.getdy() < 0) {
				window.draw(spriteQuoteWalk3);
			}
			else {
				window.draw(spriteQuoteWalk1);
			}
		}
		break;
	case 2:
		if (!dinoWalk1.isJumping()) {
			if (playerSpriteCountdown < 10 && playerSpriteCountdown >= 6) {
				window.draw(spriteDinoWalk1);
			}
			else if (playerSpriteCountdown < 6 && playerSpriteCountdown > 0) {
				window.draw(spriteDinoWalk2);
			}
		}
		else {
			window.draw(spriteDinoJump);
		}
		break;
	}
}

void game::setSpritePosition() {
	spriteTallObstacle1.setPosition(arObstacles[0].getPosition());
	spriteTallObstacle2.setPosition(arObstacles[1].getPosition());
	spriteMedObstacle1.setPosition(arObstacles[2].getPosition());
	spriteMedObstacle2.setPosition(arObstacles[3].getPosition());
	spriteWideObstacle1.setPosition(arObstacles[4].getPosition());
	spriteWideObstacle2.setPosition(arObstacles[5].getPosition());

	spriteMountain1.setPosition(arMountains[0].getPosition());
	spriteMountain2.setPosition(arMountains[1].getPosition());
	spriteMountain3.setPosition(arMountains[2].getPosition());
	spriteMountain4.setPosition(arMountains[3].getPosition());
	spriteMountain1_contam1.setPosition(arMountains[4].getPosition());
	spriteMountain2_contam1.setPosition(arMountains[5].getPosition());
	spriteMountain3_contam1.setPosition(arMountains[6].getPosition());
	spriteMountain4_contam1.setPosition(arMountains[7].getPosition());
	spriteMountain1_contam2.setPosition(arMountains[8].getPosition());
	spriteMountain2_contam2.setPosition(arMountains[9].getPosition());
	spriteMountain3_contam2.setPosition(arMountains[10].getPosition());
	spriteMountain4_contam2.setPosition(arMountains[11].getPosition());
}

void game::renderMountains() {
	window.draw(spriteMountain1);
	window.draw(spriteMountain2);
	window.draw(spriteMountain3);
	window.draw(spriteMountain4);
	window.draw(spriteMountain1_contam1);
	window.draw(spriteMountain2_contam1);
	window.draw(spriteMountain3_contam1);
	window.draw(spriteMountain4_contam1);
	window.draw(spriteMountain1_contam2);
	window.draw(spriteMountain2_contam2);
	window.draw(spriteMountain3_contam2);
	window.draw(spriteMountain4_contam2);
}

void game::renderObstacles() {
	window.draw(spriteTallObstacle1);
	window.draw(spriteTallObstacle2);
	window.draw(spriteMedObstacle1);
	window.draw(spriteMedObstacle2);
	window.draw(spriteWideObstacle1);
	window.draw(spriteWideObstacle2);
}

void game::over() {
	if (score > highScore) {
		highScore = score;
	}
	state = 2;
}

game::~game()
{
	delete[] arObstacles;
	delete[] arMountains;
}