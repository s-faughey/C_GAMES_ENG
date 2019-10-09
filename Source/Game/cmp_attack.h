#pragma once
#include "ecm.h"
#include "cmp_sprite.h"

class AttackComponent : public Component {

protected:
	bool componentsReady = false;
	std::vector <std::shared_ptr<Entity>> _entities;
public:
	explicit AttackComponent(Entity *p);
	AttackComponent() = delete;
	void render() override;
	void update(double dt) override;
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

