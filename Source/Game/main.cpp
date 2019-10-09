#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "levelsystem.h"
#include "SystemRenderer.h"
#include "ecm.h"
#include <memory>

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> optionsScene;
std::shared_ptr<Scene> activeScene;
void Load()
{
	menuScene.reset(new MenuScene());
	menuScene->load();
	optionsScene.reset(new OptionsScene());
	optionsScene->load();
	activeScene = menuScene;
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);

	Event event;
	while (window.pollEvent(event))
	{
		
		if (event.type == Event::Resized) {
			Renderer::resizeView();
			return;
		}
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}	
}

void Render(RenderWindow &window)
{
	activeScene->render();
	//flush to screen
	Renderer::render();
}

int main()
{
	sf::Clock clock;
	float lastTime = 0;
	RenderWindow window(VideoMode(Renderer::gameWidth[resolution_index], Renderer::gameHeight[resolution_index]), "Icy Dead People");
	Renderer::initialise(window);
	Load();
	while (window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;
		window.setTitle("Icy Dead People v1.0  FPS:" + std::to_string((int)fps));
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}