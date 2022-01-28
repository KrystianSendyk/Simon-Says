/// <summary>
/// Name: Krystian Sendyk
/// Date: 21/01/2022
/// 
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_redButton{ sf::Vector2f{ 200.0f, 200.0f } }, //size of the shape
	m_blueButton{ sf::Vector2f{ 200.0f, 200.0f} }, //size of the shape
	m_greenButton{ sf::Vector2f{200.0f,200.0f} }, //size of the shape
	m_yellowButton{ sf::Vector2f{200.0f,200.0f} }, //size of the shape
	m_exitGame{false} //when true game will exit
{
	m_buttons();
	m_titleWord();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_redButton); //draws red square to the board
	m_window.draw(m_blueButton); //draws blue square to the board
	m_window.draw(m_greenButton); //draws green square to the board
	m_window.draw(m_yellowButton); //darws yellow square to the board
	m_window.draw(m_title); //draws the title of the game
	m_window.draw(m_start);
	m_window.display();
}

void Game::m_buttons()
{
	m_redButton.setFillColor(RED); //colors the square red
	m_redButton.setPosition(sf::Vector2f{ 570.0f, 30.0f }); //positions the square

	m_blueButton.setFillColor(BLUE); //colors the square blue
	m_blueButton.setPosition(sf::Vector2f{ 570.0f, 250.0f }); //positions the square

	m_greenButton.setFillColor(GREEN); //colors the square green
	m_greenButton.setPosition(sf::Vector2f{ 330.0f, 30.0f }); //positons the square

	m_yellowButton.setFillColor(YELLOW); //colors the square yellow
	m_yellowButton.setPosition(sf::Vector2f{ 330.0f, 250.0f }); //positions the square
}

void Game::m_titleWord()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "Problem loading the font" << std::endl;
	}

	m_title.setFont(m_ArialBlackfont);
	m_title.setString("Simon Says");
	m_title.setPosition(sf::Vector2f{ 10.0f, 30.0f });
	m_title.setFillColor(sf::Color::White);
	m_title.setCharacterSize(50U);

	m_start.setFont(m_ArialBlackfont);
	m_start.setString("Start");
	m_start.setPosition(sf::Vector2f{ 345.0f,90.0f });
	m_start.setFillColor(sf::Color::White);
	m_start.setCharacterSize(60U);
}