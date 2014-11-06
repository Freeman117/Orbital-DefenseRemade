#ifndef NODE_HPP
#define NODE_HPP

#include "Button.hpp"
#include <UtH/UtHEngine.hpp>

class Node : public uth::GameObject
{
public:
	Node(int orb,int orbPos,float orbAngle, uth::Texture* texture);
	~Node(){};
	void MoveNode(float orb01Angle, float orb02Angle);

	int orbit, orbitPos;
	float orbAngle;

	uth::Texture* buttonTexture;
	ns::Button* button;
};

#endif