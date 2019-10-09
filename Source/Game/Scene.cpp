#include "scene.h"
#include "SystemRenderer.h"


void Scene::update(double dt)
{
}
void Scene::render()
{
	for (auto &e : _ents.list) {
		e->render();
	}
}

