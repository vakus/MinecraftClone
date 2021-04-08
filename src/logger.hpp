#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace logger
{

    enum logtype
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
    void setMinLog(logtype log);
    /**
     * Sets maximum log level to be reported
     */
    void setMaxLog(logtype log);

    /**
     * Reports FINER log
     */
    void finer(std::string message);

    /**
     * Reports FINE log
     */
    void fine(std::string message);
    
    /**
     * Reports INFO log
     */
    void info(std::string message);

    /**
     * Reports WARN log
     */
    void warn(std::string message);

    /**
     * Reports ERROR log
     */
    void error(std::string message);

    /**
     * Reports CRITICAL log
     */
    void critical(std::string message);

} // namespace logger

#endif