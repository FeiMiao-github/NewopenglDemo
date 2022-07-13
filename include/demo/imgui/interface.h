#ifndef DEMO_IMGUI_INTERFACE_H__
#define DEMO_IMGUI_INTERFACE_H__

#include "demo/coordination.h"
namespace demo
{
    namespace imgui
    {
        class IDrawImp
        {
        public:
            IDrawImp() {}
            virtual ~IDrawImp() = default;
            virtual void Draw() = 0;
        };
    }
}

#endif // DEMO_IMGUI_INTERFACE_H__