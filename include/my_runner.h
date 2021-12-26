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
    #define LOOKING 8
    #define CROUCHING 9
    #define THUMBSUP 10
    #define HURTING 11
    #define SPINNING 12
    #define DASHING 13
    #define SPEEDING 14
    #define JUMP 0
    #define BADNIK_DEATH 1
    #define BRAKE 2
    #define DEATH 3
    #define SPIN 4
    #define RING_LOSS 5
    #define RING_COLLECT 6
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

typedef struct animation {
    sfBool loop;
    int length;
    int speed;
} animation;

typedef struct enemy {
    object *obj;
    float pos;
    int enemytype;
    animation anim[3];
    int frame;
    int direction;
    sfBool is_dead;
} enemy;

typedef struct game {
    sfRenderWindow *window;
    sfClock *clock;
    sfTime time;
    sfEvent event;
    char **map;
    object *tile;
    object *parallax0;
    object *parallax1;
    sfBool paused;
    float camera_pan_x;
    float camera_pan_speed;
    int height;
    int width;
    int frame;
    enemy *e;
    sfMusic *bg_music;
    object *goalsign;
    sfText *score_text;
    sfFont *hud_font;
    int score;
    int hiscore;
    int rings;
} game;

typedef struct player {
    object *obj;
    sfVector2i map_pos;
    float speed_x, speed_y;
    int direction;
    float meters_run;
    float collision_y;
    float collision_x;
    sfBool deceleration;
    sfBool acceleration;
    sfBool is_turning;
    sfBool is_looking;
    sfBool is_crouching;
    sfBool is_jumping;
    sfBool is_grounded;
    sfBool can_move;
    sfBool goal_reached;
    sfBool is_hurt;
    sfBool is_spinning;
    sfBool is_dashing;
    sfBool is_charging;
    sfBool is_speeding;
    int is_edging;
    int anim_state;
    animation anim[15];
    int running_anim;
    int anim_frame;
    sfMusic *sound[7];
    int cooldown;
} player;

game create_game();
char **create_map(char *filepath, game *g);
player create_player(game *g);
object *create_object(int pixel_size, int scale, char *filepath);
void create_animation(animation *anim, int length, float speed, sfBool loop);
void update(game *g, player *p);
void update_player(player *p, game *g);
void player_keyboard_events(game *g, player *p);
void gravity(player *p);
void movement(player *p, game *g);
void deceleration(player *p);
void acceleration(player *p);
void animate(player *p);
void wall_collision(player *p, game *g);
void raycast(player *p, game *g);
void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos);
char **create_map(char *filepath, game *g);
void update_enemies(game *g, player *p);
void animate_object(game *g, object *obj, animation anim, int *frame);
void update_background(game *g, player *p);
int is_solid(int square);
void enemy_collision(player *p, enemy *e, game *g);
enemy *create_enemies(int enemy_count, char **map);
int find_free_spot(char **map, int map_pos_x);

#endif /* MY_RUNNER_H_ */
