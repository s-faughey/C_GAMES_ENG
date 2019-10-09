#include "cmp_pickups.h"
#include "SystemRenderer.h"
#include "maths.h"
#include "cmp_actor_movement.h"

PickupComponent::PickupComponent(Entity *p) : _points(20), Component(p) {}

void PickupComponent::update(double dt) {
	for (auto e : _entities) 
	{
		if (length(_parent->getPosition() - e->getPosition()) < 21.0f) 
		{			
			_parent->setForDelete();
			auto cp = e->GetComponent<ActorMovementComponent>();
			if (cp != nullptr) {
			//	cp->increaseSpeed(2.5f);
			}

			break;
		}
	}
}
void PickupComponent::render() {}
void PickupComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}

int PickupComponent::getPoints() const {
	return _points;
}

void PickupComponent::setPoints(int pts) {
	_points = pts;
}