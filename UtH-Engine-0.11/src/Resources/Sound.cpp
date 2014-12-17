#include <UtH/Resources/Sound.hpp>
#include <UtH/Platform/Typedefs.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <UtH/Platform/SoundDevice.hpp>
#include <UtH/Platform/FileManager.hpp>

#include <sndfile/sndfile.h>

using namespace uth;



Sound::Sound()
	: loop(false),
	  enginePaused(false),
	  duration(0.1f),
	  _posX(0), _posY(0), _posZ(0)
{
	copy = nullptr;
}

Sound::~Sound()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	for(size_t i = 0; i < tempSource.size(); i++)
	{
		alDeleteSources(1, &tempSource[i]);
	}
}

// PUBLIC
void Sound::Play()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	alSourcePlay(source);

	enginePaused = false;
}

void Sound::Play(float offset)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	if(offset >= duration)
		WriteError("Offset %f exceeds %f duration!", offset, duration);
	else
	{
		alSourcei(source, AL_SEC_OFFSET, static_cast<ALint>(offset));
		alSourcePlay(source);
	}

	enginePaused = false;
}

void Sound::PlayEffect()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	if(Status() != AL_PLAYING)
		alSourcePlay(source);
	else
		effectCopy();

	enginePaused = false;
}

void Sound::Stop()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	alSourceStop(source);
}

void Sound::Pause()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	if (Status() == AL_PLAYING)
		alSourcePause(source);
	else if (Status() == AL_PAUSED)
		alSourcePlay(source);
}
void Sound::Pause(bool pause)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	if (Status() == AL_PLAYING && pause)
		alSourcePause(source);
	else if (Status() == AL_PAUSED && !pause)
		alSourcePlay(source);
}

void Sound::Loop()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	if(loop)
	{
		alSourcei(source, AL_LOOPING, AL_FALSE);
		loop = false;
	}
	else if(!loop)
	{
		alSourcei(source, AL_LOOPING, AL_TRUE);
		loop = true;
	}
}

void Sound::Loop(bool looping)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	loop = looping;

	ALboolean looper;
	if(looping == 0)
		looper = AL_FALSE;
	else
		looper = AL_TRUE;

	alSourcei(source, AL_LOOPING, looper);
	CheckALError("al_sourcei AL_LOOPING");
}

void Sound::SetVolume(int volumePercent)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	float newVolume = float(volumePercent) / 100.0f;
	alSourcef(source, AL_GAIN, newVolume);
	CheckALError("al_sourcef AL_GAIN");
}

void Sound::SetListenerVolume(int volumePercent)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	float newVolume = float(volumePercent) / 100.0f;
	alListenerf(AL_GAIN, newVolume);
	CheckALError("al_Listenerf AL_GAIN");
}

void Sound::SetPitch(int pitchPercent)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	float newPitch = float(pitchPercent) / 100.0f;
	alSourcef(source, AL_PITCH, newPitch);
	CheckALError("al_sourcef AL_PITCH");
}

void Sound::SetSourcePosition(float x, float y, float z)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	_posX = x; _posY = y; _posZ = z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	//alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	//CheckALError("al_source3f AL_VELOCITY");
}
void Sound::SetSourcePosition(pmath::Vec3 position)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	_posX = position.x; _posY = position.y; _posZ = position.z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	//alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	//CheckALError("al_source3f AL_VELOCITY");
}

void Sound::SetListenerPosition(float x, float y, float z)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	alListener3f(AL_POSITION, x, y, z);
	CheckALError("al_slistener3f AL_POSITION");
	//alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	//CheckALError("al_listener3f AL_VELOCITY");
}
void Sound::SetListenerPosition(pmath::Vec3 position)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	alListener3f(AL_POSITION, position.x, position.y, position.z);
	CheckALError("al_slistener3f AL_POSITION");
	//alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	//CheckALError("al_listener3f AL_VELOCITY");
}

