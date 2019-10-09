#pragma once
#include "ecm.h"
#include <string>

class WorldItemComponent : public Component {
protected:
	int map_id;
	bool mapChanger = false;
	bool teleporter = false;
	sf::Vector2f destination;
	sf::Clock timer;
	int i = 0;
	int y = 0;
	bool world_text = false;
	sf::RectangleShape dialogueBox;
	std::string dialogue;
	sf::Text text;
	bool trigger = false;
	bool dialogueFinished = false;
public:
	void setTeleporter() { teleporter = true; }
	void setTeleportDestination(sf::Vector2f x) { destination = x; }
	void setWorldText() { world_text = true; }
	void setDialogue(std::string x);

	void setMapChanger(int i) { mapChanger = true; map_id = i; }
	WorldItemComponent() = delete;
	explicit WorldItemComponent(Entity *p);
	void update(double dt) override;
	
	void render() override;
	void interact();	
	
};