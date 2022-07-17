#include "demo/context.h"
#include "demo/coordination.h"
#include "demo/lighting.h"
#include "demo/log.h"

using namespace demo;

std::unique_ptr<Context> Context::s_Inst = std::unique_ptr<Context>(new Context);

std::unique_ptr<Context>& Context::Inst()
{
    return s_Inst;
}

const char* ContextNoLightingEx::what() const noexcept
{
    return "light is nullptr !";
}

Context::Context()
    : m_View(new ViewCoordination),
      m_Proj(
        new ProjectionCoordination(
            ProjectionCoordination::PerspectiveConfig{
                .Fov = glm::radians(45.0f),
                .Aspect = 1.0f,
                .Near = 0.1f,
                .Far = 100.0f
            }
        )
      ),
      m_Light(nullptr)
{
    InitView();
}

Context::~Context()
{
    delete m_Proj;
    m_Proj = nullptr;

    delete m_View;
    m_View = nullptr;
}

void Context::InitView()
{
    m_View->MoveTo(glm::vec3(0.0f, 0.0f, -3.0f));
    Log::debug("Context View", m_View->Value());
}

const ViewCoordination* Context::View() const
{
    return m_View;
}

const ProjectionCoordination* Context::Proj() const
{
    return m_Proj;
}

const Lighting& Context::GetLight() const
{
    if (m_Light == nullptr)
        throw ContextNoLightingEx();
    return *m_Light;
}

void Context::SetLight(const Lighting * light)
{
    m_Light = light;
}

const glm::vec3 Context::ViewPos() const
{
    return glm::vec3(0.0f);
}

void Context::Update()
{
}
