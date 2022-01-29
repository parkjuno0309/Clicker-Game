#include <iostream>
#include "view.hxx"
#include "ball.hxx"
#include "model.hxx"
#include "game_config.hxx"


Ball::Ball(int r,ge211::Posn<int> c,ge211::Dims<float> v,bool L, std::string
color)
    :radius(r),
     center(c),
     velocity(v),
     live(L),
     color(color)
{}

Ball::Ball(Game_config const& config)
        : radius(config.ball_radius),
          center(config.ball_center),
          velocity(Velocity(config.ball_velocity_0)),
          live(false)
{}


Position
Ball::top_left() const
{
    Position p = Position(Ball::center);
    p.up_by(Ball::radius);
    p.left_by(Ball::radius);
    return p;
}

bool
Ball::hits_bottom(Game_config const& config) const
{
    Position p = Position(Ball::center);
    if (p.down_by(Ball::radius).y > 600){
        return true;
    }
    return false;
}

bool
Ball::hits_top(Game_config const&) const
{
    Position p = Position(Ball::center);
    if (p.up_by(Ball::radius).y < 0){
        return true;
    }
    return false;
}

bool
Ball::hits_side(Game_config const& config) const
{
    // compare the axis instead of (x,y) with 0
    if (( center.x - radius < 0 ) or ( center.x + radius> 800)){
        return true;
    }
    return false;
}

Ball
Ball::next(double dt) const
{
    Ball result(*this);
    result.center += dt * result.velocity;
    return result;
}

void
Ball::reflect_vertical()
{
    velocity.height *= -1;
}

void
Ball::reflect_horizontal()
{
    velocity.width *= -1;
}

bool
operator==(Ball const& a, Ball const& b)
{
    if ((a.velocity == b.velocity)&&(a.center == b.center)&&(a.radius == b.radius)&&(a.live == b.live))
    {
        return true;
    }
    return false;
}

bool
operator!=(Ball const& a, Ball const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Ball const& ball)
{
    o << "Ball{";
    o << "TODO: see the bottom of ball.cxx for more info";
    return o << "}";
}