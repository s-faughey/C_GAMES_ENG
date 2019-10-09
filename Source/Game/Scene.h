#pragma once
#include "ecm.h"
#include <SFML/Graphics.hpp>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;
	virtual void update(double dt);
	virtual void render();
	virtual void load() = 0;
	void setID(int x) { scene_number = x; }
	int getID() { return scene_number; }
	std::vector<std::shared_ptr<Entity>> &getEnts() { return _ents.list; };
protected:
	int scene_number;

	EntityManager _ents;
};
