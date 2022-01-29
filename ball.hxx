#pragma once

#include <ge211.hxx>

#include <iostream>

#include "model.hxx"

#include "game_config.hxx"



using Position = ge211::Posn<float>;

using Velocity = ge211::Dims<float>;

struct Ball
{
    Ball(int r,ge211::Posn<int> c,ge211::Dims<float> v,bool L, std::string
    color);

    Ball(Game_config const&);

    Position top_left() const;

    Ball next(double dt) const;

    bool hits_top(Game_config const&) const;

    bool hits_bottom(Game_config const&) const;

    bool hits_side(Game_config const&) const;

    void reflect_vertical();

    void reflect_horizontal();

    int radius;
    Position center;
    Velocity velocity;
    bool live;
    std::string color;


};



