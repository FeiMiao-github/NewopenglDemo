#include "demo/coordination.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace demo;

void Coordination::Rotate(const float angle, const glm::vec3& axis)
{
    m_Mat4 = glm::rotate(m_Mat4, angle, axis);
}

void Coordination::Move(const glm::vec3& dist)
{
    m_Mat4 = glm::translate(m_Mat4, dist);
}

void Coordination::MoveTo(const glm::vec3& dist)
{
    m_Mat4 = glm::mat4(1.0f);
    Move(dist);
}

void Coordination::Scale(const glm::vec3& ratio)
{
    m_Mat4 = glm::scale(m_Mat4, ratio);
}

ProjectionCoordination::ProjectionCoordination(const PerspectiveConfig& config)
{
    m_Mat4 = glm::perspective(config.Fov, config.Aspect, config.Near, config.Far);
}

ProjectionCoordination::ProjectionCoordination(const OrthoConfig& config)
{
    m_Mat4 = glm::ortho(config.Left, config.Right, config.Bottom, config.Top, config.Near, config.Far);
}