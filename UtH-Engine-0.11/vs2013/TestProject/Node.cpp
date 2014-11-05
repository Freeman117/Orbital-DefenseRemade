#include "Node.hpp"

Node::Node(int orbit_, int orbitPos_,uth::Texture* texture) : uth::Component("Node")
{
	buttonTexture = texture;
	button = new ns::Button(uthEngine.GetWindow(), buttonTexture);
	button->setCallBack([](){std::cout << "Kaikki ovat kuolleet ;__;" << std::endl; });
	button->transform.SetPosition(20,20);
	button->transform.SetScale(1.0f);
}