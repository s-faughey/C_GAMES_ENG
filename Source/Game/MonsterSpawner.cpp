
#include "MonsterSpawner.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_enemy_attack.h"
#include "cmp_ai_steering.h"
#include "cmp_npc.h"
#include "cmp_status.h"

MonsterSpawner* MonsterSpawner::instance;
MonsterSpawner::MonsterSpawner()
{
	
}
MonsterSpawner* MonsterSpawner::getInstance()
{
	if (instance == 0)
	{
		instance = new MonsterSpawner();
	}

	return instance;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_zombie(sf::Vector2f loc)
{
	auto ghost = std::make_shared<Entity>();
	ghost->setPosition(loc);
	ghost->addComponent<ActorMovementComponent>();
	auto s = ghost->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(zombieTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	s->getSprite().setOrigin(8.0f, 12.0f);
	s->setDefaultFrames();
	ghost->addComponent<HealthComponent>();
	ghost->addComponent<EnemyHealthBarComponent>();
	ghost->addComponent<StatusComponent>();
	auto p = ghost->addComponent<EnemyAttackComponent>();
	p->setLevel(0);
	ghost->addComponent<SteeringComponent>(player.get());
	ghost->addComponent<StatusComponent>();
	gameScene->getEnts().push_back(ghost);
	return ghost;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_strong_zombie(sf::Vector2f loc)
{
	auto ghost = std::make_shared<Entity>();
	ghost->setPosition(loc);
	ghost->addComponent<ActorMovementComponent>();
	auto s = ghost->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(zombieTexture2);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	s->getSprite().setOrigin(8.0f, 12.0f);
	s->setDefaultFrames();
	auto b = ghost->addComponent<HealthComponent>();
	b->setMaxHealth(200);
	ghost->addComponent<EnemyHealthBarComponent>();
	ghost->addComponent<StatusComponent>();
	auto p = ghost->addComponent<EnemyAttackComponent>();
	p->setLevel(1);
	p->setAttack(40);
	ghost->addComponent<SteeringComponent>(player.get());
	ghost->addComponent<StatusComponent>();
	gameScene->getEnts().push_back(ghost);
	return ghost;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_WELCOME(sf::Vector2f loc)
{
	auto npc = std::make_shared<Entity>();
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setBodyless();
	d->setDialogue("Shouting and screaming outside wakes you up. As a local \nwizard's apprentice you feel obligated to check this out, \nand see if anyone needs your help!\nPress E to continue. Use the staircase on the right when ready");
	gameScene->getEnts().push_back(npc);
	return npc;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_WELCOME2(sf::Vector2f loc)
{
	
	auto npc = std::make_shared<Entity>();
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setBodyless();
	d->setDialogue("To attack zombies use keys 1-5 for spells \nor SPACE for melee attack.\nYou can change keys in the options menu.");
	gameScene->getEnts().push_back(npc);
	return npc;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_MOM(sf::Vector2f loc)
{
	auto npc = std::make_shared<Entity>();
	npc->setFace(3);
	auto n = npc->addComponent<CharacterSpriteComponent>();
	n->getSprite().setTexture(npcsTexture);
	n->getSprite().setTextureRect({ 0,0,16,21 });
	n->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	n->getSprite().setOrigin(8.0f, 12.0f);
	n->setDefaultFrames();
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("MOM: Oh! You finally woke up, hon! Master Kenbobi came looking \nfor you earlier. There are zombies everywhere,and he needs \nyour help! He'll be waiting for you in the forest.");
	gameScene->getEnts().push_back(npc);
	return npc;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_MASTER_FOREST(sf::Vector2f loc)
{
	auto npc = std::make_shared<Entity>();
	npc->setFace(3);
	auto n = npc->addComponent<StaticSpriteComponent>();
	n->getSprite().setTexture(npcsTexture);
	n->getSprite().setTextureRect({ 64,0,16,21 });
	n->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	n->getSprite().setOrigin(8.0f, 12.0f);
//	n->setDefaultFrames();
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("KENBOBI: Finally here, Grasshopah! I've completed the study\n of the anomaly! I have good news, and bad news! The good news\n is, that this is not any kind of religuous apocalypse. \nCome back to my tower, we have much to discuss!");
	d->setDisappear();
	d->addSwitch(0);
	gameScene->getEnts().push_back(npc);
	return npc;
}
std::shared_ptr<Entity> MonsterSpawner::spawn_NPC_MASTER_TOWER(sf::Vector2f loc)
{
	auto npc = std::make_shared<Entity>();
	npc->setFace(3);
	auto n = npc->addComponent<StaticSpriteComponent>();
	n->getSprite().setTexture(npcsTexture);
	n->getSprite().setTextureRect({ 64,0,16,21 });
	n->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	n->getSprite().setOrigin(8.0f, 12.0f);
	//n->setDefaultFrames();
	npc->setPosition(loc);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("KENBOBI: Oh, the bad news?\n................................\nThe bad news is that this is just a demo. Sorry, lad!");
	gameScene->getEnts().push_back(npc);
	return npc;
}