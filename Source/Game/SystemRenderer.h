#pragma once
#include <SFML/Graphics.hpp>

namespace  Renderer
{

	constexpr uint16_t gameWidth[3] = { 1280,1600, 1920};
	constexpr uint16_t gameHeight[3] = { 720,900, 1080};
	void initialise(sf::RenderWindow &);
	sf::RenderWindow &getWindow();
	void shutdown();
	void fullscreen();
	void not_fullscreen();
	void update(const double &);
	void queue(const sf::Drawable *s);
	void queue(int priority, const sf::Drawable *s);
	void queue(const sf::Drawable *s);
	void render();
	void setCenter(sf::Vector2f pos);
	void resizeView();
};
