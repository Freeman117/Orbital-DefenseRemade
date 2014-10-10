#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <UtH/Engine/Component.hpp>
#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/Object.hpp>
#include <pmath/PMath.hpp>

#include <vector>
#include <string>
#include <memory>


namespace uth
{
	class Camera;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(const std::string &tag);
        //GameObject(const GameObject& other);
        void operator =(const GameObject&) = delete;
		virtual ~GameObject();

		void AddComponent(Component* component);
        template<typename T>
        T* GetComponent();
        template<typename T>
		T* GetComponent(const std::string& name);
		// Will actually delete the component
		void RemoveComponent(Component* component);
		void RemoveComponent(const std::string& name);
		void RemoveComponents();

		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;
		void Update(float dt) final;

		// Transform is a special component that every gameobject has

	protected:
        virtual void update(float){}
        virtual void draw(RenderTarget&){}

		std::vector<std::unique_ptr<Component>> m_components;
	};


    template<typename T>
    T* GameObject::GetComponent(const std::string& name)
    {
        for (size_t i = 0; i < m_components.size(); ++i)
        {
            if (m_components.at(i)->GetName() == name)
            {
                return static_cast<T*>(m_components[i].get());
            }
        }

        return nullptr;
    }

    template<typename T>
    T* GameObject::GetComponent()
    {
        for (size_t i = 0; i < m_components.size(); ++i)
        {
            T *c = dynamic_cast<T*>(m_components.at(i).get());
            if (c != nullptr)
            {
                return c;
            }
        }

        return nullptr;
    }
}
#endif