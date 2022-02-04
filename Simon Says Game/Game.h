/// <summary>
/// Name: Krystian Sendyk
/// Date: 21/01/2022
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processMouse(sf::Event &t_event); // to detect mouse clicks
	void update(sf::Time t_deltaTime);
	void render();
	
	void m_buttons(); //function for setting the color and position of the buttons
	void randomiseNotes();
	void m_word(); //function for text of different modes and title to the screem
	void gameMode(int m_difficulty); //function for the game modes
	void timerButtons(); //countdown timers

	const sf::Color RED{ 194, 0 , 0 , 255 }; //color for red button
	const sf::Color BLUE{ 41, 41, 238, 255 }; //color for blue button
	const sf::Color GREEN{ 54, 188, 54, 255 }; //color for green button
	const sf::Color YELLOW{ 247, 247, 32, 255 }; //color for yellow button

	sf::RectangleShape m_redButton; //shape for red button
	sf::RectangleShape m_blueButton; //shape for blue button
	sf::RectangleShape m_greenButton; //shape for green butoon
	sf::RectangleShape m_yellowButton; //shape for yellow button

	const int FLASH_TIME = 60; //how long it stays lit up
	int m_redTimer = FLASH_TIME; //flash time of red button
	int m_blueTimer = FLASH_TIME; //flash time of blue button
	int m_greenTimer = FLASH_TIME; //flash time of green button
	int m_yelloweTimer = FLASH_TIME; //flash time of yellow button
	int m_difficulty = 0; //sets the difficulty of the game

	

	int m_currentNote = 0;//the current note the player is on
	int m_currentCount = 0; //counts the the notes
	int m_noteSequences[32]; //hold the sequence of the notes

	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_title; //text for message
	sf::Text m_easy; //text for easy mode
	sf::Text m_medium; //text for medium mode
	sf::Text m_hard; //text for hard mode
	sf::Text m_exit; //text for exit button

	sf::RenderWindow m_window; // main SFML window
	
	bool m_redButtonPressed = false; //check for red button press
	bool m_blueButtonPressed = false; //check for blue button press
	bool m_greenButtonPressed = false; //check for green button press
	bool m_yellowButtonPressed = false; //check for yellow button press

	bool m_exitGame; // control exiting game
};

#endif // !GAME_HPP