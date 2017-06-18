#include "sdlplayer.hpp"
#include "log.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace {
bool musicPlaying = false;
}

bool SDLPlayer::initialize() {
    LOG("SDLPlayer::initialize");
    int result = 0;
    int flags = MIX_INIT_MP3 & MIX_INIT_OGG;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        LOG("Failed to init SDL");
        return false;
    }

    if (flags != (result = Mix_Init(flags))) {
        LOG("Could not initialize mixer (result: " << result << ") error = "
                                                   << Mix_GetError());
        return false;
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

    Mix_HookMusicFinished([]() { LOG("Music finished"); });
}

void SDLPlayer::play(const std::string &path) {
    LOG("SDLPlayer::play " << path);
    current = Mix_LoadMUS(path.c_str());
    LOG("Music ptr " << static_cast<void *>(current));
    if (current == nullptr) {
        return;
    }
    LOG("Playing music");
    Mix_PlayMusic(current, 1);
}

void SDLPlayer::dispatch() { 
    SDL_Delay(250);

    bool isPlaying = Mix_PlayingMusic() == 1;
}

void SDLPlayer::stop() {
    LOG("Stop playing music");
    Mix_HaltMusic();
    if (current) Mix_FreeMusic(current);
    LOG("Freeying music");
    SDL_Quit();
}
