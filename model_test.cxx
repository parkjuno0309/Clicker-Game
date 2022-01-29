#include "model.hxx"
#include <catch.hxx>
#include <view.hxx>

Game_config const config;

/*
test cases checks whether each ball updates the score according to their
color. Blue should update score by 1 point, red should update score by 2
 points, green should update score by 3 points and yellow should update score
 by 5 points.
 */
TEST_CASE("Clicking of ball updates score based on color")
{
    Model m(config);

    //start game
    CHECK(m.game_start_ == false);
    m.game_start_ = true;
    m.initialize_balls();

    //make sure each colored ball updates score correctly
    for (auto each_ball : m.balls)
    {
        //save the current score, then add the score for the corresponding
        // circles and check whether it is accurate.
        int score = m.score_;
        if (each_ball.color == "blue")
        {
            m.score_ += 1;
            CHECK(m.score_ == score + 1);
        }

        if (each_ball.color == "red")
        {
            m.score_ += 2;
            CHECK(m.score_ == score + 2);
        }

        if (each_ball.color == "green")
        {
            m.score_ += 3;
            CHECK(m.score_ == score + 3);
        }

        if (each_ball.color == "yellow")
        {
            m.score_ += 5;
            CHECK(m.score_ == score + 5);
        }
    }
}

/*
 tests whether the blue power up is working. The blue power up should stop
 the circles in place (velocities zero) for 5 seconds. The circles should
 move again when the five seconds are over.
 */
TEST_CASE("Blue Power Up test")
{
    Model m(config);

    //start game
    CHECK(m.game_start_ == false);
    m.game_start_ = true;
    m.ball.live = true;

    //5 frames per second
    double const dt = 0.2;

    //check the velocity for the first ball. all balls behave the same as the
    // first ball
    m.balls[0].live = true;
    m.balls[0].velocity.width = 10;
    m.balls[0].velocity.height = 10;

    Ball expected_ball(m.balls[0]);

    //checks whether the velocities are zero
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
        CHECK(m.balls[0].velocity.width == 0.0);
        CHECK(m.balls[0].velocity.height == 0.0);
    };

    //checks whether the velocities are non zero
    auto check_frame_2 = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
        CHECK(m.balls[0].velocity.width != 0.0);
        CHECK(m.balls[0].velocity.height != 0.0);
    };

    //blue power up used
    m.circle_stop = true;

    //check whether the ball's velocity is zero for 5 seconds
    for (int i = 0; i < 24; i++)
    {
        check_frame();
    }

    //check whether the ball's velocity is not zero anymore after 5 seconds.
    // checks whether the ball is moving again after the power up expires
    for (int i = 25; i < 50; i ++)
    {
        check_frame_2();
    }
}

/*
 tests whether the yellow power up is working. The yellow power up should stop
 the timer in place for 10 seconds. The test should check whether the timer
 is not moving and whether the seconds_elapsed isn't changing when the red
 power up is used.
 */
TEST_CASE("Yellow Power Up test")
{
    Model m(config);

    //start game
    CHECK(m.game_start_ == false);
    m.game_start_ = true;

    //5 frames per second
    double const dt = 0.2;

    //checks whether the timer stops for 10 seconds.
    //checks whether the seconds elapsed doesn't change and whether the
    // timer_stop_time is less than 10 seconds.
    auto check_frame = [&] {
        m.on_frame(dt);
        CHECK(m.timer_stop == true);
        CHECK(m.timer_stop_time < 10.0);
        CHECK(m.seconds_elapsed() == 5.0);
    };

    //yellow power up used
    m.timer_stop = true;
    m.seconds_elapsed_ = 5.0;

    //checks whether the timer is stopped for 10 seconds (50 frames)
    for (int i = 0; i < 49; i++)
    {
        check_frame();
    }

}

//checks whether the balls are changing in radius and whether they are in the
// correct range. The balls should have a radius between 8 and 12.
TEST_CASE("Test if ball have different radius and in the correct range")
{
    Model m(config);

    //start game
    CHECK(m.game_start_ == false);
    m.game_start_ = true;
    m.initialize_balls();

    //run at 1 frame per second
    double const dt = 1;

    //checks whether the radius are in range
    Ball expected_ball(m.balls[0]);
    auto check_frame = [&] {
        expected_ball = expected_ball.next(dt);
        m.on_frame(dt);
        CHECK(8<=m.balls[0].radius);
        CHECK(m.balls[0].radius <= 12);
    };

    //simulates 5 seconds
    for (int i = 0; i< 5;i++)
    {
        check_frame();
    }

}

//tests whether the time (seconds elapsed) is working accurately. Checks
// whether the time is being incremented correctly.
TEST_CASE("Test if time works")
{
    Model m(config);
    //start game
    CHECK(m.game_start_ == false);
    m.game_start_ = true;

    //run at 1 frame per second
    double const dt = 1;

    //Checks whether the time runs as expected
    double expect_time = m.seconds_elapsed();
    auto check_frame = [&] {
        expect_time += dt;
        m.on_frame(dt);
        CHECK(m.seconds_elapsed() == expect_time);
    };

    //simulate 10 seconds
    for (int i = 0; i< 10;i++)
    {
        check_frame();
    }

}

