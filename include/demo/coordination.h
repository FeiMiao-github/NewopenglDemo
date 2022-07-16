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
        Coordination()
            : m_Mat4(1.0f)
        {
        }

        virtual ~Coordination() {}
        virtual void Rotate(const float angle, const glm::vec3& axis);
        virtual void Move(const glm::vec3& axis);
        virtual void MoveTo(const glm::vec3& dist);
        virtual void Scale(const glm::vec3& ratio);

        const glm::mat4 &Value() const
        {
            return m_Mat4;
        }
    
    protected:
        glm::mat4 m_Mat4;
    };

    class LocalCoordination
        : public Coordination
    {
    public:
        LocalCoordination() {}
        ~LocalCoordination() {}
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

        ProjectionCoordination(const OrthoConfig& config);
        ProjectionCoordination(const PerspectiveConfig& config);

        ~ProjectionCoordination() {}
    };
}
#endif // DEMO_COORDINATION_H__