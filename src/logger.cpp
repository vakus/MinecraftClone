#include "logger.hpp"
#include <iostream>
#include <string>
#include <ctime>

namespace Logger
{
    LogType min = INFO;
    LogType max = CRITICAL;

    /**
     * Sets minimum level of log
     * If min-log is set above max-log it will log a warning instead
     */
    void SetMinLog(LogType log)
    {
        if (log > max)
        {
            Warn("Attempting to set minimum log level above maximum log level.");
        }
        else
        {
            min = log;
        }
    }
    /**
     * Sets maximum level of log
     * If max-log is set below min-log it will log a warning instead
     */
    void SetMaxLog(LogType log)
    {
        if (log < min)
        {
            Warn("Attempting to set maximum log level below minimum log level.");
        }
        else
        {
            max = log;
        }
    }

    /**
     * if min log is lower or equal than FINER and max log is higher or equal than FINER, this will generate FINER log
     */
    void Finer(std::string message)
    {
        if (min <= LogType::FINER && LogType::FINER <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));

            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINER] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than FINE and max log is higher or equal than FINE, this will generate FINE log
     */
    void Fine(std::string message)
    {
        if (min <= LogType::FINE && LogType::FINE <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINE] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than INFO and max log is higher or equal than INFO, this will generate INFO log
     */
    void Info(std::string message)
    {
        if (min <= LogType::INFO && LogType::INFO <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [INFO] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than WARN and max log is higher or equal than WARN, this will generate WARN log
     */
    void Warn(std::string message)
    {
        if (min <= LogType::WARNING && LogType::WARNING<= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [WARN] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than ERROR and max log is higher or equal than ERROR, this will generate ERROR log
     */
    void Error(std::string message)
    {
        if (min <= LogType::ERROR && LogType::ERROR <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [ERROR] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than CRITICAL and max log is higher or equal than CRITICAL, this will generate CRITICAL log
     */
    void Critical(std::string message)
    {
        if (min <= LogType::CRITICAL && LogType::CRITICAL <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [CRITICAL] " << message << std::endl;
        }
    }

} // namespace Logger