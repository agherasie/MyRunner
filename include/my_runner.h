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
    #define PUSHING 5
    #define FEDGING 6
    #define BEDGING 7
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include "my.h"

typedef struct object {
    sfSprite *spr;
    sfTexture *text;
    sfIntRect rect;
    sfVector2f scale;
    sfVector2f pos;
} object;

typedef struct game {
    sfRenderWindow *window;
    sfClock *clock;
    sfTime time;
    sfEvent event;
    char **map;
    object *tile;
} game;

typedef struct animation {
    int row;
    int length;
    int speed;
} animation;

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
    sfBool can_move;
    sfBool is_edging;
    int anim_state;
    animation anim[8];
    float collision_y;
    float collision_x;
    sfVector2i map_pos;
} player;

game create_game();
player create_player();
object *create_object(int pixel_size, int scale, char *filepath);
void create_animation(animation *anim, int length, float speed);
void update(game *g, player *p);
void update_player(player *p, game *g);
void player_keyboard_events(game *g, player *p);
void player_keyboard_events(game *g, player *p);
void gravity(player *p);
void movement(player *p, game *g);
void deceleration(player *p);
void acceleration(player *p);
void animate(player *p);
void wall_collision(player *p, game *g);
void raycast(player *p, game *g);

#endif /* MY_RUNNER_H_ */
