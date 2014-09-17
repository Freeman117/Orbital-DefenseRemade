// This class is for sound wrapping.

#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <UtH/Audio/Sound.hpp>
#include <UtH/Audio/SoundDevice.hpp>

namespace uth
{
	class Audio
	{
	public:
		Audio();
		~Audio();

		void Load(const char* fileName);
		void Play();
		void Play(float offsetInMilliseconds);
		void PlayEffect();
		void Stop();
		void Pause();

		void Loop();
		void Loop(bool looping);
		void SetVolume(int volumePercent);
		void SetPitch(int pitchPercent);
		
		void SetSourcePosition(float x, float y, float z = 0);
		void SetSourcePosition(pmath::Vec3 position);

		void SetListenerPosition(float x, float y, float z = 0);
		void SetListenerPosition(pmath::Vec3 position);

	private:
		Sound* m_sound;
	};
}

#endif