
#include "SpellCaster.h"
#include "cmp_char_sheet.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"

SpellCaster* SpellCaster::instance;
SpellCaster::SpellCaster()
{
	cooldowns.push_back(0.5f);//////////fireball cooldown
	cooldowns.push_back(0.5f);//////////water gun cooldown
	cooldowns.push_back(0.5f);//////////sonic boom cooldown
	cooldowns.push_back(0.5f);//////////earth spike cooldown
	cooldowns.push_back(0.25f);////////////////////////////////SWORD ATTACK cooldown
	cooldowns.push_back(0.05f);//////////deagon breath cooldonw
	cooldowns.push_back(0.15f);///////////ice barrage
	cooldowns.push_back(1.0f);///////////wind scythe
	cooldowns.push_back(1.0f);///////////rolling boulder
	cooldowns.push_back(2.0f);//////////explosion
}
SpellCaster* SpellCaster::getInstance()
{
	if (instance == 0)
	{
		instance = new SpellCaster();
	}

	return instance;
}
void SpellCaster::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void SpellCaster::cast_spell_id(int id, sf::Vector2f location)
{
	switch (id)
	{
	case 0:
		cast_fire_ball(location);
		break;
	case 1:
		cast_water_gun(location);
		break;
	case 2:
		cast_sonic_boom(location);
		break;
	case 3:
		cast_earth_spike(location);
		break;
	case 4:
		cast_sword_swing(location);		
		break;
	case 5:
		cast_dragon_breath(location);		
		break;
	case 6:
		cast_ice_barrage(location);
		break;
	case 7:
		cast_wind_scythe(location);
		break;
	case 8:
		cast_rolling_boulder(location);
		break;
	case 9:
		cast_explosion(location);
		break;
	default:
		break;
	}
}
void SpellCaster::cast_fire_ball(sf::Vector2f location)
{////////////////////spell ID: 0//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=10)
	{
		sound_spells.setBuffer(buffer_fire);
		sound_spells.play();
		health_mana->reduceMana(10);

		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->addBurn();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelFire()*8.0f) + 20.0f);
		c2->setType(1);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->setScale();
		s->getSprite().setTextureRect({ 0,0,30,30 });
		s->getSprite().setOrigin({ 17.0f, 19.0f });

		gameScene->getEnts().push_back(bullet);
	}
}

