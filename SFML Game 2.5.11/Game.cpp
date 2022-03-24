/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
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
	m_exitGame{false} //when true game will exit
{
	setupShaders(); // load shader 
	setupSprite(); // load texture
	setupFontAndText(); //load font
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
	
	switch (t_event.key.code)
	{	
	case sf::Keyboard::Escape:
		m_exitGame = true;
		break;
	case sf::Keyboard::Up:     
		m_distortionFactor *= 1.3f;    
		break;
	case sf::Keyboard::Down:    
		m_distortionFactor /= 1.3f;    
		break;
	case sf::Keyboard::Left:    
		m_riseFactor *= 1.3f;          
		break;
	case sf::Keyboard::Right:   
		m_riseFactor /= 1.3f;          
		break;
	default:
		break;
	}
	
	m_shader.setUniform("distortionFactor", m_distortionFactor);
	m_shader.setUniform("riseFactor", m_riseFactor);

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
	m_shader.setUniform("time", m_shader_timer.getElapsedTime().asSeconds());
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_instructionsText);
	m_window.draw(m_triangles,m_states);
	
	m_window.draw(m_logoSprite, &m_shader);
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupShaders()
{
	if (!m_shader.loadFromFile("ASSETS\\SHADERS\\example_001.frag", sf::Shader::Fragment))
	{
		std::cerr << "Error while shaders" << std::endl;		
	}


	if (!m_distortionMap.loadFromFile("ASSETS\\IMAGES\\distortion_map.png"))
	{
		sf::err() << "Error while loading distortion map" << std::endl;
		
	}

	// It is important to set repeated to true to enable scrolling upwards
	m_distortionMap.setRepeated(true);
	// Setting smooth to true lets us use small maps even on larger images
	m_distortionMap.setSmooth(true);
	m_shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
	m_shader.setUniform("distortionMapTexture", m_distortionMap);

	// Shader parameters
	
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	sf::Vertex vertex;
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		std::cerr << "Error while loading texture" << std::endl;		
	}
	// Enable the smooth filter. The texture appears smoother so that pixels are less noticeable.
	m_logoTexture.setSmooth(true);

	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
	sf::FloatRect spriteSize = m_logoSprite.getGlobalBounds();
	// Set origin in the middle of the sprite
	m_logoSprite.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);
	m_logoSprite.setPosition(m_window.getSize().x / 2., m_window.getSize().y / 2.);

	m_triangles.clear();
	vertex.color = sf::Color::White;
	for (int i = 0; i < 6; i++)
	{
		vertex.position = m_points[i];
		vertex.texCoords = m_textureCoOrds[i];
		m_triangles.append(vertex);
	}
	m_states.texture = &m_logoTexture;
	
	m_states.shader = &m_shader;

}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_instructionsText.setFont(m_ArialBlackfont);
	m_instructionsText.setCharacterSize(28U);
	m_instructionsText.setString("Use arrow keys to alter parameters \n\nUse arrow keys to alter parameters");
	m_instructionsText.setFillColor(sf::Color::Black);
	m_instructionsText.setPosition(200.0f, 170.0f);
}

