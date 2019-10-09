#include "cmp_actor_movement.h"
#include "levelsystem.h"
#include "SystemRenderer.h"
#include "cmp_sprite.h"
#include "Game.h"
#include "EventSystem.h"
#include "cmp_char_sheet.h"
using namespace sf;
static const Vector2i directions[] = { Vector2i{ 0, 1 }, Vector2i{ 1, 0 }, Vector2i{ 0, -1 }, Vector2i{ -1, 0 } };
//ACTOR MOVEMENT
void ActorMovementComponent::render() {}

void ActorMovementComponent::update(double dt) 
{
	if (!_parent->is_forDeletion())
	{
		if (pushed)
		{
			pushTimer -= dt;
			move(pushVector);
			immobilize();
		}
		if (pushed && pushTimer <= 0)
		{
			mobilize();
			pushTimer = 0.1f;
			pushed = false;
			auto c = _parent->GetComponent<CharacterSpriteComponent>();
			c->getSprite().setColor(sf::Color::White);
		}
	}
}

ActorMovementComponent::ActorMovementComponent(Entity *p) : _speed(100.0f*WX/1280), Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f &pos) {
	return (LevelSystem::isWalkable(LevelSystem::getTileAt(pos)) && LevelSystem::isWalkable(LevelSystem::getTileAt2(pos)));
}

void ActorMovementComponent::move(const Vector2f &p) 
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp)) {
		_parent->setPosition(pp);
	}
}
void ActorMovementComponent::push(const Vector2f &p)
{
	EventSystem* evs= EventSystem::getInstance();

	pushed = true;
	pushVector = 0.3f*p;
	if (evs->if_forest0())
	{
		pushVector.x *= evs->getFM();
		pushVector.y *= evs->getFM();
	}
	pushTimer = 0.1f;
	auto c = _parent->GetComponent<CharacterSpriteComponent>();
	c->getSprite().setColor(sf::Color::Red);
}

void ActorMovementComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

void ActorMovementComponent::increaseSpeed(float speed) {
	_speed += speed;
}

ProjectileMovementComponent::ProjectileMovementComponent(Entity *p) : ActorMovementComponent(p) { _speed = 200.0f*WX/1280; }
void ProjectileMovementComponent::render() {}

void ProjectileMovementComponent::update(double dt)
{//amount to move
	if (!_parent->is_forDeletion())
	{
		auto face = _parent->getFace();
		if (face == 1) {
			move(Vector2f(0, -_speed * dt));
		}
		else if (face == 3) {
			move(Vector2f(0, _speed * dt));
		}
		else if (face == 4) {
			move(Vector2f(-_speed * dt, 0));
		}
		else if (face == 2) {
			move(Vector2f(_speed * dt, 0));
		}
	}
}
void ProjectileMovementComponent::move(const Vector2f &p)
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
	else
		_parent->setForDelete();

}
SnowComponent::SnowComponent(Entity *p) : ActorMovementComponent(p) 
{ 
	_speed = 50.0f*WX/1280; 
	dir = rand() % 2 -1;
}
void SnowComponent::render() {}

void SnowComponent::update(double dt)
{//amount to move
	dirTimer -= dt;
	if (dirTimer < 0)
	{
		dir = (dir) ? false : true;
		dirTimer = rand()%5 + 5;
	}
	Vector2f pos = _parent->getPosition();
	if(dir)
		move(Vector2f(_speed/3.0f*dt, _speed * dt));
	else
		move(Vector2f(-_speed / 3.0f*dt, _speed * dt));
		if (pos.y > WY)
		{
			_parent->setPosition(Vector2f(rand()%((int)WX), -55.0f*WX/1280));
		}
	
}
void SnowComponent::move(const Vector2f &p)
{
	auto pp = _parent->getPosition() + p;
	
		_parent->setPosition(pp);

}


