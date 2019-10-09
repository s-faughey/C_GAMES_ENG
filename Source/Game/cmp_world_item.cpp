#include "cmp_world_item.h"
#include "SystemRenderer.h"
#include "Game.h"
#include "cmp_actor_movement.h"
#include "EventSystem.h"

static float interactionDelay = 0;
WorldItemComponent::WorldItemComponent(Entity *p) : Component(p)
{
	dialogueBox.setFillColor(sf::Color(255,255,255,200));
	dialogueBox.setSize(sf::Vector2f(0.98f*WX, 0.25f*WY));
	dialogueBox.setPosition(sf::Vector2f(0.025f* WX, 0.75f*WY));
	text.setColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(27.0f * WX/1280);
}
void WorldItemComponent::setDialogue(std::string x)
{
	dialogue = x;
}
void WorldItemComponent::update(double dt)
{
	interactionDelay -= dt;
	if (mapChanger)
	{
		if (interactionDelay <= 0 && (length(_parent->getPosition() - player->getPosition()) < 15.0f*WX / 1280))
		{
		EventSystem* evs = EventSystem::getInstance();
		evs->changeMap(destination);
		if (map_id == 0)
			evs->map_interior0();
		else if (map_id == 1)
			evs->map_village0();
		else if (map_id == 2)
			evs->map_forest0();
		}
	}
	else if (teleporter)
	{
		if (interactionDelay <= 0 && (length(_parent->getPosition() - player->getPosition()) < 15.0f*WX / 1280))
		{
			player->setPosition(destination);
		}
	}
	else if (world_text)
	{
		if (interactionDelay <= 0 && (length(_parent->getPosition() - player->getPosition()) < 21.0f*WX / 1280) && sf::Keyboard::isKeyPressed(controls[12]))
		{
			if (interactionDelay <= 0 && (length(_parent->getPosition() - player->getPosition()) < 21.0f*WX / 1280) && sf::Keyboard::isKeyPressed(controls[12]))
			{
				player->GetComponent<PlayerMovementComponent>()->immobilize();
				interact();
			}
		}
		dialogueBox.setPosition(player->getPosition() + sf::Vector2f(-0.49f* WX, 0.14f*WY));
		text.setPosition(player->getPosition() + sf::Vector2f(-0.48f* WX, 0.15f*WY));
		if (trigger && timer.getElapsedTime().asMilliseconds() > 40.0f && i < dialogue.length())
		{
			timer.restart();
			i++;
			text.setString(sf::String(dialogue.substr(0, i)));
		}

		if (i >= dialogue.size())
		{
			dialogueFinished = true;
		}
		if (dialogueFinished && sf::Keyboard::isKeyPressed(controls[12]))
		{
			i = 0;
			trigger = false;
			dialogueFinished = false;
			interactionDelay = 0.4f;
			player->GetComponent<PlayerMovementComponent>()->mobilize();
		}
	}
	
}
void WorldItemComponent::render()
{
	if (trigger)
	{
		Renderer::queue(0,&dialogueBox);
		Renderer::queue(0,&text);
	}
}
void WorldItemComponent::interact()
{
	trigger = true;
}