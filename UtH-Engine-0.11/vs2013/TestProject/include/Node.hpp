#ifndef NODE_HPP
#define NODE_HPP

#include "Button.hpp"
#include <UtH/UtHEngine.hpp>
#include <array>
#include <memory>

class Node : public uth::GameObject
{
public:
	Node(int orb, int orbPos, float orbAngle, uth::Texture* texture);
	~Node(){};
	void MoveNode(float orb01Angle, float orb02Angle);
	void SetTrue();

	bool GetTrue();
	int GetOrbit();
	int GetOrbitPos();

	uth::Texture* buttonTexture;
	ns::Button* button;

private:
	int orbit, orbitPos;
	float orbAngle;
	bool isTrue;
};

#endif