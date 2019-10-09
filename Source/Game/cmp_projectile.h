#pragma once
#include "ecm.h"

class ProjectileComponent : public Component {

protected:
	bool conDmg = false;
	bool indestructable = false;
	bool damage_dealt = false;
	std::vector <std::shared_ptr<Entity>> _entities;
	float textTime = 0.0f;
	float damage = 30;
	float range = 30;
	int type = 1;
	bool knockback = false;
	bool blind = false;
	bool burn = false;
	bool slow = false;
	bool finishAnimation = false;
	float timer = 0.1f;
public:
	void setRange(float t) { range = t; }
	void addContinuousDmg() { conDmg = true; }
	void setIndestructable() { indestructable = true; }
	void setTimer(float t) { timer = t; }
	void finishAnimationFirst() { finishAnimation = true; }
	void addKnockback() { knockback = true; }
	void addBlind() { blind = true; }
	void addBurn() { burn = true; }
	void addSlow() { slow = true; }
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	explicit ProjectileComponent(Entity *p);
	ProjectileComponent() = delete;
	void setDamage(int x) { damage = x; }
	void setType(int x) { type = x; } ////////////////FIRE-1 WATER-2 ........
	void render() override;
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
};