#include "levelsystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

std::unique_ptr<int[]> LevelSystem::_tiles;
std::unique_ptr<int[]> LevelSystem::_tiles2;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset = Vector2f{ 0 , 0 };
sf::Texture texture;
float LevelSystem::_tileSize = 25.0f;
vector<std::unique_ptr<sf::Sprite>> LevelSystem::_sprites;
vector<std::unique_ptr<sf::Sprite>> LevelSystem::_sprites2;


std::map<int, sf::IntRect> LevelSystem::_rects{

};
sf::IntRect LevelSystem::getRect(int t) {
	auto it = _rects.find(t);
	if (it == _rects.end()) {
		_rects[t] = { 32,32,16,16 };
	}
	return _rects[t];
}

void LevelSystem::fillRects()
{
	int id = 0;
	for (int j = 0; j < 31; j++)
	{
		for (int i = 0; i < 57; i++)
		{
			_rects.insert(std::pair<int, sf::IntRect>(id, {(i*17),(j*17),16,16}));
			id++;
		}
	}
	_rects.insert(std::pair<int, sf::IntRect>(-1, { 0, 85,16,16 }));
	_rects.insert(std::pair<int, sf::IntRect>(-5, { 0, 85,16,16 }));
	_rects.insert(std::pair<int, sf::IntRect>(-3, { 0, 85,16,16 }));
}
void LevelSystem::setRect(int t, sf::IntRect c) {
	_rects.insert(std::pair<int, sf::IntRect>(t, c));
}
void LevelSystem::loadLevelFile(const std::string &path, float tileSize) {
	_tileSize = tileSize;
	fillRects();
	size_t w = 0, h = 0;
	std::vector<int> buffer;

	//load file to buffer
	ifstream f(path);
	if (f.good())
	{
		int n = 0;
		std::string line;
		int line_number = 0;
		while (std::getline(f, line))
		{
			std::stringstream ss(line);
			int i;
			while (ss >> i)
			{
					buffer.push_back(i);
				if (ss.peek() == ',')
					ss.ignore();
			}
			h++;
			
		}
	}
	w = buffer.size() / h;

	std::vector<int> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i) {
		const int c = buffer[i];
		temp_tiles.push_back(c);		
	}
	
	//check for errors
	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level: " + path);
	}

	//make an array for the level
	_tiles = std::make_unique<int[]>(w * h);
	_width = w; //set width and height
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << " loaded! " << w << "x" << h << endl;
	buildSprites();
}
void LevelSystem::loadLevelFile2(const std::string &path) {

	size_t w = 0, h = 0;
	std::vector<int> buffer;

	//load file to buffer
	ifstream f(path);
	if (f.good())
	{
		int n = 0;
		std::string line;
		int line_number = 0;
		while (std::getline(f, line))
		{
			std::stringstream ss(line);
			int i;
			while (ss >> i)
			{
				buffer.push_back(i);
				if (ss.peek() == ',')
					ss.ignore();
			}
			h++;
		}
	}
	w = buffer.size() / h;

	std::vector<int> temp_tiles;
	for (int i = 0; i < buffer.size(); ++i) {
		const int c = buffer[i];
		temp_tiles.push_back(c);
	}

	//check for errors
	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level: " + path);
	}

	//make an array for the level
	_tiles2 = std::make_unique<int[]>(w * h);
	_width = w; //set width and height
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles2[0]);
	cout << "Level " << path << " loaded! " << w << "x" << h << endl;
	buildSprites2();
}
void LevelSystem::buildSprites() {
	_sprites.clear();
	if (!texture.loadFromFile("res/img/world.png")) {
		cout << "Cannot load texture!" << endl;
	}
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			auto s = make_unique<sf::Sprite>();
			s->setPosition(getTilePosition({ x, y }));
			s->setTexture(texture);
			s->setScale(Vector2f(_tileSize / 16, _tileSize / 16));
			s->setTextureRect(getRect(getTile({ x, y })));
			_sprites.push_back(move(s));

		}
	}
}
void LevelSystem::buildSprites2() {
	_sprites2.clear();
	if (!texture.loadFromFile("res/img/world.png")) {
		cout << "Cannot load texture!" << endl;
	}
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			auto s = make_unique<sf::Sprite>();
			s->setPosition(getTilePosition({ x, y }));
			s->setTexture(texture);
			s->setScale(Vector2f(_tileSize / 16, _tileSize / 16));
			s->setTextureRect(getRect(getTile2({ x, y })));
			_sprites2.push_back(move(s));

		}
	}
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p) {
	return (Vector2f(p.x * _tileSize, p.y * _tileSize));
}

int LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
	//	throw string("Tile out of range: ") + to_string(p.x) + "," +
			to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}
int LevelSystem::getTile2(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height) {
		throw string("Tile out of range: ") + to_string(p.x) + "," +
			to_string(p.y) + ")";
	}
	return _tiles2[(p.y * _width) + p.x];
}
bool LevelSystem::isWalkable(int id)
{
	if (id==285 || (id >= 526 && id <= 540) || (id >= 28 && id <= 31) || (id >= 361 && id <= 369) || (id >= 308 && id <= 312) || (id >= 251 && id <= 259) || (id >= 80 && id <= 88) || (id >= 194 && id <= 202) || (id >= 137 && id <= 145) || (id >= 583 && id <= 597) || (id >= 640 && id <= 654) || (id >= 697 && id <= 724) || (id >= 754 && id <= 781) || (id >= 811 && id <= 838) || (id >= 868 && id <= 895) || (id >= 925 && id <= 952) || (id >= 982 && id <= 1009) || (id >= 1096 && id <= 1124) || (id >= 1153 && id <= 1180) || (id >= 1210 && id <= 1237) || (id >= 1267 && id <= 1294) || (id >= 1324 && id <= 1351) || (id >= 1381 && id <= 1406))
		return false;
	else
		return true;
}
int LevelSystem::getTileAt(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		return -1;
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}
int LevelSystem::getTileAt2(Vector2f v) {
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0) {
		return -1;
	}
	return getTile2(Vector2ul((v - _offset) / (_tileSize)));
}
std::vector<sf::Vector2f> LevelSystem::findTiles(int t)
{
	vector<Vector2f> found;
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			if (getTile({ x, y }) == t) {
				found.push_back((getTilePosition(Vector2ul{ x, y }) + Vector2f(_tileSize / 2.0f, _tileSize / 2.0f)));
			}
		}
	}

	return found;
}
std::vector<sf::Vector2f> LevelSystem::findTiles2(int t)
{
	vector<Vector2f> found;
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			if (getTile2({ x, y }) == t) {
				found.push_back((getTilePosition(Vector2ul{ x, y }) + Vector2f(_tileSize / 2.0f, _tileSize / 2.0f)));
			}
		}
	}

	return found;
}



Vector2f LevelSystem::getStart()
{
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
			if (getTile({ x, y }) == -5) {
				return getTilePosition({ x, y }) + Vector2f(_tileSize / 2.0f, _tileSize / 2.f);
			}
		}
	}
}

void LevelSystem::Render(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites[i]);
	}

}
void LevelSystem::Render2(RenderWindow &window) {
	for (size_t i = 0; i < _width * _height; ++i) {
		window.draw(*_sprites2[i]);
	}

}