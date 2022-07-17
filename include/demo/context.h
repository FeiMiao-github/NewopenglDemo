#ifndef DEMO_CONTEXT_H__
#define DEMO_CONTEXT_H__

#include <exception>
#include <memory>

#include "glm/ext/vector_float3.hpp"

#include "demo/coordination.h"
#include "demo/lighting.h"

namespace demo
{
    class ContextException :
        public std::exception
    {
    public:
        ContextException() {}
        virtual ~ContextException() {}
        const char* what() const noexcept = 0;
    };

    class ContextNoLightingEx :
        public ContextException
    {
    public:
        ContextNoLightingEx() {}
        virtual ~ContextNoLightingEx() {}
        const char* what() const noexcept override;
    };

    class Context
    {
    public:
        static std::unique_ptr<Context>& Inst();

    private:
        Context();

    public:
        virtual ~Context();

    private:
        void InitView();

    public:
        const ViewCoordination* View() const;
        const ProjectionCoordination* Proj() const;

        void Update();

        const Lighting& GetLight() const;
        void SetLight(const Lighting* light);

        const glm::vec3 ViewPos() const;

    private:
        static std::unique_ptr<Context> s_Inst;        

        ViewCoordination* m_View;
        ProjectionCoordination* m_Proj;
        const Lighting* m_Light;
    };
};

#endif