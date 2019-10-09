#include "Game.h"
#include "cmp_char_sheet.h"
#include "cmp_items.h"
#include "EventSystem.h"


CharacterSheetComponent::CharacterSheetComponent(Entity *p) : Component(p)
{
	//////////////////////exp to progress befween levels
	experience_thresholds[0] = 100;
	experience_thresholds[1] = 200;
	experience_thresholds[2] = 300;
	experience_thresholds[3] = 400;
	experience_thresholds[4] = 500;
	experience_thresholds[5] = 700;
	experience_thresholds[6] = 800;
	experience_thresholds[7] = 900;
	experience_thresholds[8] = 1000;
	experience_thresholds[9] = 2000;

}
void CharacterSheetComponent::addEXP(int stat, float amount)
{
	switch (stat)
	{
	case 0:
		if(level_melee<MAX_LEVEL)
		experience_melee += amount;
	break;
	case 1:
		if (level_fire<MAX_LEVEL)
		experience_fire += amount;
		break;
	case 2:
		if (level_water<MAX_LEVEL)
		experience_water += amount;
		break;
	case 3:
		if (level_wind<MAX_LEVEL)
		experience_wind += amount;
		break;
	case 4:
		if (level_earth<MAX_LEVEL)
		experience_earth += amount;
		break;
	default:
		break;
	}
}
void CharacterSheetComponent::equip(std::shared_ptr<Entity>& item)
{
	auto x = item->GetComponent<ItemComponent>();
	x->equip();
	switch (x->getType())
	{
	case WEAPON:
		if(weapon!=nullptr && weapon !=item)
			weapon->GetComponent<ItemComponent>()->unequip();
		weapon = item;
		break;
	case SHIELD:
		if (shield != nullptr && shield != item)
			shield->GetComponent<ItemComponent>()->unequip();
		shield = item;
		break;
	case HELMET:
		if (helmet != nullptr && helmet != item)
			helmet->GetComponent<ItemComponent>()->unequip();
		helmet = item;
		break;
	case ARMOUR:
		if (armour != nullptr && armour != item)
			armour->GetComponent<ItemComponent>()->unequip();
		armour = item;
		break;
	case BOOTS:
		if (boots != nullptr && boots!=item)
			boots->GetComponent<ItemComponent>()->unequip();
		boots = item;
		break;
	default:
		break;
	}
}
void CharacterSheetComponent::render()
{
}
std::string CharacterSheetComponent::saveLocation()
{
	return std::to_string((int)activeScene->getID()) + "," + std::to_string((int)player->getPosition().x) + "," + std::to_string((int)player->getPosition().y);
}
std::string CharacterSheetComponent::saveLevels()
{
	return std::to_string((int)level_melee) + "," + std::to_string((int)level_fire) + "," + std::to_string((int)level_water) + "," + std::to_string((int)level_wind) + "," + std::to_string((int)level_earth);
}
std::string CharacterSheetComponent::saveExperience()
{
	return std::to_string((int)experience_melee) + "," + std::to_string((int)experience_fire) + "," + std::to_string((int)experience_water) + "," + std::to_string((int)experience_wind) + "," + std::to_string((int)experience_earth);
}
std::string CharacterSheetComponent::saveItems()
{
	std::string temp="";
	for (auto items : _backpack)
	{
		if (!items->is_forDeletion())
		{
			auto inf = items->GetComponent<ItemComponent>();
			temp.append(std::to_string((int)inf->getID()) + ",");
			if (inf->isEquipped())
				temp.append(std::to_string(1) + ",");
			else
				temp.append(std::to_string(0) + ",");
		}

	}
	return temp;
}
std::string CharacterSheetComponent::saveControls()
{
	std::string temp = "";
	for (int i=0;i<12;i++)
	{
		temp.append(std::to_string((int)controls[i]) + ",");
	}
	return temp;
}
std::string CharacterSheetComponent::saveSpells()
{
	return std::to_string(selectedSpells[0]) + "," + std::to_string(selectedSpells[1]) + "," + std::to_string(selectedSpells[2]) + "," + std::to_string(selectedSpells[3]) + "," + std::to_string(selectedSpells[4]);
}
void CharacterSheetComponent::reset()
{
	for (auto n : _backpack)
	{
		n->setForDelete();
		n.reset();
	}
}
void CharacterSheetComponent::setLevels(int a, int b, int c, int d, int e) 
{
	reset();
	level_melee = a;
	level_fire = b;
	level_water = c;
	level_wind = d;
	level_earth = e;
}
void CharacterSheetComponent::setExperience(int a, int b, int c, int d, int e)
{
	experience_melee = a;
	experience_fire = b;
	experience_water = c;
	experience_wind = d;
	experience_earth = e;
}
void CharacterSheetComponent::update(double dt)
{	
	if (weapon != nullptr)
		if (!weapon->is_forDeletion())
			stat_melee_attack = 5.0f + (level_melee + weapon->GetComponent<ItemComponent>()->getAtt()) *2.0f;
		else
			stat_melee_attack = 5.0f + level_melee * 2.0f;
	else
		stat_melee_attack = 5.0f + level_melee * 2.0f;
	///////////////////////////////////////making sure items are equipped first, otherwise 0//////////////////
	float helmet_def = 0;
	float armour_def = 0;
	float shield_def = 0;
	float boots_def = 0;
	if (helmet != nullptr)
		if(!helmet->is_forDeletion())
			helmet_def = helmet->GetComponent<ItemComponent>()->getDef();
	if (armour != nullptr)
		if (!armour->is_forDeletion())
			armour_def = armour->GetComponent<ItemComponent>()->getDef();
	if (shield != nullptr)
		if (!shield->is_forDeletion())
			shield_def = shield->GetComponent<ItemComponent>()->getDef();
	if (boots != nullptr)
		if (!boots->is_forDeletion())
			boots_def = boots->GetComponent<ItemComponent>()->getDef();

	stat_defence = level_melee * 0.5f + helmet_def + armour_def + shield_def + boots_def;
	if(boots != nullptr)
		if (!boots->is_forDeletion())
			stat_speed = boots->GetComponent<ItemComponent>()->getSpd();
	EventSystem* evs = EventSystem::getInstance();
	if (experience_melee >= experience_thresholds[(int)level_melee] && level_melee<MAX_LEVEL)
	{
		experience_melee =  experience_melee - experience_thresholds[(int)level_melee];
		level_melee++;
		evs->switch_level_up();
	}
	if (experience_fire >= experience_thresholds[(int)level_fire] && level_fire<MAX_LEVEL)
	{
		experience_fire = experience_fire - experience_thresholds[(int)level_fire];
		level_fire++;
		evs->switch_level_up();
	}
	if (experience_water >= experience_thresholds[(int)level_water] && level_water<MAX_LEVEL)
	{
		experience_water = experience_water - experience_thresholds[(int)level_water];
		level_water++;
		evs->switch_level_up();
	}
	if (experience_wind >= experience_thresholds[(int)level_wind] && level_wind<MAX_LEVEL)
	{
		experience_wind = experience_wind - experience_thresholds[(int)level_wind];
		level_wind++;
		evs->switch_level_up();
	}
	if (experience_earth >= experience_thresholds[(int)level_earth] && level_earth<MAX_LEVEL)
	{
		experience_earth = experience_earth - experience_thresholds[(int)level_earth];
		level_earth++;
		evs->switch_level_up();
	}
}
std::vector<std::string> CharacterSheetComponent::getBPINFO()
{
	std::vector<std::string> temp;
	for (auto item : _backpack)
	{
		auto text = item->GetComponent<ItemComponent>();
		temp.push_back(" " + text->getName() + "\nAttack: " + std::to_string((int)text->getAtt()) + "\nDefence: " + std::to_string((int)text->getDef()) + "\nSpeed: " + std::to_string((int)text->getSpd()));
	}
	return temp;
}
bool CharacterSheetComponent::pickUp(std::shared_ptr<Entity>& item)
{
	if (_backpack.size() < 21+dropped_items)
	{
		_backpack.push_back(item);
		return true;
	}		
	return false;
}