//
// Created by Rohan on 4/4/2020.
//

#ifndef UNTITLED1_LOGGER_H
#define UNTITLED1_LOGGER_H


#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <sstream>

/**
 * @author Rohan Talkad
 */
class Logger
{
public:
    enum class Level
    {
        DEBUG, INFO, WARN, ERROR
    };

    explicit Logger(std::string clz) : clazz(std::move(clz))
    {}

    void info(const std::string &msg)
    { log(Level::INFO, msg); }


    void info(const std::string &msg, const std::string &x)
    { log(Level::INFO, msg, x); }


    void info(const std::string &msg, int v)
    { log(Level::INFO, msg, to_string(v)); }


    void info(const std::string &msg, double v)
    { log(Level::INFO, msg, to_string(v)); }

    void info(const std::string &msg, const std::vector<std::string> v)
    { log(Level::INFO, msg, to_string(v)); }


    void debug(const std::string &msg)
    { log(Level::DEBUG, msg); }


    void warn(const std::string &msg)
    { log(Level::DEBUG, msg); }


    void error(const std::string &msg)
    { log(Level::ERROR, msg); }

    void error(const std::string &msg, const std::string &s)
    { log(Level::ERROR, msg, s); }

private:
    std::string clazz;

    void log(const Level level, const std::string &message, const std::string &o1 = "")
    {
        switch (level)
        {
            case (Level::DEBUG):
                std::cout << "[DEBUG]\t";
                break;
            case (Level::ERROR):
                std::cout << "[ERROR]\t";
                break;
            case (Level::INFO):
                std::cout << "[INFO]\t";
                break;
            case (Level::WARN):
                std::cout << "[WARN]\t";
                break;
            default:
                std::cout << "[NO Level]";
        }
        std::cout << clazz << " - " << message << o1 << std::endl;
    }

    static std::string to_string(int v)
    {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    }

    static std::string to_string(double v)
    {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    }

    static std::string to_string(std::vector<std::string> v)
    {
        std::ostringstream ss;
        for (std::string i : v)
        {
            ss << i << ",";
        }
        return ss.str();
    }
};


#endif //UNTITLED1_LOGGER_H
