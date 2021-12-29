/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** game.c
*/

#include "my_runner.h"

void stop_music(game *g)
{
    sfMusic_stop(g->title_music);
    sfMusic_stop(g->finish_music);
    for (int i = 0; i < 3; i++)
        sfMusic_stop(g->bgm[i]);
}

void toggle_music(game *g)
{
    int volume = sfMusic_getVolume(g->title_music) == 0 ? 100: 0;
    sfMusic_setVolume(g->title_music, volume);
    sfMusic_setVolume(g->finish_music, volume);
    for (int i = 0; i < 3; i++)
        sfMusic_setVolume(g->bgm[i], volume);
}

void switch_music(game *g, sfMusic *music)
{
    if (sfMusic_getStatus(music) == sfPlaying)
        return;
    sfMusic_stop(g->title_music);
    sfMusic_stop(g->finish_music);
    for (int i = 0; i < 3; i++)
        sfMusic_stop(g->bgm[i]);
    sfMusic_play(music);
}

void toggle(sfBool *boolean)
{
    if (*boolean == sfTrue)
        *boolean = sfFalse;
    else
        *boolean = sfTrue;
}

void level_init(game *g)
{
    if (g->event.key.code == sfKeyNum1)
        g->level = 1;
    if (g->event.key.code == sfKeyNum2)
        g->level = 2;
    if (g->event.key.code == sfKeyNum3)
        g->level = 3;
}

void press_enter(game *g, player *p)
{
    if (g->event.key.code == sfKeyEnter) {
        if (g->is_main_menu == sfTrue) {
            g->character_menu = sfTrue;
            g->paused = sfTrue;
        }
        if (p->goal_reached == sfTrue) {
            g->tally_speed = 2;
            p->cooldown = 9700;
        }
    }
}

void keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtClosed)
        sfRenderWindow_close(g->window);
    if (g->event.type == sfEvtKeyPressed) {
        pause_game(g, p);
        press_enter(g, p);
        level_init(g);
        if (g->event.key.code == sfKeyR)
            toggle(&g->is_runner);
    }
    if (!(p->anim_state == HURTING && p->is_grounded == sfFalse)
    && g->paused == sfFalse)
        player_keyboard_events(g, p);
    else
        player_release_key(g, p);

}

void fade_transition(game *g)
{
    int alpha = 0;
    if (g->pause_frame < 255)
        alpha = g->pause_frame;
    if (g->pause_frame >= 255)
        alpha = 255 - g->pause_frame % 255;
    if (g->pause_frame >= 255*2)
        alpha = 0;
    g->pause_frame += 20;
    sfRectangleShape *screen = sfRectangleShape_create();
    sfRectangleShape_setFillColor(screen, (sfColor) {0, 0, 0, alpha});
    sfRectangleShape_setSize(screen, (sfVector2f) {W_W, W_H});
    sfRenderWindow_drawRectangleShape(g->window, screen, NULL);
    sfRectangleShape_destroy(screen);
}

void update(game *g, player *p)
{
    while (sfRenderWindow_isOpen(g->window))
        if (sfClock_getElapsedTime(g->clock).microseconds > 1000)
            update_clock(g, p);
    destroy_all(g, p);
    if (g->relaunch == sfTrue)
        launch_game();
    return;
}