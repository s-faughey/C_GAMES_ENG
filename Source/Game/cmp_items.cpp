#include "cmp_items.h"
#include "cmp_char_sheet.h"
ItemComponent::ItemComponent(Entity *p) : Component(p) ,_sprite(std::make_shared<sf::Sprite>()) {
	
	highlight.setFillColor(sf::Color(244, 203, 66, 255));
	highlight.setSize({ 0.045f*WX, 0.07f * WY });
	
}

sf::Sprite& ItemComponent::getSprite()  {
	return *_sprite;
}
void ItemComponent::render()
{

	if (equipped)
		Renderer::queue(0, &highlight);

	if (pickedUp)
		Renderer::queue(0, _sprite.get());
	else
		Renderer::queue(3, _sprite.get());

}
void ItemComponent::update(double dt)
{
	if (equipped)
		highlight.setPosition(_parent->getPosition() - sf::Vector2f(0.023f*WX, 0.03f*WY));

	_sprite->setPosition(_parent->getPosition());

	if(!pickedUp)
	if(length(_parent->getPosition() - player->getPosition()) < 20.0f)
	{
		auto x= player->GetComponent<CharacterSheetComponent>();
		if(x->pickUp(_this));
			pickedUp = true;
	}

}
