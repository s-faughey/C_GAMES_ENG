#pragma once
#include "ecm.h"
#include "cmp_sprite.h"
#include "Game.h"
#include "SystemRenderer.h"
#include <string>

class ItemComponent : public Component {
protected:
	bool equipped = false;
	bool pickedUp = false;
	sf::RectangleShape highlight;
	int id = 0;
	std::string name = "?";
	std::shared_ptr<sf::Sprite> _sprite;
	std::shared_ptr<Entity> _this;
	ITEM_TYPE type;
	float att=0;  // adds to physical attack
	float def=0;  // adds to defence
	float spd=0;	// increases movement speed
public:
	void setPickedUp() { pickedUp = true; }
	explicit ItemComponent(Entity *p);
	ItemComponent() = delete;
	void setID(int i) { id = i; }
	int getID() { return id; }
	//////////////////////SET/GET ITEM PROPERTIES///////////////////
	void setName(std::string a) { name = a; }
	bool isEquipped() { return equipped; }
	void equip() { equipped = true;  }
	void unequip() { equipped = false;  }
	std::string getName() { return name; }
	void setType(ITEM_TYPE x) { type = x; }
	void point(std::shared_ptr<Entity>& x) { _this = x; };
	ITEM_TYPE getType() { return type; }
	void setAtt(float a) { att = a; }
	float getAtt() { return att; }
	void setDef(float a) { def = a; }
	float getDef() { return def; }
	void setSpd(float a) { spd = a; }
	float getSpd() { return spd; }

	sf::Sprite &getSprite();
	void render() override;
	void update(double dt) override;
	
};