//PLAYER MOVEMENT COMPONENT
PlayerMovementComponent::PlayerMovementComponent(Entity *p) : ActorMovementComponent(p) { _parent->setPlayer(); }

void PlayerMovementComponent::update(double dt) 
{
	auto c = _parent->GetComponent<CharacterSheetComponent>();
	float spd = c->getStatSpeed();
	if (spd > 0)
	{
		_speed = 100 + spd;
	}
	if (pushed)
	{
		pushTimer -= dt;
		move(pushVector);
		immobilize();
	}
	if (pushed && pushTimer <= 0)
	{
		mobilize();
		pushTimer = 0.1f;
		pushed = false;
		auto c = _parent->GetComponent<CharacterSpriteComponent>();
		c->getSprite().setColor(sf::Color::White);
	}
	if (!immobilized)
	{
		int xdir = 0, ydir = 0;
		if (Keyboard::isKeyPressed(controls[0]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == 100)) {
			_parent->setFace(1);
			move(Vector2f(0, -_speed * dt));
		}
		else if (Keyboard::isKeyPressed(controls[1]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == -100)) {
			_parent->setFace(3);
			move(Vector2f(0, _speed * dt));
		}
		else if (Keyboard::isKeyPressed(controls[3]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == -100)) {
			_parent->setFace(4);
			move(Vector2f(-_speed * dt, 0));
		}
		else if (Keyboard::isKeyPressed(controls[2]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == 100)) {
			_parent->setFace(2);
			move(Vector2f(_speed * dt, 0));
		}

		ActorMovementComponent::update(dt);
	}
}

void PlayerMovementComponent::render() {
	ActorMovementComponent::render();
}

SwordMovementComponent::SwordMovementComponent(Entity *p) : ActorMovementComponent(p) {}

void SwordMovementComponent::update(double dt)
{
	auto c = player->GetComponent<CharacterSheetComponent>();
	float spd = c->getStatSpeed();
	if (spd > 0)
	{
		_speed = 100 + spd;
	}
	
	if (player->GetComponent<PlayerMovementComponent>()->canMove())
	{
		int xdir = 0, ydir = 0;
		if (Keyboard::isKeyPressed(controls[0]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == 100)) {
			_parent->setFace(1);
			move(Vector2f(0, -_speed * dt));
		}
		else if (Keyboard::isKeyPressed(controls[1]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == -100)) {
			_parent->setFace(3);
			move(Vector2f(0, _speed * dt));
		}
		else if (Keyboard::isKeyPressed(controls[3]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == -100)) {
			_parent->setFace(4);
			move(Vector2f(-_speed * dt, 0));
		}
		else if (Keyboard::isKeyPressed(controls[2]) || (sf::Joystick::isConnected(0) && sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == 100)) {
			_parent->setFace(2);
			move(Vector2f(_speed * dt, 0));
		}

		ActorMovementComponent::update(dt);
	}
}

void SwordMovementComponent::render() {
	ActorMovementComponent::render();
}
EnemyAIComponent::EnemyAIComponent(Entity * p) : ActorMovementComponent(p) {
	_state = ROAMING;
	_speed = 100.0f;
	_direction = Vector2f(directions[rand() % 4]);
}

