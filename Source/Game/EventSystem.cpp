
#include "EventSystem.h"
#include "cmp_char_sheet.h"
#include "Game.h"
#include "ItemGenerator.h"
#include <iostream>
#include <fstream>
#include "cmp_actor_movement.h"
#include "cmp_health.h"
#include "cmp_hud.h"
#include <sstream>

EventSystem* EventSystem::instance;
ItemGenerator* itemGenerator = ItemGenerator::getInstance();
EventSystem::EventSystem()
{
	
}
EventSystem* EventSystem::getInstance()
{
	if (instance == 0)
	{
		instance = new EventSystem();
	}

	return instance;
}
EventSystem::~EventSystem()
{
}

void EventSystem::LoadGame()
{
	gameScene.reset(new GameScene());
	gameScene->load();
	std::vector<int> location;
	std::vector<int> levels;
	std::vector<int> experience;
	std::vector<int> items;
	std::vector<int> keys;
	std::vector<int> spells;
	std::vector<bool> switches;
	int map;
	auto character = player->GetComponent<CharacterSheetComponent>();
	std::ifstream save("save.txt");
	if (save.good())
	{
		std::string line;
		int line_number = 0;
		while (std::getline(save, line))
		{
			std::stringstream ss(line);
			int i;
			while (ss >> i)
			{
				if (line_number == 0)
					location.push_back(i);
				else if (line_number == 1)
					levels.push_back(i);
				else if (line_number == 2)
					experience.push_back(i);
				else if (line_number == 3)
					items.push_back(i);
				else if (line_number == 4)
					keys.push_back(i);
				else if (line_number == 5)
					spells.push_back(i);
				else if (line_number == 6)
					map = i;
				else if (line_number == 7)
					switches.push_back((bool)i);

				if (ss.peek() == ',')
					ss.ignore();
			}
			line_number++;
		}
		switch (map)
		{
		case 0:
			interior0 = true;
			mapChange = true;
			break;
		case 1:
			village0 = true;
			mapChange = true;
		case 2:
			forest0 = true;
			mapChange = true;
		default:
			break;
		}
		new_destination = { (float)location[1],(float)location[2] };
		////////// set switches//////////////////
		tutorial_text0 = switches[0];
		forrest0_dialogue_finished = switches[1];
		activeScene = gameScene;
		player->setPosition({ (float)location[1],(float)location[2] });
		character->setLevels(levels[0], levels[1], levels[2], levels[3], levels[4]);
		character->setExperience(experience[0], experience[1], experience[2], experience[3], experience[4]);
		character->setSpell(0, spells[0]);
		character->setSpell(1, spells[1]);
		character->setSpell(2, spells[2]);
		character->setSpell(3, spells[3]);
		character->setSpell(4, spells[4]);
		for (int i = 0; i < items.size(); i += 2)
		{
			itemGenerator->load(items[i], (bool)items[i + 1]);
		}
		for (int i = 0; i<10000; i++)
		{
			
			auto cherry = std::make_shared<Entity>();
			cherry->setForDelete();
			gameScene->getEnts().push_back(cherry);
		}
		auto x = player->GetComponent<HudComponent>();
		x->reload();
		for (int i = 0; i < 12; i++)
			controls[i] = (sf::Keyboard::Key)keys[i];
		
		refreshKeyLabels = true;
		LVUP = true;
	}
	
}
int EventSystem::getCurrentMap()
{
	if (interior0)
		return 0;
	else if (village0)
		return 1;
	else if (forest0)
		return 2;
	else
		return 0;
}
std::string EventSystem::getSwitches()
{
	return std::to_string((int)tutorial_text0) + "," +std::to_string((int)forrest0_dialogue_finished);
}
void EventSystem::SaveGame()
{
	auto character = player->GetComponent<CharacterSheetComponent>();
	std::ofstream save("save.txt");
	if (save.is_open())
	{
		save << character->saveLocation() + "\n";
		save << character->saveLevels() + "\n";
		save << character->saveExperience() + "\n";
		save << character->saveItems() + "\n";
		save << character->saveControls() + "\n";
		save << character->saveSpells() + "\n";
		save << std::to_string(getCurrentMap()) + "\n";
		save << getSwitches() + "\n";
		save.close();
	}
	else std::cout << "Unable to open file";
}
void EventSystem::addExp(int a, float b)
{
	auto exp = player->GetComponent<CharacterSheetComponent>();
	exp->addEXP(a, b);
}