#pragma once
#include "ecm.h"
#include <string>

class NPCComponent : public Component {
protected:
	bool has_switch = false;
	int switch_id = 0;
	sf::RectangleShape dialogueBox;
	std::string dialogue;
	std::string dialogue2;
	sf::Text text;
	float letter_delay = 30.0f;
	bool trigger = false;
	float interactionDelay = 0.4f;
	bool dialogueStarted = false;
	bool dialogueFinished = false;
	bool bodylessText = false;
	bool disappearAfter = false;
public:
	NPCComponent() = delete;
	void setBodyless() { bodylessText = true; }
	void setDisappear() { disappearAfter = true; }
	explicit NPCComponent(Entity *p);
	void update(double dt) override;
	void setDialogue(std::string x);
	void render() override;
	void addSwitch(int id) { has_switch = true; switch_id = id; };
	
};