/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
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
	
	void setupShaders();
	void setupSprite();
	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Shader m_shader;
	sf::Font m_ArialBlackfont;
	sf::Text m_instructionsText;

	sf::Texture m_distortionMap;
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo

	float m_distortionFactor = .05f;
	float m_riseFactor = .2f;
	sf::Clock m_shader_timer;
	bool m_exitGame; // control exiting game

	sf::RenderStates m_states;

	sf::Vector2f m_points[6] = {
				{50.0f,50.0f},
				{150.0f,50.0f},
				{50.0f,150.0f},
				{150.0f,50.0f},
				{150.0f,150.0f},
				{50.0f,150.0f} };
	sf::Vector2f m_textureCoOrds[6] = {
		{0.0f, 0.0f},
		{256.0f, 0.0f},
		{0.0f, 256.0f},
		{256.0f, 0.0f},
		{256.0f, 256.0f},
		{0.0f, 256.0f}
	};
	sf::VertexArray m_triangles{ sf::Triangles };

};

#endif // !GAME_HPP

