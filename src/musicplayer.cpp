#include "musicplayer.hpp"
#include "log.hpp"
#include "playerinterface.hpp"

#include <deque>

namespace {}

void playback_thread(const bool& running, PlayerInterface& player,
                     MusicPlayer::DequeType& deque) {
    LOG("Staring playback thread");

    while (running) {
        if (!deque.empty()) {
            auto command = deque.front();
            deque.pop_front();

            if (command.first == MusicPlayer::Commands::Initialize) {
                LOG("Initialize player");
                player.initialize();
            }

            if (command.first == MusicPlayer::Commands::Play) {
                player.play(command.second);
            }
            if (command.first == MusicPlayer::Commands::Stop) {
                player.stop();
                break;
            }
        } else {
            player.dispatch();
        }
    }
}

MusicPlayer::MusicPlayer(PlayerInterface& player)
    : _player(player), _running(true),
      _musicThread(playback_thread, std::cref(_running), std::ref(_player),
                   std::ref(_commandsQueue)) {
    _commandsQueue.push_back(std::make_pair(Commands::Initialize, ""));
}

MusicPlayer::~MusicPlayer() {
    LOG("~MusicPlayer");

    _commandsQueue.push_back(std::make_pair(Commands::Stop, ""));

    if (_musicThread.joinable())
        _musicThread.join();
}

void MusicPlayer::play(const std::string& song) {
    _commandsQueue.push_back(std::make_pair(Commands::Play, song));
}