bool Sound::IsPlaying()
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return false;

	if (Status() == AL_PLAYING)
		return true;
	else
		return false;
}

void Sound::StopEffects()
{
	for (int i = 0; i < tempSource.size(); i++)
	{
		alSourceStop(tempSource[i]);
	}
}

// PRIVATE
bool Sound::LoadFromFile(const std::string& filePath)
{
	Initialize(filePath);

	if (!source)
		return false;

	m_loaded = true;
	return true;
}
void Sound::Unload()
{

}
bool Sound::EnsureLoaded()
{
	if (m_loaded)
		return true;
	const bool result = LoadFromFile(uthRS.FilePath(this, ResourceManager::Sounds));
	//assert(result);
	return result;
}

void Sound::Initialize(std::string fileName)
{
	if (!SoundDevice::getInstance().DeviceInitialized())
		return;

	SF_INFO soundInfo;

#if defined(UTH_SYSTEM_ANDROID)
	AAsset* asset = FileManager::loadSound(fileName);

	SF_VIRTUAL_IO virtualIO;
	virtualIO.get_filelen = &FileManager::getAssetLength;
	virtualIO.seek = &FileManager::seekAsset;
	virtualIO.read = &FileManager::readAsset;
	virtualIO.tell = &FileManager::tellAsset;

	SNDFILE* file = sf_open_virtual(&virtualIO, SFM_READ, &soundInfo, asset);
#elif defined(UTH_SYSTEM_WINDOWS)
	SNDFILE* file = sf_open(("assets/" + fileName).c_str(), SFM_READ, &soundInfo);
#endif

	if (!file)
	{
		int error = sf_error(file);
		WriteError("Failed to open sound file, error &d", file, error);
		WriteError(sf_error_number(error));
	}

	//WriteLog("Frames: %d\n", soundInfo.frames);
	//WriteLog("Samplerate: %d\n", soundInfo.samplerate);
	//WriteLog("Channels: %d\n", soundInfo.channels);
	//WriteLog("Format: %d\n", soundInfo.format);


	int frames = static_cast<int>(soundInfo.frames * soundInfo.channels);
	int channels = soundInfo.channels;
	int sampleRate = soundInfo.samplerate;

	short* soundBuffer = new short[frames];
	sf_read_short(file, soundBuffer, frames);

	sf_close(file);


	Sound::CreateSources(source);
	// Create buffer
	alGenBuffers(1, &buffer);
	CheckALError("alGenBuffers");

	//int channels = buf->GetSoundInfo().channels;

	alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO16:AL_FORMAT_MONO16 ,
		soundBuffer,
		frames * sizeof(short),
		sampleRate);

	CheckALError("alBufferData");

	alSourcei(source, AL_BUFFER, buffer);
	CheckALError("alSourcei");

	duration = static_cast<float>(frames)
		/ static_cast<float>(sampleRate)
		/ static_cast<float>(channels);
	//WriteLog("duration: %f\n", duration);
	//m_sounds.push_back(this);
}

