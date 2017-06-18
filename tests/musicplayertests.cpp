#include <gtest/gtest.h>

#include "musicplayer.hpp"
#include "playermock.hpp"

using ::testing::StrictMock;

struct MusicPlayerTest : public ::testing::Test {
    StrictMock<PlayerMock> mock;
    MusicPlayer mp{mock};

    virtual void SetUp() { EXPECT_CALL(mock, initialize()); }
    virtual void TearDown() { EXPECT_CALL(mock, stop()); }
};

TEST_F(MusicPlayerTest, play_test) {
    EXPECT_CALL(mock, play(::testing::_));
    EXPECT_CALL(mock, dispatch()).Times(::testing::AtLeast(1));
    mp.play("this is not important right now");
}
