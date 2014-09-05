#include <UtH/Platform/Linux/LinuxWindowImpl.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <iostream>
#include <cstdlib>



namespace
{
    static unsigned int windowRefs = 0;
    static bool initialized = false;

    void manageWindowRefs()
    {
        if (windowRefs == 0)
        {
            glfwTerminate();
            initialized = false;
        }    
    }

    void ensureGLFWInit()
    {
        if (!initialized)
        {
            if (!glfwInit())
                std::exit(EXIT_FAILURE);

            initialized = true;
        }
    }
}


namespace uth
{

    void* LinuxWindowImpl::create(const WindowSettings& settings)
    {
        ensureGLFWInit();

        GLFWwindow* wndwHandle;

        glfwWindowHint(GLFW_ALPHA_BITS, settings.useBlending ? 8 : 0);
        glfwWindowHint(GLFW_DEPTH_BITS, settings.useDepthBuffer ? 16 : 0);
        glfwWindowHint(GLFW_STENCIL_BITS, settings.useStencilBuffer ? 8 : 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

        int majorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMajor,
            minorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMinor;

        do
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);

            wndwHandle = glfwCreateWindow(settings.size.w, settings.size.h, settings.title.c_str(), settings.fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);

            if (--minorVer < 0)
            {
                --majorVer;
                minorVer = 9;
            }

        } while (!wndwHandle && majorVer > 0);


        if (!wndwHandle)
        {
            std::cout << "Failed to create an OpenGL context! Exiting..." <<std::endl;
            std::exit(EXIT_FAILURE);
        }

        ++windowRefs;
        glfwMakeContextCurrent(wndwHandle);

        glfwSetWindowPos(wndwHandle, settings.position.x, settings.position.y);
        glfwSwapInterval(settings.useVsync ? 1 : 0);

		std::cout << "glew init might produces GL_INVALID_ENUM error. Just ignore it" << std::endl;
		glewExperimental = GL_TRUE;
        oglCheck(glewInit());
        
        if(majorVer >= 3)
        {
            GLuint vertexArray;
            glGenVertexArrays(1, &vertexArray);
            glBindVertexArray(vertexArray);
        }


        return static_cast<void*>(wndwHandle);
    }


    void* LinuxWindowImpl::destroy(void* handle)
    {
        if (!handle) return handle;

        glfwDestroyWindow(static_cast<GLFWwindow*>(handle));

        handle = NULL;

        --windowRefs;
        manageWindowRefs();

        return handle;
    }


    void LinuxWindowImpl::clear(const bool clearDepth, const bool clearStencil, const float r, const float g, const float b, const float a)
    {
        oglCheck(glClear(GL_COLOR_BUFFER_BIT |
                         GL_DEPTH_BUFFER_BIT |
                         GL_STENCIL_BUFFER_BIT));
		oglCheck(glClearColor(r, g, b, a));

        if (!clearDepth) return;
			
        oglCheck(glClearDepth(1));

        if (!clearStencil) return;

        oglCheck(glClearStencil(1));
    }

    void LinuxWindowImpl::swapBuffers(void* handle)
    {
        if (!handle) return;

        glfwSwapBuffers(static_cast<GLFWwindow*>(handle));
    }
	
	bool LinuxWindowImpl::processMessages(void* handle)
	{
		if (!handle) return false;

		glfwPollEvents();

		return glfwWindowShouldClose(static_cast<GLFWwindow*>(handle));
	}
}