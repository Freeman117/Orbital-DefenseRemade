#pragma once
#ifndef PARTICLETEMPLATE_H_UTH
#define PARTICLETEMPLATE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <pmath/Rectangle.hpp>
#include <pmath/Vector4.hpp>
#include <string>
#include <functional>



namespace uth
{
    class Particle;

    class ParticleTemplate
    {
 
        friend class ParticleSystem;

    public:

        ParticleTemplate();


        void SetTexture(Texture* texture, const pmath::Rect& texCoords = pmath::Rect(0.f, 0.f, 1.f, 1.f));

        void SetLifetime(const float seconds);

        void SetSpeed(const float pixelsPerSecond);

        void SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax);

        void SetColor(const float r, const float g, const float b, const float a);


        float lifetime;
        float minSpeed,
              maxSpeed;
     
        pmath::Vec4 color;

    private:

        Texture* m_texture;
        pmath::Rect m_texCoords;

    };

}

#endif