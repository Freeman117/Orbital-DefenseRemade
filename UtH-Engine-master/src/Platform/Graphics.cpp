#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Configuration.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Debug.hpp>
#include <iostream>
#include <algorithm>


namespace uth
{
	static int shaderTypes[SHADERTYPE_LAST] =			{GL_VERTEX_SHADER,
														GL_FRAGMENT_SHADER};
	static int dataTypes[DATATYPE_LAST] =				{GL_BYTE,
														GL_UNSIGNED_BYTE,
														GL_SHORT,
														GL_UNSIGNED_SHORT,
														GL_INT,
														GL_UNSIGNED_INT,
														GL_FLOAT};
	static int bufferTypes[BUFFERTYPE_LAST] =			{GL_ARRAY_BUFFER,
														GL_ELEMENT_ARRAY_BUFFER};
	static int usageTypes[USAGETYPE_LAST] =				{GL_STREAM_DRAW,
														GL_STATIC_DRAW,
														GL_DYNAMIC_DRAW};
	static int pixelStoreParams[PIXELSTOREPARAM_LAST] = {GL_PACK_ALIGNMENT,
														GL_UNPACK_ALIGNMENT};
	static int textureTypes[TEXTURETYPE_LAST] =			{GL_TEXTURE_2D,
														GL_TEXTURE_CUBE_MAP};
	static int textureFilters[TEXTUREFILTER_LAST] =		{GL_NEAREST,
														GL_LINEAR,
														GL_REPEAT,
														GL_CLAMP_TO_EDGE};
	static int imageFormats[IMAGEFORMAT_LAST] =			{GL_RGB,
														GL_RGBA};
	static int textureParams[TEXTUREPARAM_LAST] =		{GL_TEXTURE_MIN_FILTER,
														GL_TEXTURE_MAG_FILTER,
														GL_TEXTURE_WRAP_S,
														GL_TEXTURE_WRAP_T};
	static int textureUnits[TEXUNIT_LAST] =				{GL_TEXTURE0,
														GL_TEXTURE1,
														GL_TEXTURE2,
														GL_TEXTURE3,
														GL_TEXTURE4,
														GL_TEXTURE5,
														GL_TEXTURE6,
														GL_TEXTURE7};
	static int primitiveTypes[PRIMITIVETYPE_LAST] =		{GL_POINTS,
														GL_LINE_STRIP,
														GL_LINE_LOOP,
														GL_LINES,
														GL_TRIANGLE_STRIP,
														GL_TRIANGLE_FAN,
														GL_TRIANGLES};
	static int depthFunctions[DEPTHFUNCTION_LAST] =		{GL_NEVER,
														GL_LESS,
														GL_EQUAL,
														GL_LEQUAL,
														GL_GREATER,
														GL_NOTEQUAL,
														GL_GEQUAL,
														GL_ALWAYS};
	static int blendFunctions[BLENDFUNCTION_LAST] =		{GL_ZERO,
														GL_ONE,
														GL_SRC_COLOR,
														GL_ONE_MINUS_SRC_COLOR,
														GL_DST_COLOR,
														GL_ONE_MINUS_DST_COLOR,
														GL_SRC_ALPHA,
														GL_ONE_MINUS_SRC_ALPHA,
														GL_DST_ALPHA,
														GL_ONE_MINUS_DST_ALPHA,
														GL_CONSTANT_COLOR,
														GL_ONE_MINUS_CONSTANT_COLOR,
														GL_CONSTANT_ALPHA,
														GL_ONE_MINUS_CONSTANT_ALPHA};
	static int faceCullings[FACECULLING_LAST] =			{GL_FRONT,
														GL_BACK,
														GL_FRONT_AND_BACK};

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Shaders

	const unsigned int Graphics::CreateShaderProgram()
	{
		const unsigned int i = glCreateProgram();
		CheckGLError("glCreateProgram");
		if(glIsProgram(i) == GL_FALSE)WriteWarning("m_program isn't GLprogram");

		return i;
	}

