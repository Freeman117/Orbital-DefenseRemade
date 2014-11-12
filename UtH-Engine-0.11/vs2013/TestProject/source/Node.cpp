#include "Node.hpp"

Node::Node(int orbit_, int orbitPos_, float orbAngle_, uth::Texture* texture) : uth::GameObject()
{
	buttonTexture = texture;
	orbit = orbit_;
	orbitPos = orbitPos_;
	button = new ns::Button(uthEngine.GetWindow(), buttonTexture);
	button->setCallBack([](){uth::WriteLog("lelelel"); });
	button->transform.SetPosition(cosf(orbAngle_ + orbitPos_*(pmath::pi / 3 / orbit_)) * 115 * orbit_, sinf(orbAngle_ + orbitPos_*(pmath::pi / 3 / orbit_)) * 115 * orbit_);
	button->transform.SetScale(1.0f);
	AddChild(button);
}
void Node::MoveNode(float orb01angle, float orb02angle)
{
	if (orbit == 1)
		button->transform.SetPosition(cosf(orb01angle + orbitPos*(pmath::pi / 3 / orbit)) * 115 * orbit, sinf(orb01angle + orbitPos*(pmath::pi / 3 / orbit)) * 115 * orbit);
	else if (orbit == 2)
		button->transform.SetPosition(cosf(orb02angle + orbitPos*(pmath::pi / 3 / orbit)) * 115 * orbit, sinf(orb02angle + orbitPos*(pmath::pi / 3 / orbit)) * 115 * orbit);
}