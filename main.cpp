#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include "GamePlay.h"

using namespace sf;

RenderWindow window(sf::VideoMode(800, 600), "Eadmond's Pong");

int main()
{
	
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
		else // gameState == 2 winning
		{
			newGame.Winning();
		}


		// Related to render

		window.clear();

		Text hello;
		Font font;
		font.loadFromFile("Font/ITCBLKAD.TTF");
		hello.setFont(font);
		hello.setString("How you doing?");
		hello.setCharacterSize(24);
		hello.setColor(Color::Magenta);
		hello.setPosition(400, 300);
		window.draw(hello);

		PadController myController = newGame.GetPadController();

		RectangleShape blueShape = myController.GetBlueShape();
		blueShape.setFillColor(Color::Blue);

		window.draw(blueShape);

		RectangleShape redShape = myController.GetRedShape();
		redShape.setFillColor(Color::Red);

		window.draw(redShape);


		CircleShape ball = newGame.GetBall().GetBallShape();
		ball.setFillColor(Color::Magenta);
		window.draw(ball);

		window.display();

		//newGame.Render(&window);
	}

	return 0;
}
