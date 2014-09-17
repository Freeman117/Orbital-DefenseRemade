#pragma once
#ifndef PARTICLESYSTEM_H_UTH
#define PARTICLESYSTEM_H_UTH

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>

namespace uth
{

    class ParticleSystem : public GameObject
    {
    public:

        ParticleSystem(const size_t reserve);

        ~ParticleSystem(){};


        virtual void Emit(const unsigned int amount);

        void AddAffector(const Affector& affector);

        void SetTemplate(const ParticleTemplate& pTemplate);

        void Clear(const bool particles = true, const bool affectors = true);


    private:
     
        void update(float dt);
        void draw(RenderTarget& target);

        ParticleTemplate m_template;
        SpriteBatch m_batch;

        std::vector<Affector> m_affectors;
        std::vector<Particle> m_particles;

    };

}

#endif