#include "logger.hpp"
#include <iostream>
#include <string>
#include <ctime>

namespace logger
{
    logtype min = INFO;
    logtype max = CRITICAL;
    bool profiling = false;

    void setMinLog(logtype log)
    {
        if (log > max)
        {
            warn("Attempting to set minimum log level above maximum log level.");
        }
        else
        {
            min = log;
        }
    }

    void setMaxLog(logtype log)
    {
        if (log < min)
        {
            warn("Attempting to set maximum log level below minimum log level.");
        }
        else
        {
            max = log;
        }
    }

    void setProfiling(bool prof){
        profiling = prof;
    }

    void finer(std::string message)
    {
        if (min <= logtype::FINER && logtype::FINER <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));

            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINER] " << message << std::endl;
        }
    }

    void fine(std::string message)
    {
        if (min <= logtype::FINE && logtype::FINE <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINE] " << message << std::endl;
        }
    }

    void info(std::string message)
    {
        if (min <= logtype::INFO && logtype::INFO <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [INFO] " << message << std::endl;
        }
    }

    void warn(std::string message)
    {
        if (min <= logtype::WARNING && logtype::WARNING<= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [WARN] " << message << std::endl;
        }
    }

    void error(std::string message)
    {
        if (min <= logtype::ERROR && logtype::ERROR <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [ERROR] " << message << std::endl;
        }
    }

    void critical(std::string message)
    {
        if (min <= logtype::CRITICAL && logtype::CRITICAL <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [CRITICAL] " << message << std::endl;
        }
    }

    void profile(std::string message){
        if(profiling){
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [PROFILE] " << message << std::endl;
        }
    }

} // namespace logger