#ifndef DEMO_TRANSFORM_H__
#define DEMO_TRANSFORM_H__

#include <glm/matrix.hpp>

#include "demo/imgui.h"

namespace demo
{
    class Transform
    {
    public:
        Transform(
            const glm::vec3 &pos = glm::vec3(0.0f),
            const glm::vec3 &rotation = glm::vec3(0.0f),
            const glm::vec3 &scale = glm::vec3(1.0f)
        );
        virtual ~Transform();

        virtual void SetPos(const glm::vec3& pos);
        virtual void SetRotation(const glm::vec3& rotation);
        virtual void SetScale(const glm::vec3& scale);

        virtual const glm::vec3 Pos() const;
        virtual const glm::vec3 Rotation() const;
        virtual const glm::vec3 Scale() const;

        virtual const glm::mat4 Mat4() const;

    protected:
        virtual void UpdateMat4();

    public:
        const static glm::vec3 RIGHT;
        const static glm::vec3 UP;
        const static glm::vec3 FORWARD;

    protected:
        glm::vec3 m_Pos;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;

        glm::mat4 m_MoveMat4;
        glm::mat4 m_RotateMat4;
        glm::mat4 m_ScaleMat4;

        glm::mat4 m_Mat4;
    };

    namespace imgui
    {
        class TransformUI:
            public IDrawImp,
            public PositionSubscriber,
            public RotationSubscriber,
            public ScaleSubscriber
        {
        public:
            explicit TransformUI(Transform& transform);
            virtual ~TransformUI();

            virtual void Update(PositionPublisher*, const PositionSubscriber::Type& pos) override;
            virtual void Update(RotationPublisher*, const RotationSubscriber::Type& rotation) override;
            virtual void Update(ScalePublisher*, const ScaleSubscriber::Type& scale) override;
            virtual void Draw() override;
        
        private:
            Transform& m_Transform;
            PositionPublisher* m_PositionPublisher;
            RotationPublisher* m_RotationPublisher;
            ScalePublisher* m_ScalePublisher;
        };
    };
}

#endif