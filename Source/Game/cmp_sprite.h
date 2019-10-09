#pragma once
#include "ecm.h"

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;

public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	sf::Shape &getShape() const;

	template<typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

class CharacterSpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;
	int facing; //direction player/npc is facing 1 - north, then clockwise (1-4)
	int frame = 0; //Current frame of player/npc animation (goes from 0 to 3)
	const float AnimationDelay = 0.15f; //delay between frames of animation
	float AnimationCounter = 0.15f; //used as a count-down between frames, then set to AnimationDelay when frame changes
	std::vector<sf::IntRect> walkingAnimationDown;
	std::vector<sf::IntRect> walkingAnimationUp;
	std::vector<sf::IntRect> walkingAnimationRight;
	std::vector<sf::IntRect> walkingAnimationLeft;
public:
	void setDefaultFrames();
	void addFrameUp(sf::IntRect x) {walkingAnimationUp.push_back(x);}
	void addFrameDown(sf::IntRect x) { walkingAnimationDown.push_back(x); }
	void addFrameRight(sf::IntRect x) { walkingAnimationRight.push_back(x); }
	void addFrameLeft(sf::IntRect x) { walkingAnimationLeft.push_back(x); }
	CharacterSpriteComponent() = delete;
	explicit CharacterSpriteComponent(Entity *p);
	
	void update(double dt) override;
	void setScale();
	void render() override;
	
	sf::Sprite &getSprite() const;
	
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};
class DamageTextComponent : public Component {
protected:
	sf::Text damageText;
	std::vector<sf::Text> damageArray;
	float textTime = 0.4f;
public:
	DamageTextComponent() = delete;
	explicit DamageTextComponent(Entity *p);
	void setText(int x);
	void update(double dt) override;
	void render() override;

};


class EnemyHealthBarComponent : public Component {
protected:
	bool slow = false;
	bool burn = false;
	bool blind = false;
	bool back_to_normal = false;
	sf::RectangleShape hp;
	sf::Text text_hp;
	sf::Sprite status;
	float blindTextTime = 0.5f;
	float slowTextTime = 0.5f;
	float burnTextTime = 0.5f;
public:
	EnemyHealthBarComponent() = delete;
	void setNormal() { back_to_normal = true; slow = false; burn = false; blind = false; }
	void setSlow() { slow = true; }
	void setBurn() { burn = true; }
	void setBlind() { blind = true; }
	explicit EnemyHealthBarComponent(Entity *p);
	void update(double dt) override;
	void render() override;

};
class StaticSpriteComponent : public Component {
protected:
	bool spin = false;
	std::shared_ptr<sf::Sprite> _sprite;

public:
	void setScale();
	void addSpin() { spin = true; }
	StaticSpriteComponent() = delete;
	explicit StaticSpriteComponent(Entity *p);
	void update(double dt) override;
	void render() override;
	sf::Sprite &getSprite() const;
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};
class AnimatedSpriteComponent : public Component {
protected:
	int priority = 2;
	bool singularPlay = false;
	bool animationDirection = true;
	int frame = 0; //Current frame of player/npc animation (goes from 0 to 3)
	float AnimationDelay = 0.15f; //delay between frames of animation
	float AnimationCounter = 0.15f; //used as a count-down between frames, then set to AnimationDelay when frame changes
	int max_frames = 0;
	bool spin = false;
	std::shared_ptr<sf::Sprite> _sprite;
	std::vector<sf::IntRect> animationFrames;
public:
	void setPriority(int x) { priority = x; }
	void playOnce() { singularPlay = true; }
	void setDelay(float x) { AnimationDelay = x; }
	void setScale();
	void addFrame(sf::IntRect f) { max_frames = animationFrames.size(); animationFrames.push_back(f); }
	AnimatedSpriteComponent() = delete;
	explicit AnimatedSpriteComponent(Entity *p);
	void update(double dt) override;
	void render() override;
	sf::Sprite &getSprite() const;
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};

class CursorSpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;

public:
	void setScale();
	CursorSpriteComponent() = delete;
	explicit CursorSpriteComponent(Entity *p);
	void update(double dt) override;
	void render() override;
	sf::Sprite &getSprite() const;
	template<typename T, typename... Targs>
	void setSprite(Targs... params) {
		_sprite.reset(new T(params...));
	}
};