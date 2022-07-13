#ifndef DEMO_COORDINATION_H__
#define DEMO_COORDINATION_H__

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
        virtual void Scale(const glm::vec3& ratio);

        glm::mat4 &Value()
        {
            return m_Mat4;
        }

    private:
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
        ProjectionCoordination() {}
        ~ProjectionCoordination() {}
    };
}
#endif // DEMO_COORDINATION_H__