#include <iostream>
#include "controller.hxx"

Controller::Controller()
        :view_(model_,mixer())
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code(' ')) {
        model_.game_start_ = true;
    }
    if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
    view_.resume_music_if_ended();
}

void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    int mouse_x = position.x - 18*view_.offset;
    int mouse_y = position.y - 18*view_.offset;
    mouse = ge211::Posn<int> {mouse_x, mouse_y};
}

void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> posn)
{
    int mouse_x = mouse.x;
    int mouse_y = mouse.y;


    if (model_.red_power_up_used)
    {
        mouse_x += 18*view_.offset;
        mouse_y += 18*view_.offset;
    }


    if (!model_.game_start())
    {
        if ((mouse.x < 520 && mouse.x > 270) && (mouse.y < 300 && mouse.y >
                                                                  250))
        {
            model_.game_start_ = true;
        }
    }

    if (model_.game_start_)
    {
        model_.launch();
        if(!model_.red_power_up_used)
        {
            if (((mouse_x < view_.red_rect_coordinates.x + view_.power_up_width)
            && (mouse_x > view_.red_rect_coordinates.x - view_.power_up_width))
            && (mouse_y < view_.red_rect_coordinates.y + view_.power_up_width)
            && (mouse_y > view_.red_rect_coordinates.y - view_.power_up_width))
            {
                view_.aim_cross_size *= 2.0;
                view_.offset *= 2;
                view_.aim_cross_radius *= 2;
                model_.red_power_up_used = true;
            }
        }

        if(!model_.yellow_power_up_used)
        {
            if (((mouse_x < view_.yellow_rect_coordinates.x
                + view_.power_up_width)
            && (mouse_x > view_.yellow_rect_coordinates.x
                - view_.power_up_width))
            && (mouse_y < view_.yellow_rect_coordinates.y
                + view_.power_up_width)
            && (mouse_y > view_.yellow_rect_coordinates.y
                - view_.power_up_width))
            {
                model_.timer_stop = true;
                model_.yellow_power_up_used = true;
            }
        }

        if(!model_.blue_power_up_used)
        {
            if (((mouse_x < view_.blue_rect_coordinates.x + view_
                    .power_up_width)
                 && (mouse_x > view_.blue_rect_coordinates.x - view_
                    .power_up_width))
                && (mouse_y < view_.blue_rect_coordinates.y + view_
                    .power_up_width)
                && (mouse_y > view_.blue_rect_coordinates.y -view_
                    .power_up_width))
            {
                model_.circle_stop = true;
                model_.blue_power_up_used = true;
            }
        }

        // timer bar is equal to width of the screen
        // for testing
        //if (model_.seconds_elapsed() >= 3.0)
        if ((view_.timer_speed * model_.seconds_elapsed()) >= view_.width)
        {
            // time reaches limit, make the game over first
            // if mouse hits retry
            if ((mouse.x < 260 && mouse.x > 135) && (mouse.y < 300 && mouse.y
                                                                      >250))
            {
                // game restart
                model_.game_start_ = false;
                model_.reset_seconds_elapsed();
                model_.reset_score();
                model_.initialize_balls();
            }
            // if mouse hits exit
            if ((mouse.x < 645 && mouse.x > 520) && (mouse.y < 300 && mouse.y
                                                                      >250))
            {
                // game exit
                quit();
            }

        }

    }

    if (model_.game_start_)
    {
        for (auto &each_balls : model_.balls)
        {
            float dist = ((mouse_x - each_balls.center.x)
                    * (mouse_x - each_balls.center.x))
                            + ((mouse_y - each_balls.center.y)
                            * (mouse_y - each_balls.center.y));
            int radius_sum = (each_balls.radius + view_.aim_cross_radius) *
                             (each_balls.radius + view_.aim_cross_radius);

            if (dist < radius_sum)
            {
                if (each_balls.color == "blue")
                {
                    model_.score_ += 1;
                }
                else if (each_balls.color == "red")
                {
                    model_.score_ += 2;
                }
                else if (each_balls.color == "green")
                {
                    model_.score_ += 3;
                }
                else if (each_balls.color == "yellow")
                {
                    model_.score_ += 5;
                }

                each_balls = model_.balls.back();
                model_.balls.pop_back();

            }
        }
    }



}
