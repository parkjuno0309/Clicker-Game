#pragma once

#include <ge211.hxx>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The radius of the ball:
    int ball_radius;

    ge211::Posn<int> ball_center;

    ge211::Dims<float> ball_velocity_0;

    // Leave if needed
    int max_boost;





};

