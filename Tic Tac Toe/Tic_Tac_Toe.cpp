#include <iostream>
#include <string>

// Tic Tac Toe Header file
#include "Tic_Tac_Toe.h"

using std::string;

bool TicTacToe::load_board()
{
	if (!board_texture.loadFromFile("Assets/Game/Board.png"))
	{
		return false;
	}

	board.setTexture(board_texture);
	board.setOrigin(sf::Vector2f(board.getGlobalBounds().width / 2,
								 board.getGlobalBounds().height / 2));
	board.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	return true;
}

bool TicTacToe::load_pieces()
{
	if (!texture_O.loadFromFile("Assets/Game/O.png"))
	{
		return false;
	}

	if (!texture_x.loadFromFile("Assets/Game/X.png"))
	{
		return false;
	}

	if (!texture_blank.loadFromFile("Assets/Game/Blank.png"))
	{
		return false;
	}

	return true;
}

bool TicTacToe::load_fonts_and_text()
{
	if (!font.loadFromFile("Assets/Fonts/Gasalt-Black.ttf"))
	{
		return false;
	}

	if (!titleFont.loadFromFile("Assets/Fonts/PAC-FONT.ttf"))
	{
		return false;
	}

	text.setFont(font);
	text.setCharacterSize(35);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(260.0f, 88.0f));

	title.setFont(titleFont);
	title.setCharacterSize(65);
	title.setFillColor(sf::Color::Black);
	title.setPosition(sf::Vector2f(80.0f, 3.0f));
	title.setString("Tic-Tac-Toe");

	reset.setFont(font);
	reset.setCharacterSize(55);
	reset.setFillColor(sf::Color(153, 0, 153));
	reset.setPosition(sf::Vector2f(55.0f, 700.0f));
	reset.setString("RESET");

	exit.setFont(font);
	exit.setCharacterSize(55);
	exit.setFillColor(sf::Color(34, 153, 84));
	exit.setPosition(sf::Vector2f(470.0f, 700.0f));
	exit.setString("EXIT");

	return true;
}

bool TicTacToe::load_sounds()
{
	if (!click_buffer.loadFromFile("Assets/Audio/Click.wav"))
	{
		return false;
	}
	click_sound.setBuffer(click_buffer);

	if (!win_buffer.loadFromFile("Assets/Audio/Win.wav"))
	{
		return false;
	}
	win_sound.setBuffer(win_buffer);

	return true;
}

bool TicTacToe::load_assets()
{
	if (!load_board() ||
		!load_pieces() ||
		!load_fonts_and_text() ||
		!load_sounds())
	{
		return false;
	}

	return true;
}

bool TicTacToe::initialize_game(int start_player)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			board_model[row][col] = BLANK;
		}
	}

	this->wait_for_reset = false;

	this->pieces[0][0].setPosition(sf::Vector2f(33.0f, 141.0f));
	this->pieces[0][1].setPosition(sf::Vector2f(231.0f, 141.0f));
	this->pieces[0][2].setPosition(sf::Vector2f(428.0f, 141.0f));
	this->pieces[1][0].setPosition(sf::Vector2f(33.0f, 316.0f));
	this->pieces[1][1].setPosition(sf::Vector2f(231.0f, 316.0f));
	this->pieces[1][2].setPosition(sf::Vector2f(428.0f, 316.0f));
	this->pieces[2][0].setPosition(sf::Vector2f(33.0f, 491.0f));
	this->pieces[2][1].setPosition(sf::Vector2f(231.0f, 491.0f));
	this->pieces[2][2].setPosition(sf::Vector2f(428.0f, 491.0f));

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->pieces[i][j].setTexture(texture_blank);
			this->pieces[i][j].setScale(sf::Vector2f(1.89f, 1.68f));
		}
	}

	current_player = start_player;

	if (current_player == PLAYER_X)
	{
		text.setString("X playing");
		text.setFillColor(sf::Color::Black);
	}

	else
	{
		text.setString("O playing");
		text.setFillColor(sf::Color::Red);
	}

	return true;
}

void TicTacToe::draw(sf::RenderWindow& window)
{
	window.draw(title);
	window.draw(board);
	window.draw(text);
	window.draw(reset);
	window.draw(exit);

	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			window.draw(pieces[row][column]);
}

bool TicTacToe::is_win()
{
	// Check rows for a win
	for (int row = 0; row < 3; row++)
	{
		if (board_model[row][0] == board_model[row][1] && board_model[row][1] == board_model[row][2])
		{
			if (board_model[row][0] != BLANK)
			{
				return true;
			}
		}
	}

	// Check columns for win
	for (int col = 0; col < 3; col++)
	{
		if (board_model[0][col] == board_model[1][col] && board_model[1][col] == board_model[2][col])
		{
			if (board_model[0][col] != BLANK)
			{
				return true;
			}
		}
	}

	// Check top-right to left-bottom diagonal for win
	if (board_model[0][0] == board_model[1][1] && board_model[1][1] == board_model[2][2])
	{
		if (board_model[0][0] != BLANK)
		{
			return true;
		}
	}

	// Check top-left to right-bottom diagonal for win
	if (board_model[0][2] == board_model[1][1] && board_model[1][1] == board_model[2][0])
	{
		if (board_model[0][2] != BLANK)
		{
			return true;
		}
	}

	return false;
}

bool TicTacToe::are_slots_available()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			// Slots still available to play
			if (board_model[row][col] == 0)
			{
				return true;
			}
		}
	}
	
	return false;
}

void TicTacToe::keyPress(sf::Vector2f pos, sf::RenderWindow& window)
{
	// Reset hit?
	if (reset.getGlobalBounds().contains(pos))
	{
		win_sound.stop();
		initialize_game(current_player == PLAYER_X ? PLAYER_O : PLAYER_X);
	}

	// Exit hit?
	if (exit.getGlobalBounds().contains(pos))
	{
		window.close();
	}

	// All slots played, only reset or exit possible
	if (wait_for_reset)
	{
		return;
	}

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			// Check if this piece was clicked
			if (!pieces[row][col].getGlobalBounds().contains(pos))
			{
				continue;
			}

			if (board_model[row][col] == 0)
			{
				pieces[row][col].setTexture(current_player == PLAYER_X ? texture_x : texture_O);

				board_model[row][col] = current_player;

				if (is_win())
				{
					wait_for_reset = true;
					text.setPosition(sf::Vector2f(280.0f, 88.0f));
					text.setString(current_player == PLAYER_X ? "X wins!" : "O wins!");
					text.setPosition(sf::Vector2f(260.0f, 88.0f));
					win_sound.play();
				}

				else
				{
					if (are_slots_available())
					{
						// Toggle player
						current_player = current_player == PLAYER_X ? PLAYER_O : PLAYER_X;

						if (current_player == PLAYER_X)
						{
							text.setString("X playing");
							text.setFillColor(sf::Color::Black);
						}

						else
						{
							text.setString("O playing");
							text.setFillColor(sf::Color::Red);
						}

						click_sound.play();
					}

					else
					{
						wait_for_reset = true;
						text.setPosition(sf::Vector2f(120.0f, 85.0f));
						text.setString("Draw, Play Again");
						text.setPosition(sf::Vector2f(260.0f, 88.0f));
					}
				}
			}
		}
	}
}