#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logger
{

    enum LogType
    {
        FINER,    //all information
        FINE,     //most information
        INFO,     //basic information
        WARNING,  //warnings
        ERROR,    //errors
        CRITICAL, //unrecoverable errors
        NONE      //nothing
    };

    /**
     * Sets minimum log level to be reported
     */
    void SetMinLog(LogType log);
    /**
     * Sets maximum log level to be reported
     */
    void SetMaxLog(LogType log);

    /**
     * Reports FINER log
     */
    void Finer(std::string message);

    /**
     * Reports FINE log
     */
    void Fine(std::string message);
    
    /**
     * Reports INFO log
     */
    void Info(std::string message);

    /**
     * Reports WARN log
     */
    void Warn(std::string message);

    /**
     * Reports ERROR log
     */
    void Error(std::string message);

    /**
     * Reports CRITICAL log
     */
    void Critical(std::string message);

} // namespace Logger

#endif