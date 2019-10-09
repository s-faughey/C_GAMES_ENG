#include "Game.h"
#include "ecm.h"
#include "cmp_items.h"
#include <string>

class SpellCaster
{
private:
	SpellCaster();
	std::vector <std::shared_ptr<Entity>> _entities;
	static SpellCaster* instance;
	std::vector<float> cooldowns;
public:
	static SpellCaster* getInstance();
	~SpellCaster()=default;

	std::vector<float> getCooldowns() { return cooldowns; }
	void cast_spell_id(int id, sf::Vector2f location);
	
	void setEntities(std::vector <std::shared_ptr<Entity>>& e);

	/////////////SPELLS IN ORDER BY ID
	void cast_fire_ball(sf::Vector2f location);//////0
	void cast_water_gun(sf::Vector2f location);//////1
	void cast_sonic_boom(sf::Vector2f location);//////2
	void cast_earth_spike(sf::Vector2f location);//////3
	void cast_sword_swing(sf::Vector2f location);//////4
	void cast_dragon_breath(sf::Vector2f location);//////5
	void cast_ice_barrage(sf::Vector2f location);///////6
	void cast_wind_scythe(sf::Vector2f location);///////7
	void cast_rolling_boulder(sf::Vector2f location);///////7
	void cast_explosion(sf::Vector2f location);//////////8
};