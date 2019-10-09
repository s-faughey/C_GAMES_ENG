#pragma once
#include "ecm.h"
#define MAX_LEVEL 10
class CharacterSheetComponent : public Component {

protected:
	bool componentsReady = false;
	int dropped_items = 0;
	std::shared_ptr<Entity> helmet;
	std::shared_ptr<Entity> armour;
	std::shared_ptr<Entity> boots;
	std::shared_ptr<Entity> weapon;
	std::shared_ptr<Entity> shield;
	int selectedSpells[5] = { 0 ,1, 2, 3, 4 };
	std::vector <std::shared_ptr<Entity>> _backpack;
	//////////////////////////////////SKILLS TO TRAIN/////////////////////////
	float level_melee=0;
	float level_fire=0;
	float level_water = 0;
	float level_wind = 0;
	float level_earth = 0;
	float experience_melee = 0;
	float experience_fire = 0;
	float experience_water = 0;
	float experience_wind = 0;
	float experience_earth = 0;
	float experience_thresholds[MAX_LEVEL];
	///////////////////////////////GENERAL STATS//////////////////////////////
	float stat_melee_attack = 5;
	float stat_defence = 0;
	float stat_speed = 0;
public:
	int getSpell(int i) { return selectedSpells[i]; }
	void setSpell(int pos, int id) { selectedSpells[pos] = id; }
	void dropOne() { dropped_items++; }
	float getRequiredExp(int level) { return experience_thresholds[level]; }
	float getLevelMelee() { return level_melee; }
	float getLevelFire() { return level_fire; }
	float getLevelWater() { return level_water; }
	float getLevelWind() { return level_wind; }
	float getLevelEarth() { return level_earth; }
	float getExpMeele() { return experience_melee; }
	float getExpFire() { return experience_fire; }
	float getExpWater() { return experience_water; }
	float getExpWind() { return experience_wind; }
	float getExpEarth() { return experience_earth; }
	float getStatAttack() { return stat_melee_attack; }
	float getStatDefence() { return stat_defence; }
	float getStatSpeed() { return stat_speed; }
	void addEXP(int stat, float amount); ///////0-melee and in order as defined
	std::shared_ptr<Entity> getHelmet() { return helmet; }
	std::shared_ptr<Entity> getArmour() { return armour; }
	std::shared_ptr<Entity> getBoots() { return boots; }
	std::shared_ptr<Entity> getWeapon() { return weapon; }
	std::shared_ptr<Entity> getShield() { return shield; }
	void equip( std::shared_ptr<Entity>& item);
	std::vector<std::shared_ptr<Entity>> &getBP() { return _backpack; };
	std::vector<std::string> getBPINFO();
	bool pickUp(std::shared_ptr<Entity>& item);
	explicit CharacterSheetComponent(Entity *p);
	CharacterSheetComponent() = delete;
	void setLevels(int a, int b, int c, int d, int e);
	void setExperience(int a, int b, int c, int d, int e);
	void reset();
	std::string saveLevels();
	std::string saveExperience();
	std::string saveItems();
	std::string saveLocation();
	std::string saveControls();
	std::string saveSpells();
	void render() override;
	void update(double dt) override;
	
};

