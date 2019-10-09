#include <iostream>
#include "EventSystem.h"
#include "cmp_attack.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "cmp_char_sheet.h"
#include "Game.h"
#include "SpellCaster.h"
#include <string>

SpellCaster* spells = SpellCaster::getInstance();

std::vector<float> cooldownTimes = spells->getCooldowns();
std::vector<float> cooldowns = spells->getCooldowns();


AttackComponent::AttackComponent(Entity *p) : Component(p) 
{
	
}

void AttackComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void AttackComponent::render() 
{
}
void AttackComponent::update(double dt) 
{
	EventSystem* events = EventSystem::getInstance();
	auto char_sheet = _parent->GetComponent<CharacterSheetComponent>();
	auto health_mana = _parent->GetComponent<HealthComponent>();

	static float attackTime = 0.0f;
	attackTime -= dt;
	for (int i = 0; i < cooldowns.size(); i++)
	{
		cooldowns[i] -= dt;
	}
	int spell1 = char_sheet->getSpell(0);
	int spell2 = char_sheet->getSpell(1);
	int spell3 = char_sheet->getSpell(2);
	int spell4 = char_sheet->getSpell(3);
	int spell5 = char_sheet->getSpell(4);
	if (sf::Keyboard::isKeyPressed(controls[5]) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, sf::Joystick::Z)))
	{
		if (cooldowns[spell1] < 0)
		{
			spells->cast_spell_id(spell1, _parent->getPosition());
			cooldowns[spell1] = cooldownTimes[spell1];
		}
	}
	if (sf::Keyboard::isKeyPressed(controls[6]) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, sf::Joystick::X)))
	{
		if (cooldowns[spell2] < 0)
		{
			spells->cast_spell_id(spell2, _parent->getPosition());
			cooldowns[spell2] = cooldownTimes[spell2];
		}
	}
	if (sf::Keyboard::isKeyPressed(controls[7]) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, sf::Joystick::Y)))
	{
		if (cooldowns[spell3] < 0)
		{
			spells->cast_spell_id(spell3, _parent->getPosition());
			cooldowns[spell3] = cooldownTimes[spell3];
		}
	}
	if (sf::Keyboard::isKeyPressed(controls[8]) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, sf::Joystick::R)))
	{
		if (cooldowns[spell4] < 0)
		{
			spells->cast_spell_id(spell4, _parent->getPosition());
			cooldowns[spell4] = cooldownTimes[spell4];
		}
	}
	if (sf::Keyboard::isKeyPressed(controls[9]))
	{
		if (cooldowns[spell5] < 0)
		{
			spells->cast_spell_id(spell5, _parent->getPosition());
			cooldowns[spell5] = cooldownTimes[spell5];
		}
	}
	if (sf::Keyboard::isKeyPressed(controls[4]) || (sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, sf::Joystick::V)))
	{
		if (cooldowns[4] < 0)
		{
			spells->cast_spell_id(4, _parent->getPosition());
			cooldowns[4] = cooldownTimes[4];
		}
	}
	
}
