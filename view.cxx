#include <iostream>
#include "view.hxx"

static std::string const bg_music_filename {"bg.mp3"};

View::View(Model const& model, ge211::Mixer& mixer)
        : power_up_width(20),
          aim_cross_size(1.0),
          timer_speed(1000/70),
          offset(1),
          aim_cross_radius(20),
          width(780),
          height(580),
          ball_live(false),
          ball_velocity(75,-300),
          ball_radius(8),
          random_coordinate_x(0, width),
          random_coordinate_y(0, height),
          red_rect_coordinates(random_coordinate_x.next(),
                               random_coordinate_y.next()),
          yellow_rect_coordinates(random_coordinate_x.next(),
                                  random_coordinate_y.next()),
          blue_rect_coordinates(random_coordinate_x.next(),
                                random_coordinate_y
                  .next()),
          ball_center(width/2,height/2),
          timer_bar({1,4}, ge211::Color::white()),
          aim_cross("aim_cross.png"),
          start_box({250, 50}, ge211::Color::medium_red()),
          retry_box({125,50}, ge211::Color::medium_red()),
          exit_box({125,50}, ge211::Color::medium_red()),
          score_text("score here",sans30),
          red_power_up({power_up_width, power_up_width},
                       ge211::Color::medium_red()),
          yellow_power_up({power_up_width,power_up_width},
                          ge211::Color::medium_yellow()),
          blue_power_up({power_up_width, power_up_width},
                        ge211::Color::medium_blue()),
          ball_sprite_blue_8(8, ge211::Color::medium_blue()),
          ball_sprite_blue_9(9, ge211::Color::medium_blue()),
          ball_sprite_blue_10(10, ge211::Color::medium_blue()),
          ball_sprite_blue_11(11, ge211::Color::medium_blue()),
          ball_sprite_blue_12(12, ge211::Color::medium_blue()),
          ball_sprite_red_8(8, ge211::Color::medium_red()),
          ball_sprite_red_9(9, ge211::Color::medium_red()),
          ball_sprite_red_10(10, ge211::Color::medium_red()),
          ball_sprite_red_11(11, ge211::Color::medium_red()),
          ball_sprite_red_12(12, ge211::Color::medium_red()),
          ball_sprite_green_8(8,ge211::Color::medium_green()),
          ball_sprite_green_9(9,ge211::Color::medium_green()),
          ball_sprite_green_10(10,ge211::Color::medium_green()),
          ball_sprite_green_11(11,ge211::Color::medium_green()),
          ball_sprite_green_12(12,ge211::Color::medium_green()),
          ball_sprite_yellow_8(8,ge211::Color::medium_yellow()),
          ball_sprite_yellow_9(9,ge211::Color::medium_yellow()),
          ball_sprite_yellow_10(10,ge211::Color::medium_yellow()),
          ball_sprite_yellow_11(11,ge211::Color::medium_yellow()),
          ball_sprite_yellow_12(12,ge211::Color::medium_yellow()),
          score_sprite_("0", sans24),
        //final_score_sprite_(model_.score(), sans30),
          previous_score_(0),
          mixer_(mixer),
          model_(model)
{
    if (mixer_.is_enabled()) {
        load_audio_();
    }
}

