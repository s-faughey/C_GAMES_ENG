#include "Game.h"
#include "ecm.h"
#include "cmp_items.h"
#include <string>

class ItemGenerator
{
private:
	ItemGenerator();
	static ItemGenerator* instance;
public:
	void load(int id, bool equipped);
	static ItemGenerator* getInstance();
	~ItemGenerator();

	void create_forbidden_item(sf::Vector2f location);
	void create_iron_helmet(sf::Vector2f location);
	void create_leaf(sf::Vector2f location);
	void create_dagger(sf::Vector2f location);
	void create_short_sword(sf::Vector2f location);
	void create_templar_sword(sf::Vector2f location);
	void create_giant_sword(sf::Vector2f location);
	void create_magic_sword(sf::Vector2f location);
	void create_simple_shield(sf::Vector2f location);
	void create_nike_jordans(sf::Vector2f location);

	void recreate_forbidden_item(bool equipped);
	void recreate_iron_helmet(bool equipped);
	void recreate_leaf(bool equipped);
	void recreate_dagger(bool equipped);
	void recreate_short_sword(bool equipped);
	void recreate_templar_sword(bool equipped);
	void recreate_giant_sword(bool equipped);
	void recreate_magic_sword(bool equipped);
	void recreate_simple_shield(bool equipped);
	void recreate_nike_jordans(bool equipped);


	void random_drop(int level,sf::Vector2f location);
};