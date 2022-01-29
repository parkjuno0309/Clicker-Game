#include <iostream>
#include "model.hxx"
#include "view.hxx"
#include "controller.hxx"
#include "ball.hxx"
#include "game_config.hxx"

Model::Model(Game_config const& config)
        : config(config),
          ball(config),
          random_radius(-2,2),
          random_boost_source(-config.max_boost,config.max_boost)
{
    for (int count = 0;count<50;count++)
    {
        //random generate position
        ge211::Posn<int> t = {config.ball_center.x
                              + random_boost_source.next(),
                              config.ball_center.y
                              + random_boost_source.next()};
        // random generate radius with control
        ge211::Dims<float> changing_v = {(config.ball_velocity_0.width
                                         + random_boost_source.next()),
                                         (config.ball_velocity_0.height
                                         + random_boost_source.next())};
        // random generate radius with control
        // random generate center with control
        std::string changing_c;
        int random_num;
        random_num = rand()%10;
        if (random_num <= 2)
        {
            changing_c = "blue";
        }
        if ((2<random_num) && (random_num< 5))
        {
            changing_c = "red";
        }
        if ((4<random_num) && (random_num<7))
        {
            changing_c = "green";
        }
        if ((7<random_num) && (random_num<=9))
        {
            changing_c = "yellow";
        }

        balls.push_back(Ball(ball.radius,t,changing_v,ball.live,
                             changing_c));
    }

}

void
Model::initialize_balls()
{
    for (int count = 0;count<15;count++)
    {
        //random generate position
        ge211::Posn<int> t = {config.ball_center.x
                              + random_boost_source.next(),
                              config.ball_center.y
                              + random_boost_source.next()};
        // random generate radius with control
        ge211::Dims<float> changing_v = {(config.ball_velocity_0.width
                                         + random_boost_source.next()),
                                         (config.ball_velocity_0.height
                                         + random_boost_source.next())};
        // random generate radius with control
        // random generate center with control
        std::string changing_c;
        int random_num;
        random_num = rand()%10;
        if (random_num <= 2)
        {
            changing_c = "blue";
        }
        if ((2<random_num) && (random_num< 5))
        {
            changing_c = "red";
        }
        if ((4<random_num) && (random_num<7))
        {
            changing_c = "green";
        }
        if ((7<random_num) && (random_num<=9))
        {
            changing_c = "yellow";
        }

        balls.push_back(Ball(ball.radius,t,changing_v,ball.live,
                             changing_c));
    }
}






double
Model::seconds_elapsed() const
{
    return seconds_elapsed_;
}

void
Model::reset_seconds_elapsed()
{
    seconds_elapsed_ = 0.0;
}


void
Model::on_frame(double dt)
{
    if(game_start_ && !timer_stop)
    {
        seconds_elapsed_ += dt;

    }

    if (game_start_)
    {
        for (auto &each_balls: balls)
        {
            if (!ball.live){
                return;
            }
            else{
                Ball update_ball = each_balls.next(dt);
                each_balls.radius = 10 + random_radius.next();
                if (update_ball.hits_bottom(config))
                {
                    each_balls.reflect_vertical();
                }
                if (update_ball.hits_top(config))
                {
                    each_balls.reflect_vertical();
                }
                if (update_ball.hits_side(config))
                {
                    each_balls.reflect_horizontal();
                }

                each_balls = each_balls.next(dt);
            }
        }
    }

    if(timer_stop)
    {
        timer_stop_time += dt;

        if (timer_stop_time >= 10.0)
        {
            timer_stop = false;
        }
    }

    if(circle_stop)
    {
        for (auto &each_balls: balls)
        {
            each_balls.velocity = {0,0};
        }
        circle_stop_time += dt;

        if (circle_stop_time >= 5.0)
        {
            circle_stop = false;
            for (auto &each_balls: balls)
            {
                each_balls.velocity = {(config.ball_velocity_0.width +
                                       random_boost_source.next()),
                                       (config.ball_velocity_0
                                       .height+random_boost_source.next())};
            }
        }
    }

}

bool
Model::game_start()
{
    return game_start_;
}

void
Model::launch()
{
    ball.live = true;
}

std::size_t
Model::score() const
{
    return score_;
}

void
Model::reset_score()
{
    score_ = 0;
}