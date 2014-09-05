#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include <UtH/Platform/OpenGL.hpp>

#include <assert.h>
#include <iostream>
#include <cstdarg>
#include <cstdio>

#include <AL/al.h>
#include <AL/alc.h>

#if defined(UTH_SYSTEM_ANDROID)
	#include <android/log.h>
	#ifndef LOG_TAG
		#define LOG_TAG	"uth-engine"
	#endif
	//#ifndef LOGI
	//	#define LOGI(...)	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
	//#endif
	//#ifndef LOGE
	//	#define LOGE(...)	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
	//#endif
	static inline void WriteError(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		__android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, text, v);
		va_end(v);
	}
	static inline void WriteWarning(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		__android_log_vprint(ANDROID_LOG_WARN, LOG_TAG, text, v);
		va_end(v);
	}
	static inline void WriteLog(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, text, v);
		va_end(v);
	}

	static inline void CheckEGLError()
	{
		EGLint error = eglGetError();
		if(error != EGL_SUCCESS)
		{
			WriteWarning("EGL Function Failed: %d\n", error);
		}
	}
#elif defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
	static void WriteError(const char* text, ...)
	{
		printf(	
				"\n********ERROR********"
				"\n");

		va_list v;
		va_start(v, text);
		vprintf(text, v);
		va_end(v);

		printf(
				"\n*********************"
				"\n\n");

		//assert(false);  //GL_INVALID_ENUM would crash
	}
	static void WriteWarning(const char* text, ...)
	{
		printf(	
				"\n-------WARNING-------"
				"\n");

		va_list v;
		va_start(v, text);
		vprintf(text, v);
		va_end(v);

		printf(
				"\n---------------------"
				"\n\n");
	}
	static void WriteLog(const char* text, ...)
	{
	#ifndef NDEBUG
		va_list v;
		va_start(v, text);
		vprintf(text, v);
		va_end(v);
	#endif
	}
#endif

static inline void PrintGLString(const char* name, GLenum s)
{
	const char *v = (const char *) glGetString(s);

	WriteLog("GL %s = %s\n", name, v);
}

static inline void CheckGLError(const char* op)
{
	for (GLint error = glGetError(); error; error
		= glGetError()) {
			
			WriteError("after %s() glError (0x%x)", op, error);
	}
}

static inline void CheckALError(const char* op)
{
	for(ALCenum error = alGetError(); error != ALC_NO_ERROR; error = alGetError())
	{
		WriteError("after %s() alError (0x%x)", op, error);
	}
}
#endif