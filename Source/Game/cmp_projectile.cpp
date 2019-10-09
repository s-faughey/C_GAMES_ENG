#include "cmp_projectile.h"
#include "cmp_actor_movement.h"
#include "cmp_health.h"
#include "Game.h"
#include "SystemRenderer.h"
#include "cmp_sprite.h"
#include "cmp_char_sheet.h"
#include "cmp_status.h"
#include "EventSystem.h"

EventSystem* events = EventSystem::getInstance();

ProjectileComponent::ProjectileComponent(Entity *p) : Component(p) 
{

}

void ProjectileComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void ProjectileComponent::render()
{

}
void ProjectileComponent::update(double dt)
{
	if (!_parent->is_forDeletion())
	{
		int chance = rand() % 10 + 1;
		if (finishAnimation)
		{
			timer -= dt;
			if (timer < 0)
			{
				finishAnimation = false;
			}
		}
		if (!_parent->is_forDeletion())
			for (auto g : _entities)
				if (!g->is_forDeletion())
					if (length(g->getPosition() - _parent->getPosition()) < range*WX / 1280)
					{
						auto health_mana = g->GetComponent<HealthComponent>();
						if (!damage_dealt)
						{
							auto dmg = std::make_shared<Entity>();
							auto txt = dmg->addComponent<DamageTextComponent>();
							dmg->setPosition(g->getPosition());
							health_mana->reduceHealth(damage); //should be changed to the player's attack damage
							txt->setText(damage);
							gameScene->getEnts().push_back(dmg);
							events->addExp(type, 10);
							if (!conDmg)
								damage_dealt = true;
						}
						if (knockback)
						{
							auto d = g->GetComponent<ActorMovementComponent>();
							d->push((g->getPosition() - _parent->getPosition()));
						}
						if (chance > 5 && blind) {
							auto blindcmp = g->GetComponent<StatusComponent>();
							blindcmp->setBlinded();							
						}
						if (slow) {
							auto slowcmp = g->GetComponent<StatusComponent>();
							slowcmp->setSlowed();							
						}
						if (chance >= 4 && burn) {
							auto burncmp = g->GetComponent<StatusComponent>();
							burncmp->setBurning();
						}
						if (!indestructable)
						{
							if (!finishAnimation)
								_parent->setForDelete();
						}
					}
	}
	
}
