#pragma once
#include "ecm.h"

class HealthComponent : public Component {

protected:
	float maxStamina;
	float stamina;
	float maxHealth;
	float health;
	float maxMana;
	float mana;
	float recoveryDelay = 3.0f;
	float recoveryTimer = 3.0f;
	float burnTimer = 5.0f;
	float dotTick = 1.0f;
public:
	explicit HealthComponent(Entity *p);
	HealthComponent() = delete;
	float getHealth() { return health; }
	float getMaxHealth() { return maxHealth; }
	float getMaxMana() { return maxMana; }
	float getMana() { return mana; }
	float getMaxStamina() { return maxStamina; }
	float getStamina() { return stamina; }
	void setMaxHealth(float x) { maxHealth = x; health = maxHealth; }
	void reduceHealth(float x);
	void reset();
	void reduceMana(float x);
	void reduceStamina(float x);
	void render() override;
	void update(double dt) override;	

	
};

