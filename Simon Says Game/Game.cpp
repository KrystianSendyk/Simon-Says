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
	m_noteSequences(), //sequence of the notes
	m_exitGame{false} //when true game will exit
{
	m_buttons(); //displays the buttons to the screen
	m_word(); //displays the text to the screen
	gameMode(m_difficulty);
	timerButtons();
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
		processMouse(newEvent); //event for mouse press
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processMouse(sf::Event &t_event) //function for checking if the button was pressed
{
	const int COL_1_lEFT = 330.0F; //first colum left
	const int COL_1_RIGHT = 530.0f; //first colum right
	const int Col_2_LEFT = 570.0f; //second colum left
	const int COL_2_RIGHT = 770.0f; //second colum right

	const int ROW_1_TOP = 30.0f; //first row top
	const int ROW_1_BOTTOM = 230;//first row bottom
	const int ROW_2_TOP = 250.0f; //second row top
	const int ROW_2_BOTTOM = 450.0f; //second row bottom

	if (sf::Event::MouseButtonReleased == t_event.type)
	{
		//checks if the player presses the squares
		if (t_event.mouseButton.x > COL_1_lEFT && t_event.mouseButton.x < COL_1_RIGHT) //checks if the player pressed between first colum
		{
			if (t_event.mouseButton.y > ROW_1_TOP && t_event.mouseButton.y < ROW_1_BOTTOM) //checks if the player pressed between first row
			{
				m_greenButtonPressed = true; //sets the pressed button to true
				timerButtons();
			}

			if (t_event.mouseButton.y > ROW_2_TOP && t_event.mouseButton.y < ROW_2_BOTTOM) //checks if the player pressed between second row
			{
				m_yellowButtonPressed = true; //sets the pressed button to true
				timerButtons();
			}
		}

		if (t_event.mouseButton.x > Col_2_LEFT && t_event.mouseButton.x < COL_2_RIGHT)//checks if the player pressed between second colum
		{
			if (t_event.mouseButton.y > ROW_1_TOP && t_event.mouseButton.y < ROW_1_BOTTOM) //checks if the player pressed between first row
			{
				m_redButtonPressed = true; //sets the pressed button to true
				timerButtons();
			}

			if (t_event.mouseButton.y > ROW_2_TOP && t_event.mouseButton.y < ROW_2_BOTTOM) //checks if the player pressed between second row
			{
				m_blueButtonPressed = true; //sets the pressed button to true
				timerButtons();
			}
		}
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
	if (m_blueButtonPressed == true) //blue button pressed exits the game
	{
		m_window.close();
	}

	if (m_redButtonPressed == true) //red button pressed, lights up
	{
		randomiseNotes(); //randomises the notes for easy mode
		m_difficulty = 32; //the difficulty level
		m_currentNote = 0; // the current note you are on
		m_currentCount = 1; // the count of the notes
	}

	if (m_yellowButtonPressed == true) //yellow button pressed, light up
	{
		randomiseNotes(); //randomises the notes for easy mode
		m_difficulty = 16; //the difficulty level
		m_currentNote = 0; // the current note you are on
		m_currentCount = 1; // the count of the notes
	}

	if (m_greenButtonPressed == true) //green button pressed, light up
	{
		randomiseNotes(); //randomises the notes for easy mode
		m_difficulty = 8; //the difficulty level
		m_currentNote = 0; // the current note you are on
		m_currentCount = 1; // the count of the notes
	}
	timerButtons();//countdown timers
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
	m_window.draw(m_easy); //draws the start text for easy mode
	m_window.draw(m_medium); //draws the start text for medium mode
	m_window.draw(m_hard); //draws the start text for hard mode
	m_window.draw(m_exit); //draw the exit text

	m_window.display();
}

void Game::m_buttons() //sets the color and position of the buttons
{
	m_greenButton.setFillColor(GREEN); //colors the square green
	m_greenButton.setPosition(sf::Vector2f{ 330.0f, 30.0f }); //positons the square

	m_yellowButton.setFillColor(YELLOW); //colors the square yellow
	m_yellowButton.setPosition(sf::Vector2f{ 330.0f, 250.0f }); //positions the square

	m_redButton.setFillColor(RED); //colors the square red
	m_redButton.setPosition(sf::Vector2f{ 570.0f, 30.0f }); //positions the square

	m_blueButton.setFillColor(BLUE); //colors the square blue
	m_blueButton.setPosition(sf::Vector2f{ 570.0f, 250.0f }); //positions the square
}

void Game::randomiseNotes() //randomises the notes played
{
	for (int i = 0; i < 32; i++)
	{
		m_noteSequences[i] = std::rand() % 4;
	}

	const int GREEN_BUTTON = 0; //the notes are stored as numbers
	const int YELLOW_BUTTON = 1;
	const int RED_BUTTON = 2;
	const int BLUE_BUTTON = 3;
}

void Game::m_word() //text for different modes and title to the screem
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

	m_easy.setFont(m_ArialBlackfont);
	m_easy.setString("Easy");
	m_easy.setPosition(sf::Vector2f{ 380.0f,110.0f });
	m_easy.setFillColor(sf::Color::White);
	m_easy.setCharacterSize(40U);

	m_medium.setFont(m_ArialBlackfont);
	m_medium.setString("Medium");
	m_medium.setPosition(sf::Vector2f{ 345.0f,320.0f });
	m_medium.setFillColor(sf::Color::White);
	m_medium.setCharacterSize(40U);

	m_hard.setFont(m_ArialBlackfont);
	m_hard.setString("Hard");
	m_hard.setPosition(sf::Vector2f{ 620.0f,110.0f });
	m_hard.setFillColor(sf::Color::White);
	m_hard.setCharacterSize(40U);

	m_exit.setFont(m_ArialBlackfont);
	m_exit.setString("Exit");
	m_exit.setPosition(sf::Vector2f{ 630.0f,320.0f });
	m_exit.setFillColor(sf::Color::White);
	m_exit.setCharacterSize(40U);
}

void Game::gameMode(int m_difficulty)
{
	
}

void Game::timerButtons()
{
	if (m_greenTimer > 0)
	{
		if (0 == --m_greenTimer) //when timer reaches zero it turns to the original color
		{
			m_greenButton.setFillColor(sf::Color::Green);
		}
	}
}