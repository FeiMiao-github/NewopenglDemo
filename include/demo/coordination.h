#ifndef DEMO_COORDINATION_H__
#define DEMO_COORDINATION_H__

#include "glm/ext/matrix_clip_space.hpp"
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo
{
    class Coordination
    {
    public:
        Coordination();
        virtual ~Coordination() {}
        
        [[deprecated]]
        virtual void Rotate(const float angle, const glm::vec3& axis);
        virtual void RotateTo(const glm::vec3& angle);
        [[deprecated]]
        virtual void Move(const glm::vec3& axis);
        virtual void MoveTo(const glm::vec3& dist);
        [[deprecated]]
        virtual void Scale(const glm::vec3& ratio);
        virtual void ScaleTo(const glm::vec3& ratio);

        const glm::mat4 &Value() const
        {
            return m_Mat4;
        }

        const static glm::vec3 RIGHT;
        const static glm::vec3 UP;
        const static glm::vec3 FORWARD;

    protected:
        virtual void UpdateMat4();
    
    protected:
        glm::mat4 m_Transform;
        glm::mat4 m_Rotate;
        glm::mat4 m_Scale;

        glm::mat4 m_Mat4;
    };

    class ViewCoordination
        : public Coordination
    {
    public:
        ViewCoordination() {}
        ~ViewCoordination() {}
    };

    class ProjectionCoordination
        : public Coordination
    {
    public:
        struct OrthoConfig
        {
            double Left;
            double Right;
            double Bottom;
            double Top;
            double Near;
            double Far;
        };

        struct PerspectiveConfig
        {
            double Fov;
            double Aspect;
            double Near;
            double Far;
        };

        explicit ProjectionCoordination(const OrthoConfig& config);
        explicit ProjectionCoordination(const PerspectiveConfig& config);

        ~ProjectionCoordination() {}
    };
}
#endif // DEMO_COORDINATION_H__