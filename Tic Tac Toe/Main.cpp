#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "Tic_Tac_Toe.h"

int main()
{
	TicTacToe tic_tac_toe;

	if (!tic_tac_toe.load_assets())
	{
		std::cout << "Unable to load game assets, Quitting!" << std::endl;
		return -1;
	}

	if (!tic_tac_toe.initialize_game(PLAYER_X))
	{
		std::cout << "Unable to initialize game, Quitting!" << std::endl;
		return -1;
	}

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tic-Tac-Toe");

	sf::Image game_icon;
	game_icon.loadFromFile("Assets/Logo/Logo.png");
	window.setIcon(game_icon.getSize().x, game_icon.getSize().y, game_icon.getPixelsPtr());

	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		tic_tac_toe.draw(window);
		window.display();

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					tic_tac_toe.keyPress(window.mapPixelToCoords(sf::Mouse::getPosition(window)), window);
				}
			}
		}
	}

	return 0;
}