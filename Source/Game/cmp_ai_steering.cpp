#include "cmp_ai_steering.h"
#include "cmp_status.h"
#include "SystemRenderer.h"
#include <maths.h>
#include "Game.h"
#include "levelsystem.h"
using namespace sf;
#define WX  1.0f*Renderer::gameWidth[resolution_index]

SteeringComponent::SteeringComponent(Entity * p, Entity* player)
	: _player(player), _seek(Seek(p, player, 100.f)),
	_flee(Flee(p, player, 100.0f)), Component(p) {
	_speed = 80.0f+rand()%20;
}

void SteeringComponent::update(double dt)
{
	auto slowed = _parent->GetComponent<StatusComponent>();
	if (slowed->getSlowed()) {
		std::cout << "asdf";
		_speed = 40.0f;
	}
	else {
		_speed = 80.0f;
	}
	const auto mva = (float)(dt * _speed);
	// If target (player) is within 300 pixels seek
	if (length(_parent->getPosition() - _player->getPosition()) < 0.49f*WX && length(_parent->getPosition() - _player->getPosition()) > 20.0f*WX / 1280)
	{
		double pi = 3.14159265359;
		auto output = _seek.getSteering();
		move(output.direction * mva);

		Vector2f j(_parent->getPosition());
		Vector2f k(_player->getPosition());

		float angle = atan2f(k.y-j.y, k.x-j.x) * 180 / pi;


		if (angle >= 45 && angle < 135) {
			_parent->setFace(3);
		}
		if (angle >= 135 && angle <= 180 || angle >= -180 && angle < -135) {
			_parent->setFace(4);
		}
		if (angle >= -135 && angle < -45) {
			_parent->setFace(1);
		}
		if (angle >= -45 && angle < 45) {
			_parent->setFace(2);
		}
	} else
		_parent->setMoving(false);
	
}

bool SteeringComponent::validMove(const sf::Vector2f& pos) const
{
	////////////////////////////////////////INSTERT ALLL WALLS
	return (LevelSystem::isWalkable(LevelSystem::getTileAt(pos)) && LevelSystem::isWalkable(LevelSystem::getTileAt2(pos)));
}

void SteeringComponent::move(const Vector2f& p)
{
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos))
	{
		_parent->setMoving(true);
		_parent->setPosition(new_pos);
	}
	else if (validMove(Vector2f(new_pos.x, _parent->getPosition().y)))
	{
		_parent->setMoving(true);
		_parent->setPosition(Vector2f(new_pos.x, _parent->getPosition().y));
	}
	else if (validMove(Vector2f(_parent->getPosition().x, new_pos.y)))
	{
		_parent->setMoving(true);
		_parent->setPosition(Vector2f(_parent->getPosition().x, new_pos.y));
	}
	else if (validMove(-new_pos))
	{
		_parent->setMoving(true);
		_parent->setPosition(-new_pos);

	}
	else
		_parent->setMoving(false);
	
	
}

void SteeringComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}