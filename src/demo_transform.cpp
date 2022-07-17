#include <glm/ext/matrix_transform.hpp>

#include "demo/transform.h"
#include "demo/log.h"

using namespace demo;

const glm::vec3 Transform::RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Transform::FORWARD = glm::vec3(0.0f, 0.0f, 1.0f);

Transform::Transform(const glm::vec3 &pos,const glm::vec3 &rotation,const glm::vec3 &scale)
    : m_Pos(pos),
      m_Rotation(rotation),
      m_Scale(scale),
      m_MoveMat4(1.0f),
      m_RotateMat4(1.0f),
      m_ScaleMat4(1.0f)
{
    m_MoveMat4 = glm::translate(m_MoveMat4, pos);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.x, Transform::RIGHT);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.y, Transform::UP);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.z, Transform::FORWARD);
    m_ScaleMat4 = glm::scale(m_ScaleMat4, scale);
    UpdateMat4();
}

Transform::~Transform()
{
}

void Transform::SetPos(const glm::vec3& pos)
{
    m_Pos = pos;
    m_MoveMat4 = glm::mat4(1.0f);
    m_MoveMat4 = glm::translate(m_MoveMat4, pos);
    UpdateMat4();
}

void Transform::SetRotation(const glm::vec3& rotation)
{
    m_Rotation = rotation;
    m_RotateMat4 = glm::mat4(1.0f);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.x, Transform::RIGHT);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.y, Transform::UP);
    m_RotateMat4 = glm::rotate(m_RotateMat4, rotation.z, Transform::FORWARD);
    UpdateMat4();
}

void Transform::SetScale(const glm::vec3& scale)
{
    m_Scale = scale;
    m_ScaleMat4 = glm::mat4(1.0f);
    m_ScaleMat4 = glm::scale(m_ScaleMat4, scale);
    UpdateMat4();
}

const glm::vec3 Transform::Pos() const
{
    return m_Pos;
}

const glm::vec3 Transform::Rotation() const
{
    return m_Rotation;
}

const glm::vec3 Transform::Scale() const
{
    return m_Scale;
}

const glm::mat4 Transform::Mat4() const
{
    return m_Mat4;
}

void Transform::UpdateMat4()
{
    m_Mat4 = m_MoveMat4 * m_RotateMat4 * m_ScaleMat4;
}

imgui::TransformUI::TransformUI(Transform& transform)
    : m_Transform(transform),
      m_PositionPublisher(new PositionPublisher("Position", m_Transform.Pos())),
      m_RotationPublisher(new RotationPublisher("Rotation", m_Transform.Rotation())),
      m_ScalePublisher(new ScalePublisher("Scale", m_Transform.Scale()))
{
    m_PositionPublisher->AddSubscriber(this);
    m_RotationPublisher->AddSubscriber(this);
    m_ScalePublisher->AddSubscriber(this);
}

imgui::TransformUI::~TransformUI()
{
    m_PositionPublisher->RemoveSubscriber(this);
    delete m_PositionPublisher;
    m_PositionPublisher = nullptr;

    m_RotationPublisher->RemoveSubscriber(this);
    delete m_RotationPublisher;
    m_RotationPublisher = nullptr;

    m_ScalePublisher->RemoveSubscriber(this);
    delete m_ScalePublisher;
    m_ScalePublisher = nullptr;
}

void imgui::TransformUI::Update(PositionPublisher*, const PositionSubscriber::Type& pos)
{
    Log::debug("update pos: ", pos);
    m_Transform.SetPos(pos);
}

void imgui::TransformUI::Update(RotationPublisher*, const RotationSubscriber::Type& rotation)
{
    Log::debug("update rotation: ", rotation);
    m_Transform.SetRotation(rotation);
}

void imgui::TransformUI::Update(ScalePublisher*, const ScaleSubscriber::Type& scale)
{
    Log::debug("update rotation: ", scale);
    m_Transform.SetScale(scale);
}

void imgui::TransformUI::Draw()
{
    m_PositionPublisher->Draw();
    m_RotationPublisher->Draw();
    m_ScalePublisher->Draw();
}