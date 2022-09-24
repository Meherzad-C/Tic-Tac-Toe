#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Size of the Render Window
#define SCREEN_WIDTH 650
#define SCREEN_HEIGHT 800

// Player markers
#define BLANK 0
#define PLAYER_X 1
#define PLAYER_O 2

class TicTacToe
{
private:

	// Textures
	sf::Texture board_texture;
	sf::Texture texture_x;
	sf::Texture texture_O;
	sf::Texture texture_blank;
	
	// Fonts
	sf::Font titleFont;
	sf::Font font;  

	// Sounds
	sf::SoundBuffer click_buffer;
	sf::Sound click_sound;
	sf::SoundBuffer win_buffer;
	sf::Sound win_sound;

	// Sprites
	sf::Sprite board;
	sf::Sprite pieces[3][3];

	// Text
	sf::Text text;
	sf::Text title;
	sf::Text reset;
	sf::Text exit;

	// Determine which player is playing currently
	int current_player;
	
	// Reset 
	bool wait_for_reset;

	// Game functions
	bool load_board();
	bool load_pieces();
	bool load_fonts_and_text();
	bool load_sounds();

	// Check if there is a win for either player
	bool is_win();

	// Chech if slots are available to play on board
	bool are_slots_available();

public:

	// Board
	unsigned int board_model[3][3];

	// Asset loading function
	bool load_assets();

	// Initializing the game
	bool initialize_game(int start_player);

	// Draw in Window
	void draw(sf::RenderWindow& window);

	// Keypress
	void keyPress(sf::Vector2f pos, sf::RenderWindow& window);
};
