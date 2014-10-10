#include "UtH/Engine/Engine.hpp"


#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Input.hpp>

using namespace uth;

Engine::Engine()
    : m_running(false)
{ }

bool Engine::Init(const uth::WindowSettings &wsettings)
{
	m_wsettings = wsettings;
	return initialize();
}

void Engine::Update()
{
	const float deltaTime = static_cast<float>(m_timer.DeltaTime());
	uthInput.Update(deltaTime);
	uthSceneM.Update(deltaTime);
	if(m_wndw->processMessages())
	{
		Exit();
	}
}

void Engine::Draw()
{
	m_wndw->Clear(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	uthSceneM.Draw();
    m_wndw->swapBuffers();
}

void Engine::Exit()
{
	m_running = false;
}

void Engine::SetClearColor(const pmath::Vec4& color)
{
    m_clearColor = color;
}

void Engine::SetClearColor(float r, float g, float b, float a)
{
    SetClearColor(pmath::Vec4(r, g, b, a));
}

Window& Engine::GetWindow()
{
    return *m_wndw;
}

bool Engine::initialize()
{
	m_wndw = new Window(m_wsettings);
	uth::Graphics::SetBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);
	uthInput.SetWindow(m_wndw->m_windowHandle);
    m_wndw->SetViewport(pmath::Rect(0, 0, m_wsettings.size.x, m_wsettings.size.y));
	m_running = true;

	return true;
}

const Timer& Engine::Timer() const
{
	return m_timer;
}

const pmath::Vec2 Engine::GetWindowResolution() const
{
	return m_wsettings.size;
}

const bool Engine::Running() const
{
	return m_running;
}

void Engine::SetWindow(void* handle)
{
	m_wndw = (Window*)handle;
}