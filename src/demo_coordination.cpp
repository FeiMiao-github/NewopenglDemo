#include "demo/coordination.h"

using namespace demo;

void Coordination::Rotate(const float angle, const glm::vec3& axis)
{
    m_Mat4 = glm::rotate(m_Mat4, angle, axis);
}

void Coordination::Move(const glm::vec3& dist)
{
    m_Mat4 = glm::translate(m_Mat4, dist);
}

void Coordination::Scale(const glm::vec3& ratio)
{
    m_Mat4 = glm::scale(m_Mat4, ratio);
}
