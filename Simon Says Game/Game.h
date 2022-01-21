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
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void m_buttons();

	const sf::Color RED{ 194, 0 , 0 , 255 }; //color for red button
	const sf::Color BLUE{ 41, 41, 238, 255 }; //color for blue button

	sf::RectangleShape m_redButton; //shape for red button
	sf::RectangleShape m_blueButton; //shape for blue button

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

