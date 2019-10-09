
#include "ItemGenerator.h"
#include "cmp_char_sheet.h"

ItemGenerator* ItemGenerator::instance;
ItemGenerator::ItemGenerator()
{
	
}
ItemGenerator* ItemGenerator::getInstance()
{
	if (instance == 0)
	{
		instance = new ItemGenerator();
	}

	return instance;
}
ItemGenerator::~ItemGenerator()
{
}
void ItemGenerator::load(int id, bool equipped)
{
	switch (id)
	{
	case 0:
		recreate_iron_helmet(equipped);
		break;
	case 1:
		recreate_leaf(equipped);
		break;
	case 2:
		recreate_dagger(equipped);
		break;
	case 3:
		recreate_short_sword(equipped);
		break;
	case 4:
		recreate_templar_sword(equipped);
		break;
	case 5:
		recreate_giant_sword(equipped);
		break;
	case 6:
		recreate_magic_sword(equipped);
		break;
	case 7:
		recreate_simple_shield(equipped);
		break;
	case 8:
		recreate_nike_jordans(equipped);
		break;
	default:
		break;
	}
}
void ItemGenerator::random_drop(int level, sf::Vector2f location)
{
	int drop = rand() % 100;
	switch (level)
	{
	case 0:
		if (drop >= 0 && drop < 10)
			create_iron_helmet(location);
		if (drop >= 10 && drop < 20)
			create_leaf(location);
		if (drop >= 20 && drop < 30)
			create_dagger(location);
		if (drop >= 30 && drop < 35)
			create_simple_shield(location);
		break;
	case 1:
		if (drop >= 0 && drop < 10)
			create_short_sword(location);	
		if (drop >= 10 && drop < 15)
			create_templar_sword(location);
		if (drop >= 15 && drop < 20)
			create_giant_sword(location);
		if (drop >= 20 && drop < 35)
			create_simple_shield(location);
		if (drop >= 35 && drop < 55)
			create_nike_jordans(location);
		break;
	case 2:
		if (drop >= 0 && drop < 5)
			create_templar_sword(location);
		break;
	case 3:
		if (drop >= 0 && drop < 2)
			create_giant_sword(location);
		break;
	case 4:
		if (drop >= 0 && drop < 5)
			create_giant_sword(location);
		break;
	case 5:
		if (drop >= 0 && drop < 2)
			create_magic_sword(location);
		break;
	default:
		break;
	}
}
void ItemGenerator::create_iron_helmet(sf::Vector2f location)
{
		auto item = std::make_shared<Entity>();
		item->setPosition(location);
		auto it = item->addComponent<ItemComponent>();
		it->setID(0);
		it->point(item);
		it->setName("IRON HELMET");
		it->setType(HELMET);
		it->setDef(10);
		it->getSprite().setTexture(itemsTexture);
		it->getSprite().setTextureRect({ 0,144,16,16 });
		it->getSprite().setScale({ 2*WX / 1280,2*WY / 720 });
		it->getSprite().setOrigin({ 8,8 });
		activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_iron_helmet(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	item->setPosition({ 100,100 });
	it->setPickedUp();
	it->setID(0);
	it->point(item);
	it->setName("Iron Helmet");
	it->setType(HELMET);
	it->setDef(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 0,144,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}

void ItemGenerator::create_leaf(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(1);
	it->point(item);
	it->setName("Leaf");
	it->setType(ARMOUR);
	it->setDef(1);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,192,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_leaf(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(1);
	it->point(item);
	it->setName("Leaf");
	it->setType(ARMOUR);
	it->setPickedUp();
	it->setDef(1);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,192,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_dagger(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(2);
	it->point(item);
	it->setName("Dagger");
	it->setType(WEAPON);
	it->setAtt(5);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 0,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_dagger(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(2);
	it->point(item);
	it->setName("Dagger");
	it->setPickedUp();
	it->setType(WEAPON);
	it->setAtt(5);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 0,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_short_sword(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(3);
	it->point(item);
	it->setName("Short Sword");
	it->setType(WEAPON);
	it->setAtt(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_short_sword(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(3);
	it->point(item);
	it->setName("Short Sword");
	it->setPickedUp();
	it->setType(WEAPON);
	it->setAtt(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 16,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_templar_sword(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(4);
	it->point(item);
	it->setName("Templar Sword");
	it->setType(WEAPON);
	it->setAtt(22);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 32,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_templar_sword(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(4);
	it->point(item);
	it->setName("Templar Sword");
	it->setType(WEAPON);
	it->setPickedUp();
	it->setAtt(22);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 32,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_giant_sword(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(5);
	it->point(item);
	it->setName("Giant Sword");
	it->setType(WEAPON);
	it->setAtt(38);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 48,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_giant_sword(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(5);
	it->point(item);
	it->setName("Giant Sword");
	it->setPickedUp();
	it->setType(WEAPON);
	it->setAtt(38);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 48,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_magic_sword(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(6);
	it->point(item);
	it->setName("Magic Sword");
	it->setType(WEAPON);
	it->setAtt(60);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 192,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_magic_sword(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(6);
	it->point(item);
	it->setName("Magic Sword");
	it->setType(WEAPON);
	it->setPickedUp();
	it->setAtt(60);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 192,112,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_forbidden_item(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(-1);
	it->point(item);
	it->setName("?");
	it->setType(WEAPON);
	it->setAtt(150);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 192,128,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_forbidden_item(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	it->setID(-1);
	it->point(item);
	it->setName("?");
	it->setType(WEAPON);
	it->setPickedUp();
	it->setAtt(150);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 192,128,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_simple_shield(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(7);
	it->point(item);
	it->setName("SIMPLE SHIELD");
	it->setType(SHIELD);
	it->setDef(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 80,176,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_simple_shield(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	item->setPosition({ 100,100 });
	it->setPickedUp();
	it->setID(7);
	it->point(item);
	it->setName("SIMPLE SHIELD");
	it->setType(SHIELD);
	it->setDef(10);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 80,176,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}
void ItemGenerator::create_nike_jordans(sf::Vector2f location)
{
	auto item = std::make_shared<Entity>();
	item->setPosition(location);
	auto it = item->addComponent<ItemComponent>();
	it->setID(8);
	it->point(item);
	it->setName("NIKE JORDANS");
	it->setType(BOOTS);
	it->setDef(2);
	it->setSpd(20);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 80,160,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
}
void ItemGenerator::recreate_nike_jordans(bool equipped)
{
	auto item = std::make_shared<Entity>();
	auto it = item->addComponent<ItemComponent>();
	item->setPosition({ 100,100 });
	it->setPickedUp();
	it->setID(8);
	it->point(item);
	it->setName("NIKE JORDANS");
	it->setType(BOOTS);
	it->setDef(2);
	it->setSpd(20);
	it->getSprite().setTexture(itemsTexture);
	it->getSprite().setTextureRect({ 80,160,16,16 });
	it->getSprite().setScale({ 2 * WX / 1280,2 * WY / 720 });
	it->getSprite().setOrigin({ 8,8 });
	activeScene->getEnts().push_back(item);
	auto x = player->GetComponent<CharacterSheetComponent>();
	x->pickUp(item);
	if (equipped) x->equip(item);
}