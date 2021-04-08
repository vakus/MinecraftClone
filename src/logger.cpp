#include "logger.hpp"
#include <iostream>
#include <string>
#include <ctime>

namespace logger
{
    logtype min = INFO;
    logtype max = CRITICAL;

    /**
     * Sets minimum level of log
     * If min-log is set above max-log it will log a warning instead
     */
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
    /**
     * Sets maximum level of log
     * If max-log is set below min-log it will log a warning instead
     */
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

    /**
     * if min log is lower or equal than FINER and max log is higher or equal than FINER, this will generate FINER log
     */
    void finer(std::string message)
    {
        if (min <= logtype::FINER && logtype::FINER <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));

            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINER] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than FINE and max log is higher or equal than FINE, this will generate FINE log
     */
    void fine(std::string message)
    {
        if (min <= logtype::FINE && logtype::FINE <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [FINE] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than INFO and max log is higher or equal than INFO, this will generate INFO log
     */
    void info(std::string message)
    {
        if (min <= logtype::INFO && logtype::INFO <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [INFO] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than WARN and max log is higher or equal than WARN, this will generate WARN log
     */
    void warn(std::string message)
    {
        if (min <= logtype::WARNING && logtype::WARNING<= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [WARN] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than ERROR and max log is higher or equal than ERROR, this will generate ERROR log
     */
    void error(std::string message)
    {
        if (min <= logtype::ERROR && logtype::ERROR <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [ERROR] " << message << std::endl;
        }
    }

    /**
     * if min log is lower or equal than CRITICAL and max log is higher or equal than CRITICAL, this will generate CRITICAL log
     */
    void critical(std::string message)
    {
        if (min <= logtype::CRITICAL && logtype::CRITICAL <= max)
        {
            const std::time_t now = std::time(nullptr);

            const std::tm cnow = *std::localtime(std::addressof(now));
            std::cout << "[" << cnow.tm_hour << ":" << cnow.tm_min << ":" << cnow.tm_sec << "] [CRITICAL] " << message << std::endl;
        }
    }

} // namespace logger