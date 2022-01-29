/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"


// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        :
          ball_radius {10},
          ball_center {390, 290},
          ball_velocity_0 {75, -300},
          max_boost(200)
          //scene_dims{780,580}
{ }