	bool Graphics::CreateShader(const ShaderType type, const int shaderProgram, const char* shaderCode)
	{
		if (!shaderCode) return false;

		unsigned int shader = glCreateShader(shaderTypes[type]);
		CheckGLError("glCreateShader");
		glShaderSource(shader, 1, &shaderCode, nullptr);
		CheckGLError("glShaderSource");

		glCompileShader(shader);
		CheckGLError("glGetShaderiv");

		int infoLenght;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLenght);
		CheckGLError("glGetShaderiv");
		if(infoLenght > 1)
		{
			switch (type)
			{
			case VERTEX_SHADER:
				WriteLog("\nVertex ");
				break;
			case FRAGMENT_SHADER:
				WriteLog("\nFragment ");
				break;
			default:
				break;
			}
			WriteLog("Shader Log:\n");
			char* buf = new char[infoLenght];
			glGetShaderInfoLog(shader, infoLenght, nullptr, buf);
			CheckGLError("glGetShaderInfoLog");
			WriteLog("%s", buf);
			delete[] buf;
		}


		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		CheckGLError("glDeleteShader");

		if (!success)
		{
			glDeleteShader(shader);
			WriteWarning("Shader compilation failed");
			return false;
		}

		glAttachShader(shaderProgram, shader);
		CheckGLError("glDeleteShader");
		glDeleteShader(shader);
		CheckGLError("glDeleteShader");

