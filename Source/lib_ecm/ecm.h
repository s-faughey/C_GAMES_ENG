#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "maths.h"
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>

class Component;

class Entity {
private:
	std::vector<std::shared_ptr<Component>> _components;
	sf::Vector2f _position;
	int face=rand()%3+1;
	float _rotation=0.0f;
	bool _alive=true;
	bool _moving = false;
	bool _visible=true;
	bool _forDeletion=false;
	bool _isPlayer = false;
public:
	Entity();
	void setMoving(bool m) { _moving = m; }
	virtual ~Entity() = default;
	bool isMoving() { return _moving; }
	virtual void update(const double dt);
	virtual void render();
	int getFace() { return face; }
	void setFace(int f) { face = f; }
	sf::Vector2f &getPosition();
	void setPosition(const sf::Vector2f &pos);
	bool is_forDeletion() const;
	float getRotation()	const;
	void setRotation(float _rot);
	bool isPlayer() { return _isPlayer; }
	void setPlayer() { _isPlayer = true; }
	bool isAlive() const;
	void setAlive(bool _value);
	void setForDelete();
	bool isVisible() const;
	void setVisible(bool _value);


	template <typename T, typename... Targs>
	std::shared_ptr<T> addComponent(Targs... params) {
		static_assert(std::is_base_of<Component, T>::value, "must be a component!");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params...));
		_components.push_back(sp);
		return sp;
	}

	const std::vector<std::shared_ptr<Component>>& getComponents() {
		return _components;
	}

	template<typename ComponentType>
	ComponentType* GetComponent() {
		for (unsigned int i = 0; i < _components.size(); ++i) {
			if (ComponentType* cmp = dynamic_cast<ComponentType*>(_components[i].get())) {
				return cmp;
			}
		}

		return nullptr;
	}

};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(double dt);
	void render();
};

class Component {
protected:
	Entity* _parent;
	bool _forDeletion;
	explicit Component(Entity *p);

public:
	Component() = delete;
	bool is_forDeletion();
	void setForDeletion();
	virtual void update(double dt) = 0;
	virtual void render() = 0;
	virtual ~Component();
};