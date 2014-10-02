#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#define UTHDefaultScene -1

#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Layer.hpp>
#include <map>

namespace uth
{
	class Scene
    {
        friend class SceneManager;

	public:

		Scene();
		virtual ~Scene() = 0;

		virtual bool Init() = 0;
		virtual bool DeInit() = 0;

		virtual bool Update(float dt) = 0;
		virtual bool Draw() = 0;	

	protected:

		//LAYERS
		Layer* CreateLayer(const int layerId, const bool adoptObjects = true);
        bool DeleteLayer(const int layerID);
        Layer* GetLayer(const int layerID);
		GameObject* AddGameObjectToLayer(const int layerId, GameObject* gameObject);
		GameObject* RemoveGameObjectFromLayer(const int LayerId, GameObject* gameObject, const bool deleteObject = true);

        // If id < 0, all layers will be updated/drawn.
        void UpdateLayers(float dt, const int id = -1);
        void DrawLayers(RenderTarget& target, const int id = -1);

    private:

        struct LayerDeleter
        {
            void operator ()(Layer* layer)
            {
                delete layer;
            }
        };

        std::map<int, std::unique_ptr<Layer, LayerDeleter>> m_layers;
	};
}

#endif