		return true;
	}

	bool Graphics::LinkShaderProgram(const int shaderProgram)
	{
		if(glIsProgram(shaderProgram) == GL_FALSE)
			WriteWarning("shaderProgram isn't GLprogram");
		CheckGLError("glIsProgram");

		glLinkProgram(shaderProgram);
		CheckGLError("glLinkProgram");


		int infoLenght;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLenght);
		CheckGLError("glGetProgramiv INFO");
		if(infoLenght > 1)
		{
			WriteLog("\nShader Program (%d) Log:\n", shaderProgram);
			char* buf = new char[infoLenght];
			glGetProgramInfoLog(shaderProgram, infoLenght, nullptr, buf);
			CheckGLError("glGetProgramInfoLog");
			WriteLog(buf);
			delete[] buf;
		}
		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		CheckGLError("glGetProgramiv LINK");

		if (!success)
		{
			DestroyShaderProgram(shaderProgram);
			WriteWarning("Shader link failed");
			return false;
		}
		return true;
	}

	void Graphics::BindProgram(const int shaderProgram)
	{
		if (shaderProgram)
			oglCheck(glUseProgram(shaderProgram));
	}

	void Graphics::UnbindProgram()
	{
		oglCheck(glUseProgram(0));
	}

	void Graphics::DestroyShaderProgram(const int shaderProgram)
	{
		oglCheck(glDeleteProgram(shaderProgram));
	}

	int Graphics::GetUniformLocation(const int shaderProgram, const char* name)
	{
		return glGetUniformLocation(shaderProgram, name);
	}

	int Graphics::GetAttributeLocation(const int shaderProgram, const char* name)
	{
		return glGetAttribLocation(shaderProgram, name);
	}

	void Graphics::SetUniform(const int location, const int x)
	{
		oglCheck(glUniform1i(location, x));
	}

	void Graphics::SetUniform(const int location, const float x)
	{
		oglCheck(glUniform1f(location, x));
	}

	void Graphics::SetUniform(const int location, const float x, const float y)
	{
		oglCheck(glUniform2f(location, x, y));
	}

	void Graphics::SetUniform(const int location, const float x, const float y, const float z)
	{
		oglCheck(glUniform3f(location, x, y, z));
	}

	void Graphics::SetUniform(const int location, const float x, const float y, const float z, const float w)
	{
		oglCheck(glUniform4f(location, x, y, z, w));
	}

	void Graphics::SetUniform(const int location, const pmath::Vec2& vector)
	{
		oglCheck(glUniform2fv(location, 1, &vector.x));
	}

	void Graphics::SetUniform(const int location, const pmath::Vec3& vector)
	{
		oglCheck(glUniform3fv(location, 1, &vector.x));
	}

	void Graphics::SetUniform(const int location, const pmath::Vec4& vector)
	{
		oglCheck(glUniform4fv(location, 1, &vector.x));
	}

	void Graphics::SetUniform(const int location, const pmath::Mat3& matrix)
	{
		oglCheck(glUniformMatrix3fv(location, 1, GL_FALSE, matrix.ptr()));
	}

	void Graphics::SetUniform(const int location, const pmath::Mat4& matrix)
	{
		oglCheck(glUniformMatrix4fv(location, 1, GL_FALSE, matrix.ptr()));
	}

	void Graphics::EnableVertexAttribArray(const int location)
	{
		oglCheck(glEnableVertexAttribArray(location));
	}

	void Graphics::DisableVertexAttribArray(const int location)
	{
		oglCheck(glDisableVertexAttribArray(location));
	}

	void Graphics::SetVertexAttribPointer(const int location, const int size, DataType type, const int stride, const void* pointer)
	{
		oglCheck(glVertexAttribPointer(location, size, dataTypes[type], GL_FALSE, stride, pointer));
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Buffers

	void Graphics::GenerateBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glGenBuffers(amount, buffers));
	}

	void Graphics::DeleteBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glDeleteBuffers(amount, buffers));
	}

	void Graphics::BindBuffer(BufferType type, const unsigned int buffer)
	{
		oglCheck(glBindBuffer(bufferTypes[type], buffer));
	}

	void Graphics::SetBufferData(BufferType type, const unsigned int size, const void* data, UsageType usageType)
	{
		oglCheck(glBufferData(bufferTypes[type], size, data, usageTypes[usageType]));
	}

	void Graphics::SetBufferSubData(BufferType type, const unsigned int offset, const unsigned int size, const void* data)
	{
		oglCheck(glBufferSubData(bufferTypes[type], offset, size, data));
	}


	/////////////////////////////////////////////////////////
	// Framebuffer functions
	void Graphics::GenerateFrameBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glGenFramebuffers(amount, buffers));
	}

	void Graphics::DeleteFrameBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glDeleteFramebuffers(amount, buffers));
	}

	void Graphics::BindFrameBuffer(const unsigned int buffer)
	{
		oglCheck(glBindFramebuffer(GL_FRAMEBUFFER, buffer));
	}

	void Graphics::GenerateRenderBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glGenRenderbuffers(amount, buffers));
	}

	void Graphics::DeleteRenderBuffers(const unsigned int amount, unsigned int* buffers)
	{
		oglCheck(glDeleteRenderbuffers(amount, buffers));
	}

	void Graphics::SetRenderBufferStorage(const unsigned int x, const unsigned int y)
	{
		#ifdef UTH_SYSTEM_OPENGLES
			oglCheck(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, x, y));
		#else
			oglCheck(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, x, y));
		#endif
	}

	void Graphics::BindRenderBuffer(const unsigned int buffer)
	{
		oglCheck(glBindRenderbuffer(GL_RENDERBUFFER, buffer));
	}

	void Graphics::BindTextureToFrameBuffer(const unsigned int buffer, const unsigned int texture)
	{
		BindFrameBuffer(buffer);

		oglCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0));
	}

	void Graphics::BindRenderBufferToFrameBuffer(const unsigned int framebuffer, const unsigned int renderbuffer)
	{
		BindFrameBuffer(framebuffer);

		oglCheck(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer));
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Texture functions
		
	void Graphics::SetPixelStore(PixelStoreParam param, const int value)
	{
		oglCheck(glPixelStorei(pixelStoreParams[param], value));
	}

	void Graphics::GenerateTextures(const unsigned int amount, unsigned int* data)
	{
		oglCheck(glGenTextures(amount, data));
	}

	void Graphics::DeleteTextures(const unsigned int amount, unsigned int* data)
	{
		oglCheck(glDeleteTextures(amount, data));
	}

	void Graphics::SetActiveTexUnit(TexUnit unit)
	{
		oglCheck(glActiveTexture(textureUnits[unit]));
	}

	void Graphics::BindTexture(TextureType type, const int texture)
	{
		oglCheck(glBindTexture(textureTypes[type], texture));
	}
	/*
	void Graphics::setTextureImage1D(const int level, ImageFormat imageFormat, const unsigned int width, ImageFormat pixelFormat, DataType dataType, const void* pixels)
	{
		oglCheck(glTexImage1D(textureTypes[TEXTURE_1D], level, imageFormats[imageFormat], width, 0, imageFormats[pixelFormat], dataTypes[dataType], pixels));
	}
	*/
	void Graphics::SetTextureImage2D(TextureType type, const int level, ImageFormat imageFormat, const unsigned int width, const unsigned int height, ImageFormat pixelFormat, DataType dataType, const void* pixels)
	{
		oglCheck(glTexImage2D(textureTypes[type], level, imageFormats[imageFormat], width, height, 0, imageFormats[pixelFormat], dataTypes[dataType], pixels));
	}

	void Graphics::SetTextureParameter(TextureType type, TextureParam param, TextureFilter filter)
	{
		oglCheck(glTexParameteri(textureTypes[type], textureParams[param], textureFilters[filter]));
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Drawing functions
	void Graphics::DrawArrays(PrimitiveType type, const int first, const unsigned int count)
	{
		oglCheck(glDrawArrays(primitiveTypes[type], first, count));
	}

	void Graphics::DrawElements(PrimitiveType type, const unsigned int count, DataType dataType, const void* indices)
	{
		oglCheck(glDrawElements(primitiveTypes[type], count, dataTypes[dataType], indices));
	}
/*
	void Graphics::setPointSize(const float size)
	{
		oglCheck(glPointSize(size));
	}
*/
	void Graphics::SetLineWidth(const float width)
	{
		oglCheck(glLineWidth(width));
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Other
	void Graphics::Clear(const float r, const float g, const float b, const float a)
	{
		glClearColor(r, g, b, a);

		#ifdef UTH_SYSTEM_OPENGLES
			glClearDepthf(1.f);
		#else
			glClearDepth(1.f);
		#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::Flush()
	{
		oglCheck(glFlush());
	}

	void Graphics::SetDepthFunction(const bool enable, DepthFunction func)
	{
		static bool enabled = false;

		if (enable != enabled)
		{
			if (enable)
				oglCheck(glEnable(GL_DEPTH_TEST));
			else
				oglCheck(glDisable(GL_DEPTH_TEST));

			enabled = !enabled;
		}

		oglCheck(glDepthFunc(depthFunctions[func]));
	}

	void Graphics::SetBlendFunction(const bool enable, BlendFunction sfunc, BlendFunction dfunc)
	{
		static bool enabled = false;

		if (enable != enabled)
		{
			if (enable)
				oglCheck(glEnable(GL_BLEND));
			else
				oglCheck(glDisable(GL_BLEND));

			enabled = !enabled;
		}

		oglCheck(glBlendFunc(blendFunctions[sfunc], blendFunctions[dfunc]));
	}

	void Graphics::SetFaceCulling(const bool enable, FaceCulling mode)
	{
		static bool enabled = false;

		if (enable != enabled)
		{
			if (enable)
				oglCheck(glEnable(GL_CULL_FACE));
			else
				oglCheck(glDisable(GL_CULL_FACE));

			enabled = !enabled;
		}

		oglCheck(glCullFace(faceCullings[mode]));
	}

	void Graphics::SetViewport(const int x, const int y, const int width, const int height)
	{
		oglCheck(glViewport(x, y, width, height));
	}



	// Private

	Graphics::Graphics()
	{

	}

	Graphics::~Graphics()
	{

	}
}