void Sound::CreateSources(ALuint &source)
{
	// create source
	alGenSources(1, &source);
	CheckALError("alGen_sources");
	// set normal pitch = 1
	alSourcef(source, AL_PITCH, 1);
	CheckALError("al_sourcef AL_PITCH");
	// set maximum volume = 1
	alListenerf(AL_GAIN, 1);
	CheckALError("al_Listenerf AL_GAIN");
	alSourcef(source, AL_GAIN, 1);
	CheckALError("al_sourcef AL_GAIN");
	// set position to center
	alSource3f(source, AL_POSITION, 0, 0, 0);
	CheckALError("al_source3f AL_POSITION");
	// set velocity to center
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	CheckALError("al_source3f AL_VELOCITY");
	// default set for loop = false
	alSourcei(source, AL_LOOPING, AL_FALSE);
	CheckALError("al_sourcei AL_LOOPING");
}
// Returns in what state source is currently.
ALint Sound::Status()
{
	ALint _state;
	alGetSourcei(source, AL_SOURCE_STATE, &_state);
	return _state;
}
// Copies effect sound into vector and starts to play it.
// Removes already finished playback from beginning of vector.
void Sound::effectCopy()
{
	float pitch, gain;
	alGetSourcef(source, AL_PITCH, &pitch);
	CheckALError("al_getsourcef AL_PITCH");
	alGetListenerf(AL_GAIN, &gain);
	CheckALError("al_getsourcef AL_GAIN");

	for (int i = 0; i < tempSource.size(); i++)
	{
		ALint tempState;
		alGetSourcei(tempSource[i], AL_SOURCE_STATE, &tempState);
		if (tempState == AL_STOPPED)
		{
			alSourcef(tempSource[i], AL_PITCH, pitch);
			CheckALError("al_sourcef AL_PITCH");
			alSourcef(tempSource[i], AL_GAIN, gain);
			CheckALError("al_sourcef AL_GAIN");
			alSource3f(tempSource[i], AL_POSITION, _posX, _posY, _posZ);
			CheckALError("al_source3f AL_POSITION");
			alSource3f(tempSource[i], AL_VELOCITY, _posX, _posY, _posZ);
			CheckALError("al_source3f AL_VELOCITY");
			alSourcePlay(tempSource[i]);
			return;
		}		

	}
	
	ALuint t_source;
	Sound::CreateSources(t_source);
	// We want to put copied sound in same location as copied source.
	alSourcef(t_source, AL_PITCH, pitch);
	CheckALError("al_sourcef AL_PITCH");
	alSourcef(t_source, AL_GAIN, gain);
	CheckALError("al_sourcef AL_GAIN");
	alSource3f(t_source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	alSource3f(t_source, AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_VELOCITY");

	alSourcei(t_source, AL_BUFFER, buffer);
	CheckALError("alSourcei AL_BUFFER");

	// Push new source into vector.
	
	tempSource.push_back(t_source);
	alSourcePlay(tempSource.back());
	// Remove source from beginning of vector as it finishes playback.
	//tempSource.erase(tempSource.begin());
}

Sound* Sound::Copy()
{
	copy = new Sound();
	copy->loop = loop;
	copy->enginePaused = enginePaused;
	copy->duration = duration;
	copy->_posX = _posX;
	copy->_posY = _posY;
	copy->_posZ = _posZ;


	alGenBuffers(1, &copy->buffer);
	CheckALError("alGenBuffers");

	copy->CreateSources(copy->source);
	copy->buffer = buffer;

	alSourcei(copy->source, AL_BUFFER, copy->buffer);
	CheckALError("alSourcei AL_BUFFER");

	float value;
	alGetSourcef(source, AL_PITCH, &value);
	CheckALError("alGetSourcef AL_PITCH");
	alSourcef(copy->source, AL_PITCH, value);
	CheckALError("alSourcef AL_PITCH");
	alGetListenerf(AL_GAIN, &value);
	CheckALError("alGetSourcef AL_GAIN");
	alListenerf(AL_GAIN, value);
	CheckALError("alListenerf AL_GAIN");
	alSourcef(copy->source, AL_GAIN, value);
	CheckALError("alSourcef AL_GAIN");

	float posX, posY, posZ;
	alGetSource3f(source, AL_POSITION, &posX, &posY, &posZ);
	CheckALError("alGetSource3f AL_POSITION");
	alSource3f(copy->source, AL_POSITION, posX, posY, posZ);
	CheckALError("alSource3f AL_POSITION");

	alGetSource3f(source, AL_VELOCITY, &posX, &posY, &posZ);
	CheckALError("alGetSource3f AL_VELOCITY");
	alSource3f(copy->source, AL_VELOCITY, posX, posY, posZ);
	CheckALError("alSource3f AL_VELOCITY");

	//alSourcei(copy->source, AL_LOOPING, copy->loop);
	//CheckALError("alGetSourcei AL_LOOPING");

	return copy;
}