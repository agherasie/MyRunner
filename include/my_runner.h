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
} game;

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
} player;

void update(game *g, player *p);
void update_player(player *p, game *g);
void player_keyboard_events(game *g, player *p);
game create_game();
player create_player();
object *create_object(int pixel_size, int scale, char *filepath);

#endif /* MY_RUNNER_H_ */
