#include "cmp_health.h"
#include "cmp_status.h"



HealthComponent::HealthComponent(Entity *p) : Component(p) 
{
	health = 150;
	mana = 250;
	maxHealth = 150;
	maxMana = 250;
	stamina = 100;
	maxStamina = 100;
}
void HealthComponent::reset()
{
	health = maxHealth;
	mana = maxMana;
	stamina = maxStamina;
}
void HealthComponent::render() {}
void HealthComponent::update(double dt)
{
	////automatic recovery of health and mana over time 
	recoveryTimer -= dt;
	if (recoveryTimer <= 0)
	{
		if (health <= maxHealth-3)
			health += 3;
		if (mana <= maxMana-6)
			mana += 6;
		if (stamina <= maxStamina - 15)
			stamina += 15;
		recoveryTimer = recoveryDelay;
	}

	if (burnTimer <= 0) {
		burnTimer = 5.0f; //need to search for dot implementation
	}

	auto statuscmp = _parent->GetComponent<StatusComponent>();
	if (statuscmp->getBurning() && burnTimer >= 0) { //if status is burning, and timer is good
		burnTimer -= dt; //lower burn timer
		dotTick -= dt; //lower dot tick
		if (dotTick <= 0.0f) { //if it ticks
			reduceHealth(maxHealth * 0.01f);
			dotTick = 1.0f;
		}
	}

}
void HealthComponent::reduceHealth(float x)
{
	health -= x;
}
void HealthComponent::reduceMana(float x)
{
	mana -= x;
}
void HealthComponent::reduceStamina(float x)
{
	stamina -= x;
}