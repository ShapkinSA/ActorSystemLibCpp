//
// Created by user on 21.02.24.
//

#ifndef ACTORSYSTEM_LOGGER_H
#define ACTORSYSTEM_LOGGER_H

#include <log4cpp/Appender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include "log4cpp/PropertyConfigurator.hh"
#include "libs/fmt/include/fmt/format.h"


#define log_info(...) (Logger::getLogger().info(Logger::stringFromFormat(__VA_ARGS__)))
#define log_debug(...) (Logger::getLogger().debug(Logger::stringFromFormat(__VA_ARGS__)))
#define log_warn(...) (Logger::getLogger().warn(Logger::stringFromFormat(__VA_ARGS__)))
#define log_error(...) (Logger::getLogger().error(Logger::stringFromFormat(__VA_ARGS__)))
#define setLoggerConfiguration(path) (Logger::setLoggerProperties(path))

class Logger {
public:
    static void setLoggerProperties(const std::string& pathToFile) {
        log4cpp::PropertyConfigurator::configure(pathToFile);
        logger = &log4cpp::Category::getRoot();
    }

    template <typename... Args>
    static std::string stringFromFormat(fmt::format_string<Args...> s, Args&&... args) {
        return fmt::format(s, std::forward<Args>(args)...);
    }

    static log4cpp::Category &getLogger() {
        return *logger;
    }


private:
    inline static log4cpp::Category *logger;
};

#endif //ACTORSYSTEM_LOGGER_H
