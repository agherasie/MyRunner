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
    #define DYING 15
    #define TIRING 16
    #define JUMP 0
    #define BADNIK_DEATH 1
    #define BRAKE 2
    #define DEATH 3
    #define SPIN 4
    #define RING_LOSS 5
    #define RING_COLLECT 6
    #define GOALSIGN 7
    #define TALLY 8
    #define ONEUP 9
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

typedef struct ring {
    sfVector2f pos;
    sfBool is_collected;
    sfBool is_null;
} ring;

typedef struct game {
    sfRenderWindow *window;
    sfClock *clock;
    sfTime time;
    sfEvent event;
    int seconds;
    char **map;
    object *tile;
    object *plx[11];
    sfBool paused;
    sfVector2f camera_pan;
    sfVector2f camera_speed;
    int height;
    int width;
    int frame;
    enemy *e;
    ring *r;
    object *ring;
    animation ring_anim;
    int ring_frame;
    sfMusic *bgm[5];
    sfMusic *title_music;
    sfMusic *finish_music;
    object *goalsign;
    animation goalanim;
    int goalframe;
    sfText *score_text;
    sfFont *hud_font;
    int score;
    int hiscore;
    int rings;
    object *player_icon;
    int lives;
    int level;
    object *title_sonic;
    object *title_background;
    sfBool is_main_menu;
    int title_sonic_frame;
    sfBool is_runner;
    animation ocean_anim;
    int ocean_frame;
    int tally_speed;
    int select;
    sfMusic *select_sound;
    int pause_frame;
    sfTexture *sonic_text;
    sfTexture *tails_text;
    sfTexture *knux_text;
    sfBool character_menu;
    sfBool relaunch;
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
    sfBool is_dropping;
    sfBool is_dying;
    int is_edging;
    int anim_state;
    animation anim[17];
    int running_anim;
    int anim_frame;
    sfMusic *sound[10];
    int cooldown;
    char character;
    sfBool is_flying;
    sfBool is_gliding;
} player;

int launch_game();
void do_death(player *p, game *g);
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
void update_enemies(game *g, player *p, enemy *e);
void animate_object(game *g, object *obj, animation anim, int *frame);
void update_background(game *g, player *p);
int is_solid(int square);
void enemy_collision(player *p, enemy *e, game *g);
enemy *create_enemies(int enemy_count, char **map);
int find_free_spot(char **map, int map_pos_x);
ring *create_rings(int ring_count, char **map);
void update_rings(game *g, player *p);
void ring_collision(player *p, ring *r, game *g, int i);
player create_bools(player p);
void restart(game *g, player *p);
void destroy_entities(game *g);
void fade_transition(game *g);
player create_animations(player p, char character);
player create_sonic_animations(player p);
player create_tails_animations(player p);
player create_knux_animations(player p);
void pause_game(game *g, player *p);
void toggle(sfBool *boolean);
void hud_display(game *g, sfBool center);
void update_title_screen(game *g);
void keyboard_events(game *g, player *p);
void pause_game(game *g, player *p);
void destroy_all(game *g, player *p);
void pause_menu(game *g);
void draw_text(game *g, char *str, float x, float y);
void d_txt_var(game *g, char *str, sfVector2i pos, int value);
void draw_spr_at_pos(game *g, sfSprite *spr, float x, float y);
void update_clock(game *g, player *p);
void invisible_walls(player *p, game *g);
void enemy_collision(player *p, enemy *e, game *g);
void ring_collision(player *p, ring *r, game *g, int i);
int is_ring_collision(player *p, ring *r, game *g);
int is_enemy_collision(player *p, enemy *e, game *g);
void sound_update(player *p);
void camera_adjustments(player *p, game *g, sfBool is_first);
void misc(player *p);
void update_unpaused(player *p, game *g);
void update_lives(player *p, game *g);
void tally(player *p, game *g);
void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos);
void draw_tile(game *g, sfSprite *spr, sfVector2f pos);
void tile_interpretor(char **map, int y, int x);
void do_damage(player *p, game *g);
void player_hit(player *p, game *g);
void enemy_death(enemy *e, player *p);
void player_release_key(game *g, player *p);
void toggle_music(game *g);
void stop_music(game *g);
void switch_music(game *g, sfMusic *music);

#endif /* MY_RUNNER_H_ */
