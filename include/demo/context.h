#ifndef DEMO_CONTEXT_H__
#define DEMO_CONTEXT_H__

#include "demo/coordination.h"

namespace demo
{
    class Context
    {
    public:
        Context();
        virtual ~Context();

        const ViewCoordination* View() const;
        const ProjectionCoordination* Proj() const;
        const glm::vec3& LightColor() const;

    private:
        ViewCoordination* m_View;
        ProjectionCoordination* m_Proj;
        glm::vec3 m_LightColor;
    };
};

#endif