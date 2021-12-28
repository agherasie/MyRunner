/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** game.c
*/

#include "my_runner.h"

void destroy_entities(game *g)
{
    free(g->r);
    for (int i = 0; g->e[i].enemytype != -1; i++) {
        sfSprite_destroy(g->e[i].obj->spr);
        sfTexture_destroy(g->e[i].obj->text);
    }
    free(g->e);
}

void destroy_all(game *g, player *p)
{
    destroy_entities(g);
    sfSprite_destroy(g->ring->spr);
    sfTexture_destroy(g->ring->text);
    sfText_destroy(g->score_text);
    sfFont_destroy(g->hud_font);
    sfSprite_destroy(g->tile->spr);
    sfTexture_destroy(g->tile->text);
    sfClock_destroy(g->clock);
    sfSprite_destroy(p->obj->spr);
    sfTexture_destroy(p->obj->text);
    for (int i = 0; g->map[i] != NULL; i++)
        free(g->map[i]);
    free(g->map);
    sfMusic_destroy(g->bg_music);
    sfMusic_destroy(g->title_music);
    sfMusic_destroy(g->finish_music);
    sfMusic_destroy(g->select_sound);
    for (int i = 0; i < 10; i++)
        sfMusic_destroy(p->sound[i]);
    sfSprite_destroy(g->parallax0->spr);
    sfSprite_destroy(g->parallax1->spr);
    sfTexture_destroy(g->parallax0->text);
    sfTexture_destroy(g->parallax1->text);
    sfSprite_destroy(g->parallax2->spr);
    sfSprite_destroy(g->parallax3->spr);
    sfTexture_destroy(g->parallax2->text);
    sfTexture_destroy(g->parallax3->text);
    sfSprite_destroy(g->title_sonic->spr);
    sfTexture_destroy(g->title_sonic->text);
    sfRenderWindow_destroy(g->window);
}

void toggle(sfBool *boolean)
{
    if (*boolean == sfTrue)
        *boolean = sfFalse;
    else
        *boolean = sfTrue;
}

void keyboard_events(game *g, player *p)
{
    while (sfRenderWindow_pollEvent(g->window, &g->event)) {
        if (g->event.type == sfEvtClosed)
            sfRenderWindow_close(g->window);
        if (g->event.type == sfEvtKeyPressed) {
            pause_game(g, p);
            if (g->event.key.code == sfKeyEnter) {
                if (g->is_main_menu == sfTrue)
                    g->is_main_menu = sfFalse;
                if (p->goal_reached == sfTrue) {
                    g->tally_speed = 2;
                    p->cooldown = 9700;
                }
            }
            if (g->event.key.code == sfKeyR)
                toggle(&g->is_runner);
        }
        player_keyboard_events(g, p);
    }
}

void update_title_screen(game *g)
{
    draw_text(g, "epitech 2021", W_W / 20 - 12, W_H / 20 - 3.5f);
    if (sfMusic_getStatus(g->title_music) != sfPlaying)
        sfMusic_play(g->title_music);
    g->title_sonic_frame--;
    sfRenderWindow_setPosition(g->window, (sfVector2i) {600, 175});
    g->title_sonic->rect.height = 224;
    g->title_sonic->rect.width = 320;
    if (g->title_sonic_frame == 0) {
        g->title_sonic->rect.left += 320;
        g->title_sonic_frame = 10;
    }
    if (g->title_sonic->rect.left >= 320 * 3 && g->title_sonic->rect.top < 224 * 5) {
        g->title_sonic->rect.left = 0;
        g->title_sonic->rect.top += 224;
    }
    if (g->title_sonic->rect.left >= 320 * 3 && g->title_sonic->rect.top == 224 * 5) {
        g->title_sonic->rect.left = 320;
        g->title_sonic->rect.top = 224 * 5;
    }
    sfSprite_setTextureRect(g->title_sonic->spr, g->title_sonic->rect);
    sfRenderWindow_drawSprite(g->window, g->title_sonic->spr, NULL);
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
