/*
** EPITECH PROJECT, 2021
** MYRRUNER
** File description:
** my.runner.h
*/

#ifndef MY_RUNNER_H_
    #define MY_RUNNER_H_
    #define W_W 800
    #define W_H 600
    #define FPS 60
    #define TOPSPEED 8
    #define IDLE 0
    #define WALKING 1
    #define RUNNING 2
    #define JUMPING 3
    #define TURNING 4
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include "my.h"

typedef struct game {
    sfRenderWindow *window;
    sfClock *clock;
    sfTime time;
    sfEvent event;
    char **map;
} game;

typedef struct animation {
    int row;
    int length;
    float speed;
} animation;

typedef struct object {
    sfSprite *spr;
    sfTexture *text;
    sfIntRect rect;
    sfVector2f scale;
    sfVector2f pos;
} object;

typedef struct player {
    object *obj;
    float speed_x, speed_y;
    sfBool deceleration;
    sfBool acceleration;
    sfBool is_turning;
    int running_anim;
    int anim_frame;
    int direction;
    float meters_run;
    sfBool is_jumping;
    sfBool is_grounded;
    int anim_state;
    animation anim[5];
} player;

void create_animation(animation *anim, int length, float speed);
void update(game *g, player *p);
void update_player(player *p, game *g);
void player_keyboard_events(game *g, player *p);
game create_game();
player create_player();
object *create_object(int pixel_size, int scale, char *filepath);
void player_keyboard_events(game *g, player *p);
void gravity(player *p);
void movement(player *p);
void deceleration(player *p);
void acceleration(player *p);

#endif /* MY_RUNNER_H_ */
