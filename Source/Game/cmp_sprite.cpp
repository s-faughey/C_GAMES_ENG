#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>
#include "cmp_actor_movement.h"
#include "cmp_status.h"
#include "Game.h"
#include "cmp_health.h"
#include "cmp_ai_steering.h"
using namespace sf;
ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

void ShapeComponent::update(double dt) 
{
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

CharacterSpriteComponent::CharacterSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{
	frame = 0;
	
}
void CharacterSpriteComponent::setDefaultFrames()
{
	walkingAnimationDown.push_back(sf::IntRect(0, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(16, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(32, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(48, 0, 16, 21));

	walkingAnimationUp.push_back(sf::IntRect(0, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(16, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(32, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(48, 42, 16, 21));

	walkingAnimationRight.push_back(sf::IntRect(0, 21, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(16, 21, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(32, 21, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(48, 21, 16, 21));

	walkingAnimationLeft.push_back(sf::IntRect(0, 64, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(16, 64, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(32, 64, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(48, 64, 16, 21));
}
void CharacterSpriteComponent::update(double dt)
{
	
	AnimationCounter -= dt;
	if (!_parent->isPlayer())
	{
	
		bool mov = _parent->isMoving();
		
		if (frame > 3) frame = 0;

		if (_parent->getFace() == 1 && AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		else if (_parent->getFace() == 2 && AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		else if (_parent->getFace() == 3 && AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		else if (_parent->getFace() == 4 && AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		
		if (!mov)
		{
			frame = 0;
		}
			

	}
	else
	{
		if (Keyboard::isKeyPressed(controls[0]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == 100))
		{
			facing = 1;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[1]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == -100))
		{
			facing = 3;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[3]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == -100))
		{
			facing = 4;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[2]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == 100))
		{
			facing = 2;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}

		else
		{
			frame = 0;
			switch (facing)
			{
			case 1:
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				break;
			case 2:
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				break;
			case 3:
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				break;
			case 4:
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				break;
			}
		}
	}
	
	_sprite->setPosition(_parent->getPosition());
}
void CharacterSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void CharacterSpriteComponent::render() {
	if(_parent->isPlayer())
	Renderer::queue(1,_sprite.get());
	else
	{
		if(_parent->getPosition().y>=player->getPosition().y)
			Renderer::queue(1, _sprite.get());
		else
			Renderer::queue(2, _sprite.get());
	}
}
sf::Sprite& CharacterSpriteComponent::getSprite() const {
	return *_sprite;
}

DamageTextComponent::DamageTextComponent(Entity *p) : Component(p) 
{
	damageText.setFont(font);
	damageText.setCharacterSize(12);
	damageText.setScale(WX/1280,WY/720);
	damageText.setColor(sf::Color::Red);
	

}
void DamageTextComponent::setText(int x)
{
	damageText.setString(std::to_string(x));
}
void DamageTextComponent::update(double dt)
{
	textTime -= dt;
	damageText.setPosition(_parent->getPosition()+Vector2f(-14.0f*WX/1280,-15.0f*WY/720));
	if (textTime < 0)
		_parent->setForDelete();
	
}
void DamageTextComponent::render()
{
	Renderer::queue(1,&damageText);
}



	
sf::Sprite& StaticSpriteComponent::getSprite() const {
	return *_sprite;
}

StaticSpriteComponent::StaticSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{
	
}

void StaticSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void StaticSpriteComponent::update(double dt)
{
	if(spin)
	_sprite->rotate(-360.0f*dt*5.0f);
	_sprite->setPosition(_parent->getPosition());
}

void StaticSpriteComponent::render()
{
	Renderer::queue(2,_sprite.get());
}

CursorSpriteComponent::CursorSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{

}

void CursorSpriteComponent::setScale()
{
	_sprite->setScale(2, 2);
}
void CursorSpriteComponent::update(double dt)
{
	_sprite->setPosition(_parent->getPosition());
}

void CursorSpriteComponent::render()
{
	Renderer::queue(-1, _sprite.get());
}

sf::Sprite & CursorSpriteComponent::getSprite() const
{
	return *_sprite;
}

EnemyHealthBarComponent::EnemyHealthBarComponent(Entity *p) : Component(p) 
{
	status.setTexture(spellsTexture);
	status.setTextureRect({95,30,30,30});
	status.setScale(WX / 1280, WY / 720);
	text_hp.setFont(font);
	text_hp.setCharacterSize(12);
	text_hp.setScale(WX / 1280, WY / 720);
	text_hp.setColor(sf::Color::Red);
	hp.setFillColor(sf::Color::Red);
	hp.setSize({31.0f, 4.0f});
	auto health = _parent->GetComponent<HealthComponent>();
	text_hp.setString(std::to_string((int)health->getHealth()) + "/" + std::to_string((int)health->getMaxHealth()));
}
void EnemyHealthBarComponent::update(double dt)
{
	if (back_to_normal)
	{
		status.setTextureRect({ 95,30,30,30 });
		back_to_normal = false;
	}
	else if (slow)
	{
		status.setTextureRect({ 30,30,30,30 });
		slow = false;
	}
	else if (blind)
	{
		status.setTextureRect({ 60,30,30,30 });
		blind = false;
	}
	else if (burn)
	{
		status.setTextureRect({ 0,30,30,30 });
		burn = false;
	}

	auto health = _parent->GetComponent<HealthComponent>();
	float scaleX = health->getHealth() / health->getMaxHealth();
	hp.setScale(scaleX * (WX / 1280) , WY / 720);
	status.setPosition(_parent->getPosition() + Vector2f(15.0*WX / 1280, -35.0f*WY / 720));
	hp.setPosition(_parent->getPosition() + Vector2f(-15.0*WX/1280, -30.0f*WY/720));
	text_hp.setPosition(_parent->getPosition() + Vector2f(-33.0*WX / 1280, -50.0f*WY / 720));
	text_hp.setString(std::to_string((int)health->getHealth()) + "/" + std::to_string((int)health->getMaxHealth()));
}
void EnemyHealthBarComponent::render()
{
	Renderer::queue(1,&status);
	Renderer::queue(1,&hp);
	Renderer::queue(1,&text_hp);
}
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{

}

void AnimatedSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void AnimatedSpriteComponent::update(double dt)
{
	AnimationCounter -= dt;

	if (frame >= max_frames)
	{
		animationDirection = false;
		if (singularPlay)
			_parent->setForDelete();
	}
	else if (frame <= 0)
		animationDirection = true;
	if(!_parent->is_forDeletion())
	if ( AnimationCounter <= 0.0f)
	{
		if (animationDirection)
			frame++;
		else
			frame--;
		_sprite->setTextureRect(animationFrames[frame]);		
		AnimationCounter = AnimationDelay;
	}
	_sprite->setPosition(_parent->getPosition());

	
}
sf::Sprite& AnimatedSpriteComponent::getSprite() const {
	return *_sprite;
}

void AnimatedSpriteComponent::render()
{
	Renderer::queue(priority, _sprite.get());
}