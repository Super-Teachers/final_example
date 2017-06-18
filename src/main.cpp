
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <thread>
#include <vector>

#include "musicplayer.hpp"
#include "sdlplayer.hpp"
#include "log.hpp"

int main(int argc, char *argv[]) {
    const std::vector<std::string> arguments{argv, argv + argc};

    SDLPlayer sdl;
    MusicPlayer player{sdl};

    if (arguments.size() != 2) {
        LOG("Aguments size is not correct");
        return 1;
    }

    const std::string file = arguments[1];
    std::string command;
    bool running = true;
    std::thread musicThread;

    // clang-format off
     const std::map<std::string, std::function<void()>> actions{
        {"quit", [&running]() { running = false; }},
        {"start", [&player, &file]() { player.play(file); }}
    };

    // clang-format on

    std::cout << "enter command " << std::endl;
    while (running) {
        std::cin >> command;
        LOG("Command = " << command);

        const auto commandIt = actions.find(command);

        if (commandIt == actions.end()) {
            LOG("Unable to find action " << command);
            continue;
        }

        commandIt->second();
    }

    LOG("Exiting");
    return 0;
}
