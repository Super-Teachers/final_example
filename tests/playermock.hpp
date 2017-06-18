#ifndef PLAYERMOCK_HPP_FPEWSD05
#define PLAYERMOCK_HPP_FPEWSD05

#include <gmock/gmock.h>
#include "playerinterface.hpp"

struct PlayerMock : public PlayerInterface {
    MOCK_METHOD1(play, void(const std::string&));
    MOCK_METHOD0(stop, void());
    MOCK_METHOD0(initialize, bool());
    MOCK_METHOD0(dispatch, void());
};

#endif /* end of include guard: PLAYERMOCK_HPP_FPEWSD05 */
