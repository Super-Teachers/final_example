#ifndef PLAYERINTERFACE_HPP_L1M5P26M
#define PLAYERINTERFACE_HPP_L1M5P26M

#include <string>
#include <functional>

struct PlayerInterface {

    typedef std::function<void()> CallbackType;
    virtual ~PlayerInterface() {};

    virtual void play(const std::string& path) = 0;
    virtual void stop() = 0;
    virtual bool initialize() = 0;

    virtual void dispatch() = 0;
};


#endif /* end of include guard: PLAYERINTERFACE_HPP_L1M5P26M */
