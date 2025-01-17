#include "Entity.h"


class Dummy : public sf::Drawable, protected Entity
{
public:
	sf::FloatRect rect;

	Dummy();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};