//ENEMY COMPONENT
void EnemyAIComponent::update(double dt) {
	//amount to move
	const auto mva = (float)(dt * _speed);
	//current position
	const Vector2f pos = _parent->getPosition();
	//next pos
	const Vector2f newPos = pos + _direction * mva;
	//inverse of current pos
	const Vector2i badDir = -1 * Vector2i(_direction);
	//random new direction
	Vector2i newDir = directions[(rand() % 4)];

	switch (_state)
	{
	case EnemyAIComponent::ROAMING:
		if (ls::getTileAt(newPos) == 10 || ls::getTileAt(pos) == 10) { //if wall in front or at waypoint
			_state = ROTATING; //start rotating
		}
		else {
			move(_direction * mva); //keep moving
		}
		break;
	case EnemyAIComponent::ROTATING:
		//don't reverse and don't pick a direction which leads to a wall
		//std::cout << badDir << ";" << _direction << std::endl;
		while (newDir == badDir || ls::getTileAt(pos + Vector2f(newDir) * mva) == 10) {
			newDir = directions[rand() % 4]; 		//pick a new direction
													//std::cout << "WHILE LOOP: " << _state << newDir << badDir << std::endl;
		}
		_direction = Vector2f(newDir);
		_state = ROTATED;
		break;
	case EnemyAIComponent::ROTATED:
		//has it left the waypoint?
		if (ls::getTileAt(newPos) != 10) {
			_state = ROAMING; //yes, roam
		}
		move(_direction * mva); //No
		break;
	default:
		break;
	}
	//////////////SET DIRECTION PARENT IS FACING//////////////////////
	if (_direction.x == 0 && _direction.y < 0)
		_parent->setFace(1);
	else if (_direction.x > 0 && _direction.y == 0)
		_parent->setFace(2);
	else if (_direction.x == 0 && _direction.y > 0)
		_parent->setFace(3);
	else if (_direction.x < 0 && _direction.y == 0)
		_parent->setFace(4);

	ActorMovementComponent::update(dt);
}

void EnemyAIComponent::render() {
	ActorMovementComponent::render();
}

CursorMovementComponent::CursorMovementComponent(Entity * p) : ActorMovementComponent(p)
{
}

void CursorMovementComponent::move(const sf::Vector2f &p)
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
}

bool CursorMovementComponent::validMove(const sf::Vector2f &p) {
	int minX = player->getPosition().x - (WX / 2);
	int maxX = player->getPosition().x + (WX / 2);
	int minY = player->getPosition().y - (WY / 2);
	int maxY = player->getPosition().y + (WY / 2);

	int mX = p.x;
	int mY = p.y;

	if (mX < minX || mY < minY || mX > maxX || mY > maxY)
	{
		Vector2f joystick(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 20, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 20);
		return false;
	}
	return true;
}

void CursorMovementComponent::update(double dt)
{
	Vector2f joystick(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 20, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 20);
	if (validMove(_parent->getPosition()) == false) {
		reset();
	}
	if (sf::Joystick::isConnected(0)) {
		if (joystick.x > 0.5f || joystick.x < -0.5f || joystick.y > 0.5f || joystick.y < -0.5f) {
			if (validMove(_parent->getPosition() + joystick)) {
				move(joystick);
			}
		}
	}
}

void CursorMovementComponent::reset() {
	_parent->setPosition(player->getPosition());
}

void CursorMovementComponent::render()
{
}

//options cursor
OptionsMovementComponent::OptionsMovementComponent(Entity * p) : ActorMovementComponent(p)
{
}

void OptionsMovementComponent::move(const sf::Vector2f &p)
{
	auto pp = _parent->getPosition() + p;
	if (validMove(pp))
	{
		_parent->setPosition(pp);
	}
}

bool OptionsMovementComponent::validMove(const sf::Vector2f &p) {
	int minX = 0;
	int maxX = WX;
	int minY = 0;
	int maxY = WY;

	int mX = p.x;
	int mY = p.y;

	if (mX < minX || mY < minY || mX > maxX || mY > maxY)
	{
		return false;
	}
	return true;
}

void OptionsMovementComponent::update(double dt)
{
	Vector2f joystick(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 20, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 20);
	if (sf::Joystick::isConnected(0)) {
		if (joystick.x > 0.5f || joystick.x < -0.5f || joystick.y > 0.5f || joystick.y < -0.5f) {
			if (validMove(_parent->getPosition() + Vector2f(joystick.x / 5, joystick.y / 5))) {
				move(Vector2f(joystick.x / 5, joystick.y / 5));
			}
		}
	}
}

void OptionsMovementComponent::render()
{
}

void OptionsMovementComponent::reset()
{
}
