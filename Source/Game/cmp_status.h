#pragma once
#include "ecm.h"

class StatusComponent : public Component {

protected:
	bool burning = false;
	bool blinded = false;
	bool slowed = false;
	float blindTimer = 3.0f;
	float burnTimer = 7.0f;
	float slowTimer = 2.0f;
	float burnDamageDelay = 1.0f;
	float burnDamageTimer = 1.0f;
public:
	explicit StatusComponent(Entity *p);
	StatusComponent() = delete;
	bool getBurning() { return burning; }
	bool getBlinded() { return blinded; }
	bool getSlowed() { return slowed; }
	void reset();
	void setBurning() { burning = true; }
	void setBlinded() { blinded = true; }
	void setSlowed() { slowed = true; }
	void render() override;
	void update(double dt) override;


};

