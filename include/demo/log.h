#ifndef DEMO_LOG_H__
#define DEMO_LOG_H__

#include <ostream>
#include <iostream>

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <loguru/loguru.hpp>

namespace demo
{
    class Log
    {
    public:
        template<typename Next, typename... Args>
        static inline void debug(const Next & next, Args &&... args)
        {
            LOG_S(INFO) << next;
            debug(std::forward<Args&&>(args)...);
        }

        template <typename Last>
        static inline void debug(const Last &last)
        {
            LOG_S(INFO) << last;
        }

    private:
        class InitConfig {
        public:
            InitConfig()
            {
                loguru::g_preamble_file = false;
                loguru::g_preamble_uptime = false;
                loguru::g_preamble_thread = false;
            }

            ~InitConfig()
            {
            }
        };

        const static InitConfig s_InitConfig; 
    };

    ::std::ostream & operator<<(::std::ostream& o, const glm::mat4 & m);
    ::std::ostream & operator<<(::std::ostream& o, const glm::vec4 & v);
    ::std::ostream & operator<<(::std::ostream& o, const glm::vec3 & v);
}

#endif 