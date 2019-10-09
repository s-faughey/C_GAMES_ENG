#pragma once
#include "ecm.h"
#include <string>

#define BPslots 21
class HudComponent : public Component {

protected:
	bool highlighted = false;
	bool showInventory = false;
	bool hideInventory = false;
	float buttonDelay = 0.0f;
	sf::RectangleShape HP;
	sf::RectangleShape MP;
	sf::RectangleShape STAM;
	////////////SKILL INTICATORS////////////////////////////////////
	sf::RectangleShape buttonsBackground;	
	sf::RectangleShape skill1;
	sf::RectangleShape skill2;
	sf::RectangleShape skill3;
	sf::RectangleShape skill4;
	sf::RectangleShape skill5;

	sf::Text label_skill1;
	sf::Text label_skill2;
	sf::Text label_skill3;
	sf::Text label_skill4;
	sf::Text label_skill5;

	/////////////////////////////////////////INGAME MENU BUTTONS
	sf::RectangleShape button_inventory;
	sf::RectangleShape button_skill_tree;
	sf::RectangleShape button_menu;
	sf::RectangleShape button_save;
	//////////////////////////////////////////inventory window
	sf::RectangleShape inventory;
	sf::RectangleShape backpack;
	sf::RectangleShape slots[BPslots];
	sf::RectangleShape statsArea;
	sf::Text label_backpack;
	sf::Text label_stats;
	sf::Text label_equipped;
	sf::RectangleShape equippedArea;
	sf::RectangleShape helmet;
	sf::RectangleShape armour;
	sf::RectangleShape boots;
	sf::RectangleShape weapon;
	sf::RectangleShape shield;

	////////////////////////////ICONS
	sf::Sprite icon_weapon;
	sf::Sprite icon_armour;
	sf::Sprite icon_boots;
	sf::Sprite icon_helmet;
	sf::Sprite icon_shield;

	sf::Sprite icon_inventory;
	sf::Sprite icon_menu;
	sf::Sprite icon_save;
	sf::Sprite icon_skills;
	float sliderX=0;
	float slideTime = 0.2f;


	float maxHealth;
	float health;
	float maxMana;
	float mana;
	float stamina;
	float maxStamina;

	sf::Text text;
	

	///////////////////////ITEM INTERACTION
	sf::RectangleShape infoArea;
	bool displayInfo = false;
	bool displayItemOptions = false;
	sf::Text itemInfo;
	//////////////item options
	sf::RectangleShape itemOptionsArea;
	sf::Text itemOptionsEquip;
	sf::Text itemOptionsDrop;
	

	/////////////STATS TEXT
	sf::Text experience_levels;
	sf::RectangleShape progressBar_Melee;
	sf::RectangleShape progressBar_Melee_BG;
	sf::RectangleShape progressBar_Fire;
	sf::RectangleShape progressBar_Fire_BG;
	sf::RectangleShape progressBar_Water;
	sf::RectangleShape progressBar_Water_BG;
	sf::RectangleShape progressBar_Wind;
	sf::RectangleShape progressBar_Wind_BG;
	sf::RectangleShape progressBar_Earth;
	sf::RectangleShape progressBar_Earth_BG;


	sf::Text label_skill_tree;
	sf::RectangleShape skill_tree;
	sf::RectangleShape fire_tree;
	sf::RectangleShape water_tree;
	sf::RectangleShape wind_tree;
	sf::RectangleShape earth_tree;

	sf::Text label_fire, label_water, label_wind, label_earth;

	sf::RectangleShape info_spells_area;
	sf::Text info_spells_text;
	sf::Sprite spell_slots[20];
	sf::Sprite equipped_spells[5];
	bool spell_available[20];
	int spell_ids[20] = {0,5,9,-1,-1, 1,6,-1,-1,-1, 2, 7,-1,-1,-1, 3 ,8,-1,-1,-1};
	int id_to_slot[21] = { 0,   ///////////ID 0 = SLOT 0 ////// FIREBALL
							5, ///////////ID 1 = SLOT 5 ////// Water gun
							10, ///////////ID 2 = SLOT 10 ////// Sonic Boom
							15, ///////////ID 3 = SLOT 15 ////// Earth spike
							-1, ///////////ID 4                  SWORD SWING
							1, ///////////ID 5 = SLOT 1 ////// Dragonbreath
							6,  ///////////ID 6 = SLOT 6 ////// ice barrage
							11,  ///////////ID 7 = SLOT 11 ////// wind scythe
							16, ///////////ID 8 = SLOT 16 ////// earth boulder
							2,  ///////////ID 9 = SLOT 2 ////// earth boulder
							0,
							5,
							10,
							15,
							1,
							0,5,10,15,1,1 };
	sf::Text label_spell_options_1, label_spell_options_2, label_spell_options_3, label_spell_options_4, label_spell_options_5;
	sf::RectangleShape bg_spell_options;
	std::vector<std::string> descriptions;
	bool show_spell_info = false;
	bool show_spell_options = false;
	bool show_skill_tree = false;
	bool hide_skill_tree = false;
	float tree_sliderX = 0;
	float tree_slideTime = 0.2f;
public:
	///////////////EQUIPPED ITEMS///////////
	void reload();
	void getStats();
	void resetButtons();
	void resetSlot(int i);
	void set(float health, float maxhealth, float mana, float maxmana, float stam, float maxstam);
	explicit HudComponent(Entity *p);
	HudComponent() = delete;
	void setMaxHealth(float maxHealth);
	void setHealth(float health);
	void setMaxMana(float maxMana);
	void setMana(float mana);
	void setText();
	void setPosition();
	void render() override;
	void update(double dt) override;
};
