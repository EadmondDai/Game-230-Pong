#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include "GamePlay.h"

using namespace sf;

RenderWindow window(sf::VideoMode(800, 600), "Eadmond's Pong");


int main()
{
	window.setFramerateLimit(60);

	//CircleShape shape(100.f);
	//shape.setFillColor(Color::Green);

	GamePlay newGame;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		int gameState = newGame.GetGameState();
		if (gameState == 0) // playing game
		{
			newGame.PlayGame();
		}
		else if (gameState == 1) // scoring
		{
			newGame.Score();
		}
		else if(gameState == 2) // gameState == 2 winning
		{
			newGame.Winning();
		}
		else {
			newGame.ChooseMode(&window);
			continue;
		}

		newGame.Render(&window);
	}

	return 0;
}
