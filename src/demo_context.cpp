#include "demo/context.h"
#include "demo/coordination.h"

using namespace demo;

Context::Context()
    : m_View(new ViewCoordination),
      m_Proj(new ProjectionCoordination),
      m_LightColor(glm::vec3(1.0f))
{
}

Context::~Context()
{
}

const ViewCoordination* Context::View() const
{
    return m_View;
}

const ProjectionCoordination* Context::Proj() const
{
    return m_Proj;
}

const glm::vec3& Context::LightColor() const
{
    return m_LightColor;
}