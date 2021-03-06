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

    void setMinLog(logtype log);
    void setMaxLog(logtype log);

    #ifdef PROFILE
    void setProfiling(bool profiling);
    #endif

    void finer(std::string message);
    void fine(std::string message);
    void info(std::string message);
    void warn(std::string message);
    void error(std::string message);
    void critical(std::string message);

    #ifdef PROFILE
    void profile(std::string message);
    #endif

} // namespace logger

#endif