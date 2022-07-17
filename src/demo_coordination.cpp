#include "demo/coordination.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace demo;

const glm::vec3 Coordination::RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Coordination::UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Coordination::FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);

Coordination::Coordination()
    : m_Transform(1.0f),
      m_Rotate(1.0f),
      m_Scale(1.0f),
      m_Mat4(1.0f)
{
}

void Coordination::Rotate(const float, const glm::vec3&)
{
    // m_Mat4 = glm::rotate(m_Mat4, angle, axis);
}

void Coordination::RotateTo(const glm::vec3& angle)
{
    m_Rotate = glm::mat4(1.0f);
    m_Rotate = glm::rotate(m_Rotate, angle[0], RIGHT);
    m_Rotate = glm::rotate(m_Rotate, angle[1], UP);
    m_Rotate = glm::rotate(m_Rotate, angle[2], FORWARD);
    UpdateMat4();
}

void Coordination::Move(const glm::vec3&)
{
    // m_Mat4 = glm::translate(m_Mat4, dist);
}

void Coordination::MoveTo(const glm::vec3& dist)
{
    m_Transform = glm::mat4(1.0f);
    m_Transform = glm::translate(m_Transform, dist);
    UpdateMat4();
}

void Coordination::Scale(const glm::vec3& ratio)
{
    m_Mat4 = glm::scale(m_Mat4, ratio);
}

void Coordination::ScaleTo(const glm::vec3& ratio)
{
    m_Scale = glm::mat4(1.0f);
    m_Scale = glm::scale(m_Scale, ratio);
    UpdateMat4();
}

void Coordination::UpdateMat4()
{
    m_Mat4 = m_Transform * m_Rotate * m_Scale;
}

ProjectionCoordination::ProjectionCoordination(const PerspectiveConfig& config)
{
    m_Mat4 = glm::perspective(config.Fov, config.Aspect, config.Near, config.Far);
}

ProjectionCoordination::ProjectionCoordination(const OrthoConfig& config)
{
    m_Mat4 = glm::ortho(config.Left, config.Right, config.Bottom, config.Top, config.Near, config.Far);
}