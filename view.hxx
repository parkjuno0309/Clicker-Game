#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model,ge211::Mixer& mixer);

    void draw(ge211::Sprite_set& set, ge211::Posn<int> mouse);

    int power_up_width;

    double aim_cross_size;

    double timer_speed;

    int offset;

    int aim_cross_radius;

    int width;

    int height;

    bool ball_live;

    ge211::Dims<float> ball_velocity;

    int ball_radius;

    ge211::Random_source<int> random_coordinate_x;

    ge211::Random_source<int> random_coordinate_y;

    ge211::Posn<int> red_rect_coordinates;

    ge211::Posn<int> yellow_rect_coordinates;

    ge211::Posn<int> blue_rect_coordinates;

    ge211::Posn<int> ball_center;

    void load_audio_();

    void resume_music_if_ended() const;

private:
    void draw_timer(ge211::Sprite_set& sprites);
    void draw_score(ge211::Sprite_set&, int x, int y, int z);
    ge211::Rectangle_sprite timer_bar;
    ge211::Image_sprite aim_cross;
    ge211::Rectangle_sprite start_box;
    ge211::Rectangle_sprite retry_box;
    ge211::Rectangle_sprite exit_box;
    ge211::Font sans30 {"sans.ttf", 30};
    ge211::Font sans24 {"sans.ttf", 24};
    ge211::Text_sprite start_text {"Click to Start", sans30};
    ge211::Text_sprite score_text;
    ge211::Text_sprite exit_text {"Exit", sans30};
    ge211::Text_sprite retry_text {"Retry", sans30};
    ge211::Rectangle_sprite red_power_up;
    ge211::Rectangle_sprite yellow_power_up;
    ge211::Rectangle_sprite blue_power_up;
    ge211::Text_sprite score_sprite;

    ge211::Circle_sprite ball_sprite_blue_8;
    ge211::Circle_sprite ball_sprite_blue_9;
    ge211::Circle_sprite ball_sprite_blue_10;
    ge211::Circle_sprite ball_sprite_blue_11;
    ge211::Circle_sprite ball_sprite_blue_12;

    ge211::Circle_sprite ball_sprite_red_8;
    ge211::Circle_sprite ball_sprite_red_9;
    ge211::Circle_sprite ball_sprite_red_10;
    ge211::Circle_sprite ball_sprite_red_11;
    ge211::Circle_sprite ball_sprite_red_12;

    ge211::Circle_sprite ball_sprite_green_8;
    ge211::Circle_sprite ball_sprite_green_9;
    ge211::Circle_sprite ball_sprite_green_10;
    ge211::Circle_sprite ball_sprite_green_11;
    ge211::Circle_sprite ball_sprite_green_12;

    ge211::Circle_sprite ball_sprite_yellow_8;
    ge211::Circle_sprite ball_sprite_yellow_9;
    ge211::Circle_sprite ball_sprite_yellow_10;
    ge211::Circle_sprite ball_sprite_yellow_11;
    ge211::Circle_sprite ball_sprite_yellow_12;
    ge211::Text_sprite score_sprite_;
    ge211::Text_sprite final_score_sprite_;
    std::size_t previous_score_;
    ge211::Mixer& mixer_;
    ge211::Music_track bg_music_;
    Model const& model_;
};
