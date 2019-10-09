#include <iostream>
#include "cmp_enemy_attack.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_status.h"
#include "ItemGenerator.h"
#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include "cmp_items.h"
#include "Game.h"
#include "cmp_char_sheet.h"
#include <string>


ItemGenerator* items = ItemGenerator::getInstance();

EnemyAttackComponent::EnemyAttackComponent(Entity *p) : Component(p) 
{
	
}

void EnemyAttackComponent::render()
{

}
void EnemyAttackComponent::update(double dt)
{
	auto hp = _parent->GetComponent<HealthComponent>();
	//////////////WHEN ENEMY DIES////////////////////////
	if (hp->getHealth() < 0)
	{
		items->random_drop(level, _parent->getPosition());
		_parent->setForDelete();
	}
	
	if (!_parent->is_forDeletion())
	{
		///////////////////////////////////////////////////////WHEN PLAYER TOUCHES THE ENEMY//////////////////////////////////
		if (length(_parent->getPosition() - player->getPosition()) < 20.0f*WX/1280)
		{
			int player_def = player->GetComponent<CharacterSheetComponent>()->getStatDefence();
			auto status = _parent->GetComponent<StatusComponent>();
			bool blindStatus = status->getBlinded();
			if (!blindStatus) {
				auto hp = player->GetComponent<HealthComponent>();
				auto d = player->GetComponent<PlayerMovementComponent>();
				d->push((player->getPosition() - _parent->getPosition()));
				auto pp = player->GetComponent<CharacterSpriteComponent>();
				if(player_def<attack)
				hp->reduceHealth(attack-player_def);
			}
		}
	}
	
}
