#ifndef MUSICPLAYER_HPP_45OMNCUM
#define MUSICPLAYER_HPP_45OMNCUM

#include <deque>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class PlayerInterface;
struct MusicPlayer {
   public:
    enum Commands { Initialize = 0, Play, Stop };
    typedef std::deque<std::pair<Commands, std::string> > DequeType;

    MusicPlayer(PlayerInterface& player);
    ~MusicPlayer();

    void play(const std::string& song);
    void play(const std::vector<std::string>& songs);

   private:
    PlayerInterface& _player;
    bool _running;
    std::thread _musicThread;

    DequeType _commandsQueue;
};

#endif /* end of include guard: MUSICPLAYER_HPP_45OMNCUM */
