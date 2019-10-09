#pragma once
#include "ecm.h"
class PickupComponent : public Component {
protected:
	std::vector <std::shared_ptr<Entity>> _entities;
	int _points;
public:
	PickupComponent() = delete;
	explicit PickupComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
	int getPoints() const;
	void setPoints(int pts);

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};