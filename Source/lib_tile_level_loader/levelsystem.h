#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include "maths.h"

#define ls LevelSystem

class LevelSystem {
public:

	//static sf::Texture texture;
	static void loadLevelFile(const std::string&, float tileSize);
	static void loadLevelFile2(const std::string&);
	static void Render(sf::RenderWindow &window);
	static void Render2(sf::RenderWindow &window);
	static sf::IntRect getRect(int t);
	static void setRect(int t, sf::IntRect);
	//get tile at coordinate
	static int getTile(sf::Vector2ul);
	static int getTile2(sf::Vector2ul);
	//get screenspace coords of tile
	static sf::Vector2f getTilePosition(sf::Vector2ul);
	//get tile at screen space pos
	static int getTileAt(sf::Vector2f);
	static int getTileAt2(sf::Vector2f);
	static std::vector<sf::Vector2f> findTiles(int t);
	static std::vector<sf::Vector2f> findTiles2(int t);
	const static size_t getHeight() {return _height;}
	const static size_t getWidth() {return _width;}
	static sf::Vector2f getStart();
	static bool isWalkable(int id);
	static void fillRects();
//	static void setTexture(sf::Texture a) { texture = a; }
protected:

	static std::unique_ptr<int[]> _tiles;
	static size_t _width;
	static size_t _height;
	static float _tileSize;
	static sf::Vector2f _offset;
	static std::map<int, sf::IntRect> _rects;
	static std::vector< std::unique_ptr < sf::Sprite>> _sprites;

	static std::unique_ptr<int[]> _tiles2;
	static std::vector< std::unique_ptr < sf::Sprite>> _sprites2;
	static void buildSprites();
	static void buildSprites2();

private:
	LevelSystem() = delete;
	~LevelSystem() = delete;
};