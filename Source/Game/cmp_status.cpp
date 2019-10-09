#include "cmp_status.h"
#include "cmp_sprite.h"
#include "Game.h"
#include "cmp_health.h"

StatusComponent::StatusComponent(Entity * p) : Component(p)
{
}

void StatusComponent::reset()
{
	burning = false;
	slowed = false;
	blinded = false;
}

void StatusComponent::render()
{
}

void StatusComponent::update(double dt)
{
	////timers for status
	if (blinded) {
		blindTimer -= dt;
		auto st = _parent->GetComponent<EnemyHealthBarComponent>();
		st->setBlind();
		if (blindTimer <= 0)
		{
			blinded = false;
			st->setNormal();
			blindTimer = 3.0f;
		}
	}
	if (burning) {
		burnDamageTimer -= dt;
		auto st = _parent->GetComponent<EnemyHealthBarComponent>();
		st->setBurn();
		if (burnDamageTimer < 0)
		{
			auto health = _parent->GetComponent<HealthComponent>();
			health->reduceHealth(5);
			auto dmg = std::make_shared<Entity>();
			auto txt = dmg->addComponent<DamageTextComponent>();
			dmg->setPosition(_parent->getPosition());
			txt->setText(5);
			gameScene->getEnts().push_back(dmg);
			burnDamageTimer = burnDamageDelay;
		}
		burnTimer -= dt;
		if (burnTimer <= 0) {
			burning = false;
			st->setNormal();
			burnTimer = 5.0f;
		}
	}
	if (slowed) {
		slowTimer -= dt;
		auto st = _parent->GetComponent<EnemyHealthBarComponent>();
		st->setSlow();
		if (slowTimer < 0) {
			slowed = false;
			slowTimer = 2.0f;
			st->setNormal();
		}
	}
}
