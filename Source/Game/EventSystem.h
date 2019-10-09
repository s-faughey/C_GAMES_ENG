#include "Game.h"
#include "levelsystem.h"

class EventSystem
{

private:

	//////////if newgame ///////////// for loading correct map
	bool newGame = false;
	bool mapChange = false;
	////////////////////////////CURRENT MAP SWITCHES//////////////////
	bool village0 = false;
	bool interior0 = false;
	bool forest0 = false;
	float forestMultiplier = 3.33f;
	sf::Vector2f new_destination;
	////////////////////switches

	bool LVUP = true;
	bool refreshKeyLabels = false;
	bool gameLoaded = false;
	/////////////////////////////////GAMEPLAY SWITCHES
	bool tutorial_text0 = true;
	bool forrest0_dialogue_finished = false;

	EventSystem();
	static EventSystem* instance;
	int resolution_index=0;
public:
	void reset_switches() { tutorial_text0 = true; forrest0_dialogue_finished = false; };
	bool is_forrest_dialogue_finished() { return forrest0_dialogue_finished; }
	void switch_forrest_dialogue() { forrest0_dialogue_finished = true; }
	float getFM() { return forestMultiplier; }
	bool is_tutorial() { return tutorial_text0; }
	void switch_tutorial_complete() { tutorial_text0 = false; }
	bool is_newGame() { return newGame;  }
	void switch_new_game_dialogue() { newGame = false; }
	void setNewGame() { newGame = true; new_destination = { 150,170 }; reset_switches();}
	int getCurrentMap();
	std::string getSwitches();
	bool if_changeMap() { return mapChange; }
	void changeMap(sf::Vector2f d) { mapChange = true; new_destination = d; }
	sf::Vector2f getDest() { return new_destination; }
	void changeMapFinished() { mapChange = false; }
	//////////////////////map changers
	void map_village0() { village0 = true; interior0 = false; forest0 = false; }
	void map_interior0() { village0 = false; interior0 = true; }
	void map_forest0() { village0 = false; forest0 = true; }

	//////////////////////////map checkers
	bool if_village0() { return village0; }
	bool if_interior0() { return interior0; }
	bool if_forest0() { return forest0; }


	void switch_level_up() { LVUP = (LVUP) ? false : true; }
	bool is_leveled_up() { return LVUP; }

	void refresh() { refreshKeyLabels = true; }
	bool is_for_refresh() {  return refreshKeyLabels; }
	void refreshed() { refreshKeyLabels = false; }
	int getRes() { return resolution_index; }
	static EventSystem* getInstance();
	bool isLoaded() { return gameLoaded; }
	void gameLoad() { gameLoaded = true; }
	void SaveGame();
	void LoadGame();
	~EventSystem();
	void addExp(int stat, float exp);
};