void
View::draw(ge211::Sprite_set& set, ge211::Posn<int> mouse)
{
    if (!model_.game_start_) {
        set.add_sprite(start_box, ge211::Posn<int> {270, 250}, 2);
        set.add_sprite(start_text,
                       ge211::Posn<int> {305, 248}, 3);
    }

    set.add_sprite(timer_bar, ge211::Posn<int> {0, 0});
    ge211::Transform
            smallerer = ge211::Transform {}.scale(aim_cross_size / 40.0);
    set.add_sprite(aim_cross, mouse, 1, smallerer);
    draw_timer(set);
    draw_score(set,750,25,10);

    if (model_.game_start_) {

        for (auto each_balls: model_.balls)
        {
            //std::cout << model_.balls.size() << std::endl;
            if (each_balls.color == "blue")
            {
                if (each_balls.radius == 8)
                {
                    set.add_sprite(ball_sprite_blue_8, each_balls.top_left()
                                                                 .into<int>());
                }
                if (each_balls.radius == 9)
                {
                    set.add_sprite(ball_sprite_blue_9, each_balls.top_left()
                                                                 .into<int>());
                }
                if (each_balls.radius == 10)
                {
                    set.add_sprite(ball_sprite_blue_10, each_balls.top_left()
                                                                  .into<int>());
                }
                if (each_balls.radius == 11)
                {
                    set.add_sprite(ball_sprite_blue_11, each_balls.top_left()
                                                                  .into<int>());
                }
                if (each_balls.radius == 12)
                {
                    set.add_sprite(ball_sprite_blue_12, each_balls.top_left()
                                                                  .into<int>());
                }

            }
            else if (each_balls.color == "red")
            {
                if (each_balls.radius == 8)
                {
                    set.add_sprite(ball_sprite_red_8, each_balls.top_left()
                                                                .into<int>());
                }
                if (each_balls.radius == 9)
                {
                    set.add_sprite(ball_sprite_red_9, each_balls.top_left()
                                                                .into<int>());
                }
                if (each_balls.radius == 10)
                {
                    set.add_sprite(ball_sprite_red_10, each_balls.top_left()
                                                                 .into<int>());
                }
                if (each_balls.radius == 11)
                {
                    set.add_sprite(ball_sprite_red_11, each_balls.top_left()
                                                                 .into<int>());
                }
                if (each_balls.radius == 12)
                {
                    set.add_sprite(ball_sprite_red_12, each_balls.top_left()
                                                                 .into<int>());
                }

            }
            else if (each_balls.color == "green")
            {
                if (each_balls.radius == 8)
                {
                    set.add_sprite(ball_sprite_green_8,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 9)
                {
                    set.add_sprite(ball_sprite_green_9,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 10)
                {
                    set.add_sprite(ball_sprite_green_10,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 11)
                {
                    set.add_sprite(ball_sprite_green_11,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 12)
                {
                    set.add_sprite(ball_sprite_green_12,
                                   each_balls.top_left().into<int>());
                }

            }
            else if (each_balls.color == "yellow")
            {
                if (each_balls.radius == 8)
                {
                    set.add_sprite(ball_sprite_yellow_8,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 9)
                {
                    set.add_sprite(ball_sprite_yellow_9,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 10)
                {
                    set.add_sprite(ball_sprite_yellow_10,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 11)
                {
                    set.add_sprite(ball_sprite_yellow_11,
                                   each_balls.top_left().into<int>());
                }
                if (each_balls.radius == 12)
                {
                    set.add_sprite(ball_sprite_yellow_12,
                                   each_balls.top_left().into<int>());
                }
            }

        }

        if (model_.game_start_) {
            //make both appear in random positions
            if (!model_.red_power_up_used) {
                set.add_sprite(red_power_up, red_rect_coordinates);
            }

            if (!model_.yellow_power_up_used) {
                set.add_sprite(yellow_power_up, yellow_rect_coordinates);
            }
            if (!model_.blue_power_up_used) {
                set.add_sprite(blue_power_up, blue_rect_coordinates);
            }
        }

        //if (model_.seconds_elapsed() >= 3.0) -> for testing only, don't delete
        if ((timer_speed * model_.seconds_elapsed()) >= width)
        {
            //when time reaches 60s
            //draw score
            //set.add_sprite(model_.score(), ge211::Posn<int> {320, 248},3);
            draw_score(set,380,248,10);
            //draw retry
            set.add_sprite(retry_box,
                           ge211::Posn<int> {135, 250}, 2);
            set.add_sprite(retry_text,
                           ge211::Posn<int> {160, 248}, 3);
            //draw exit
            set.add_sprite(exit_box,
                           ge211::Posn<int> {520, 250}, 2);
            set.add_sprite(exit_text,
                           ge211::Posn<int> {555, 248}, 3);

        }
    }
}

void
View::draw_timer(ge211::Sprite_set& sprites)
{
    double multiple = model_.seconds_elapsed();
    int width = multiple*(1000/70);
    auto trans = ge211::Transform()
            .set_scale_x(width)
            .set_scale_y(4);
    sprites.add_sprite(timer_bar, {0,0}, 1, trans);
}

//Copied from bejeweled
// add xyz parameter to adjust its position
void
View::draw_score(ge211::Sprite_set& sprites,int x,int y,int z)
{
    // If the score has changed, update the score sprite.
    if (model_.score() != previous_score_) {
        ge211::Text_sprite::Builder builder(sans30);
        builder << model_.score();
        score_sprite_.reconfigure(builder);
    }

    //sprites.add_sprite(score_sprite_, {750, 25}, 10);
    sprites.add_sprite(score_sprite_, {x, y}, z);
}

//code from bejeweled
void
View::resume_music_if_ended() const
{
    if (mixer_.get_music_state() == ge211::Mixer::State::paused) {
        mixer_.resume_music();
    }
}

//code from bejeweled
void
View::load_audio_()
{
    if (bg_music_.try_load(bg_music_filename, mixer_))
    {
        mixer_.play_music(bg_music_,true);
    }

}