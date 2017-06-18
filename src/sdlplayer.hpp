#ifndef SDLPLAYER_HPP_AUKFV20D
#define SDLPLAYER_HPP_AUKFV20D

#include "playerinterface.hpp"

struct _Mix_Music;
struct SDLPlayer : public PlayerInterface {

    virtual bool initialize() override;
    virtual void play(const std::string& path) override;
    virtual void dispatch() override;
    virtual void stop() override;

    private:
    _Mix_Music *current { nullptr };
};


#endif /* end of include guard: SDLPLAYER_HPP_AUKFV20D */
