#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

using namespace uth;

GameObject::GameObject()
    : transform(*(new Transform())),
      parent(nullptr),
      m_name(""),
      m_active(true)
	  
{
	AddComponent(&transform);
	transform.parent = this;
}

GameObject::GameObject(const std::string &name)
    : transform(*(new Transform())),
      parent(nullptr),
      m_name(name),
	  m_active(true)
{
	AddComponent(&transform);
	transform.parent = this;
}

uth::GameObject::GameObject(const GameObject& other)
    : transform(*(new Transform(other.transform))),
      parent(other.parent),
      components(),
      m_name(other.m_name),
      m_active(other.m_active)
{
    AddComponent(&transform);
    transform.parent = this;
}

GameObject::~GameObject()
{
	RemoveComponents();
}

void GameObject::SetActive(bool value)
{
	m_active = value;
}

const bool GameObject::IsActive() const
{
	return m_active;
}

void GameObject::AddComponent(Component* component)
{
	components.emplace_back(component);
	component->parent = this;
	component->Init();
}

const std::string GameObject::GetName() const
{
	return m_name;
}

void GameObject::RemoveComponent(Component* component)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i).get() == component)
		{
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponent(const std::string& name)
{
	for(size_t i = 0; i < components.size(); ++i)
	{
		if(components.at(i)->GetName() == name)
		{
			components.erase(components.begin() + i);
		}
	}
}

void GameObject::RemoveComponents()
{
	components.clear();
}

void GameObject::Draw(RenderTarget& target)
{
	if(!m_active)
		return;

	target.Bind();

	draw(target);

	for (auto itr = components.begin(); itr != components.end(); ++itr)
	{
		target.GetShader().Use();
		auto component = itr->get();
		if (component->IsActive())
			component->Draw(target);
	}
}

void GameObject::Update(float dt)
{
	if(!m_active)
		return;

	update(dt);

	for (auto itr = components.begin(); itr != components.end(); ++itr)
	{
		auto component = itr->get();
		if (component->IsActive())
			component->Update(dt);
	}
}

void GameObject::draw(RenderTarget& target)
{
	Shader& shader = target.GetShader();

	shader.Use();
	shader.SetUniform("unifModel", transform.GetTransform());
	shader.SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());
}