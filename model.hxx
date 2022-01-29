#pragma once

#include <ge211.hxx>
#include "ball.hxx"
#include "game_config.hxx"
#include <vector>

class Model
{
public:
    void start();

    void on_frame(double dt);

    double seconds_elapsed() const;

    bool game_start();

    bool game_start_ = false;

    bool red_power_up_used = false;

    bool yellow_power_up_used = false;

    bool blue_power_up_used = false;

    bool timer_stop = false;

    bool circle_stop = false;

    double timer_stop_time = 0.0;

    double circle_stop_time = 0.0;

    explicit Model(Game_config const& config = Game_config());

    void launch();

    Game_config const config;

    std::vector<Ball> balls;

    Ball ball;

    ge211::Random_source<int> random_radius;

    // In case needed
    ge211::Random_source<int> random_boost_source;

    void reset_seconds_elapsed();

    void initialize_balls();

    std::size_t score() const;

    std::size_t score_ = 0;

    void reset_score();

    double seconds_elapsed_ = 0.0;

};