void SpellCaster::cast_water_gun(sf::Vector2f location)
{////////////////////spell ID: 1//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=10)
	{
		sound_spells.setBuffer(buffer_water);
		sound_spells.play();
		health_mana->reduceMana(10);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelWater()*8.0f) + 20.0f);
		c2->setType(2);
		c2->addSlow();
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->setScale();
		s->getSprite().setTextureRect({ 30,0,30,30 });
		s->getSprite().setOrigin({ 15.0f, 15.0f });

		gameScene->getEnts().push_back(bullet);
	}
}
void SpellCaster::cast_sonic_boom(sf::Vector2f location)
{////////////////////spell ID: 2//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=10)
	{
		sound_spells.setBuffer(buffer_water);
		sound_spells.play();
		health_mana->reduceMana(10);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->addKnockback();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelWind()*7.0f) + 15.0f);
		c2->setType(3);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->setScale();
		s->getSprite().setTextureRect({ 60,0,30,30 });
		s->getSprite().setOrigin({ 15.0f, 15.0f });

		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_earth_spike(sf::Vector2f location)
{////////////////////spell ID: 3//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=10)
	{
		sound_spells.setBuffer(buffer_earth);
		sound_spells.play();
		health_mana->reduceMana(10);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->addBlind();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelEarth()*8.0f) + 20.0f);
		c2->setType(4);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(animatedSpellsTexture);
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->getSprite().setTextureRect({ 0,0,30,30 });
		s->setDelay(0.1f);
		s->getSprite().setScale(2.0f*WX / 1280, 2.0f*WY / 720);
		s->addFrame(sf::IntRect(0, 0, 30, 30));
		s->addFrame(sf::IntRect(0, 0, 30, 30));
		s->addFrame(sf::IntRect(30, 0, 30, 30));
		s->addFrame(sf::IntRect(60, 0, 30, 30));
		s->addFrame(sf::IntRect(90, 0, 30, 30));
		s->addFrame(sf::IntRect(120, 0, 30, 30));

		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_sword_swing(sf::Vector2f location)
{////////////////////spell ID: 4//////////////////////////////////////

	
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getStamina() >= 4)
	{
		sound_spells.setBuffer(buffer_swing);
		sound_spells.play();
		health_mana->reduceStamina(4);
		auto bullet = std::make_shared<Entity>();
		auto pr = bullet->addComponent<SwordMovementComponent>();
		bullet->setFace(player->getFace());
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->finishAnimationFirst();
		c2->setEntities(_entities);
		c2->addKnockback();
		c2->setDamage(dmg->getStatAttack());
		c2->setType(0);
		c2->setTimer(0.35f);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(swordSwingTexture);
		s->getSprite().setOrigin({ 45, 40 });
		
		s->setDelay(0.05f);
		s->setScale();
		s->playOnce();
		s->addFrame(sf::IntRect(0, 0, 100, 70));
		s->addFrame(sf::IntRect(100, 0, 100, 70));
		s->addFrame(sf::IntRect(200, 0, 100, 70));
		s->addFrame(sf::IntRect(300, 0, 100, 70));
		s->addFrame(sf::IntRect(400, 0, 100, 70));
		s->addFrame(sf::IntRect(500, 0, 100, 70));
		s->addFrame(sf::IntRect(600, 0, 100, 70));
		s->getSprite().setTextureRect({ 0, 0, 100, 70 });
		if (player->getFace() == 1)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(0, -15.0 *WY / 720));
			s->getSprite().rotate(-90);
		}
		else if (player->getFace() == 2)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(15 * WX / 1280, 0));
		}
		else if (player->getFace() == 3)
		{
			s->setPriority(1);
			bullet->setPosition(player->getPosition() + sf::Vector2f(0, 15.0 *WY / 720));
			s->getSprite().rotate(90);

		}
		else if (player->getFace() == 4)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(-15 * WX / 1280, 0));
			s->getSprite().rotate(180);
		}
		gameScene->getEnts().push_back(bullet);

	}
}
void SpellCaster::cast_dragon_breath(sf::Vector2f location)
{////////////////////spell ID: 5//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana() >= 2)
	{
		health_mana->reduceMana(2);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition() +sf::Vector2f(-3 + rand() % 7, -3+ rand() % 7));
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		c2->addBurn();
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage(dmg->getLevelFire());
		c2->setType(1);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(animatedSpellsTexture);
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->getSprite().setTextureRect({ 0,30,30,30 });
		s->playOnce();
		s->setDelay(0.05f*dmg->getLevelFire());
		s->addFrame(sf::IntRect(0, 30, 30, 30));
		s->addFrame(sf::IntRect(30, 30, 30, 30));
		s->addFrame(sf::IntRect(60, 30, 30, 30));
		s->addFrame(sf::IntRect(90, 30, 30, 30));
		s->addFrame(sf::IntRect(120, 30, 30, 30));
		s->setScale();


		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_ice_barrage(sf::Vector2f location)
{////////////////////spell ID: 6//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana() >= 2)
	{
		health_mana->reduceMana(2);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition() + sf::Vector2f(-7+ rand()%15,-7+rand()%15 ));
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage(dmg->getLevelWater());
		c2->setType(2);
		c2->addSlow();
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->getSprite().setTextureRect({ 90,0,30,30 });
		if (player->getFace() == 1)
		{
			
			s->getSprite().rotate(-90);
		}
		else if (player->getFace() == 3)
		{
			
			s->getSprite().rotate(90);
		}
		s->setScale();


		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_wind_scythe(sf::Vector2f location)
{////////////////////spell ID: 7//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana() >= 20)
	{
		health_mana->reduceMana(20);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		c2->addKnockback();
		c2->setIndestructable();
		c2->addContinuousDmg();
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage(dmg->getLevelWind() *2.0f + 30);
		c2->setType(3);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->getSprite().setTextureRect({ 60,0,30,30 });
		if (player->getFace() == 1)
		{
			s->getSprite().rotate(-90);
		}
		else if (player->getFace() == 2)
		{
			
		}
		else if (player->getFace() == 3)
		{

			s->getSprite().rotate(90);
		}
		else if (player->getFace() == 4)
		{
			s->getSprite().rotate(180);
		}
		s->getSprite().setScale(2.0f*WX / 1280, 2.0f*WY / 720);


		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_rolling_boulder(sf::Vector2f location)
{////////////////////spell ID: 7//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana() >= 20)
	{
		health_mana->reduceMana(20);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		c2->addKnockback();
		c2->addBlind();
		c2->setIndestructable();
		c2->addContinuousDmg();
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage(dmg->getLevelEarth() *2.0f + 30);
		c2->setType(4);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->addSpin();
		s->getSprite().setTextureRect({ 120,0,30,30 });
		s->getSprite().setScale(2.0f*WX / 1280, 2.0f*WY / 720);
		gameScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_explosion(sf::Vector2f location)
{////////////////////spell ID: 8//////////////////////////////////////

	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana() >= 35)
	{
		health_mana->reduceMana(35);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->finishAnimationFirst();
		c2->setEntities(_entities);
		c2->addKnockback();
		c2->addBurn();
		c2->setRange(90.0f);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelFire()+5)*10.0f);
		c2->setType(1);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(animatedSpellsTexture);
		s->getSprite().setOrigin({ 45, 45 });
		c2->setTimer(0.54f);
		s->setDelay(0.07f);
		s->getSprite().setScale(2.0f*WX / 1280, 2.0f*WY / 720);
		s->playOnce();
		s->addFrame(sf::IntRect(0, 60, 90, 90));
		s->addFrame(sf::IntRect(90, 60, 90, 90));
		s->addFrame(sf::IntRect(180, 60, 90, 90));
		s->addFrame(sf::IntRect(270, 60, 90, 90));
		s->addFrame(sf::IntRect(360, 60, 90, 90));
		s->addFrame(sf::IntRect(450, 60, 90, 90));
		s->addFrame(sf::IntRect(540, 60, 90, 90));
		s->addFrame(sf::IntRect(630, 60, 90, 90));
		s->addFrame(sf::IntRect(720, 60, 90, 90));
		s->getSprite().setTextureRect({ 0, 60, 90, 90 });
		gameScene->getEnts().push_back(bullet);

	}
}