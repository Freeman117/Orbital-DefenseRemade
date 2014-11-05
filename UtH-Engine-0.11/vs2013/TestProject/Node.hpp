#ifndef NODE_HPP
#define NODE_HPP

#include <UtH/UtHEngine.hpp>
#include "Button.hpp"

class Node : public uth::Component
{
public:
	Node(int orb,int orbPos, uth::Texture* texture);
	~Node(){};

	int orbit, orbitPos;

	uth::Texture* buttonTexture;
	ns::Button* button;
};

#endif