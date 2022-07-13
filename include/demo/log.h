#ifndef DEMO_LOG_H__
#define DEMO_LOG_H__

#include <ostream>
#include <sstream>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // support for user defined types

#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace demo
{
    class Log
    {
    public:
        template<typename... Args>
        static inline void debug(spdlog::format_string_t<Args...> fmt, Args &&... args)
        {
            m_LogInner.debug(fmt, std::forward<Args&&>(args)...);
        }

        template <typename T>
        static inline void debug(const T &msg)
        {
            m_LogInner.debug(msg);
        }

    private:
        class InnerLog
        {
        public:
            InnerLog()
            {
                spdlog::set_level(spdlog::level::trace);
            }

            ~InnerLog() {}

            template<typename... Args>
            inline void debug(spdlog::format_string_t<Args...> fmt, Args &&... args)
            {
                spdlog::debug(fmt, std::forward<Args>(args)...);
            }

            template<typename T>
            inline void debug(const T &msg)
            {
                spdlog::debug(msg);
            }
        };

        static InnerLog m_LogInner;
    };

    std::ostream & operator<<(std::ostream& o, const glm::mat4 & m);
    std::ostream & operator<<(std::ostream& o, const glm::vec3 & v);
}

template<>
struct spdlog::fmt_lib::formatter<glm::mat4> : spdlog::fmt_lib::formatter<std::string>
{
    auto format(const glm::mat4 &m, format_context &ctx) -> decltype(ctx.out())
    {
        std::stringstream ss;
        demo::operator<<(ss, m);
        return spdlog::fmt_lib::format_to(ctx.out(), "{}", ss.str());
    }
};

template<>
struct spdlog::fmt_lib::formatter<glm::vec3> : spdlog::fmt_lib::formatter<std::string>
{
    auto format(const glm::vec3 &v, format_context &ctx) -> decltype(ctx.out())
    {
        std::stringstream ss;
        demo::operator<<(ss, v);
        return spdlog::fmt_lib::format_to(ctx.out(), "{}", ss.str());
    }
};

#endif 