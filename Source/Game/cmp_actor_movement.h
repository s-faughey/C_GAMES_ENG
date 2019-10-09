#pragma once
#include "ecm.h"

class ActorMovementComponent : public Component {
protected:
	bool validMove(const sf::Vector2f&);
	float _speed;
	bool immobilized=false;
	bool pushed = false;
	float pushTimer = 0.1f;
	sf::Vector2f pushVector;
public:
	explicit ActorMovementComponent(Entity *p);
	ActorMovementComponent() = delete;
	float getSpeed() const;
	void setSpeed(float speed);
	void immobilize() { immobilized = true; }
	bool canMove() { return !immobilized; }
	void mobilize() { immobilized = false; }
	void move(const sf::Vector2f&);
	void push(const sf::Vector2f&);
	void move(float x, float y);
	void increaseSpeed(float sp);

	void render() override;
	void update(double dt) override;
};
class ProjectileMovementComponent : public ActorMovementComponent {

protected:
	sf::Vector2f _direction;
public:
	ProjectileMovementComponent() = delete;
	explicit ProjectileMovementComponent(Entity *p);
	void move(const sf::Vector2f&);
	void update(double dt) override;
	void render() override;
};
class SnowComponent : public ActorMovementComponent {

protected:
	float dirTimer = 1.0f;
	bool dir;
public:
	SnowComponent() = delete;
	explicit SnowComponent(Entity *p);
	void move(const sf::Vector2f&);
	void update(double dt) override;
	void render() override;
};

class CursorMovementComponent : public ActorMovementComponent {

protected:
	float dirTimer = 1.0f;
	bool dir;
public:
	CursorMovementComponent() = delete;
	explicit CursorMovementComponent(Entity *p);
	void move(const sf::Vector2f&);
	bool validMove(const sf::Vector2f & p);
	void update(double dt) override;
	void render() override;
	void reset();
};

class OptionsMovementComponent : public ActorMovementComponent {

protected:
	float dirTimer = 1.0f;
	bool dir;
public:
	OptionsMovementComponent() = delete;
	explicit OptionsMovementComponent(Entity *p);
	void move(const sf::Vector2f&);
	bool validMove(const sf::Vector2f & p);
	void update(double dt) override;
	void render() override;
	void reset();
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity *p);

	void update(double dt) override;
	void render() override;

};
class SwordMovementComponent : public ActorMovementComponent {
public:
	SwordMovementComponent() = delete;
	explicit SwordMovementComponent(Entity *p);

	void update(double dt) override;
	void render() override;

};

class EnemyAIComponent : public ActorMovementComponent {
protected:
	sf::Vector2f _direction;
	enum STATE { DEADEND, ROAMING, ROTATING, ROTATED };
	STATE _state;

public:
	
	EnemyAIComponent() = delete;
	explicit EnemyAIComponent(Entity *p);

	void update(double dt) override;
	void render() override;
};