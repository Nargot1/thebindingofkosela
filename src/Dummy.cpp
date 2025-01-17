#include "Dummy.h"

Dummy::Dummy()
{
	rect = sf::FloatRect(800, 400, 52, 64);
}

void Dummy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite sp;
	sp.setPosition(rect.left, rect.top);
	sf::Texture texture;
	texture.loadFromFile("../Dummy.png", sf::IntRect(0, 0, rect.width, rect.height));
	sp.setTexture(texture);
	target.draw(sp);
}
