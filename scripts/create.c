/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** create.c
*/

#include "my_runner.h"
#include "create.h"

void reset_values(game *g, player *p)
{
    g->ring_frame = 0;
    g->rings = 0;
    g->seconds = 0;
    g->goalsign->rect.left = 0;
    g->frame = 0;
    g->goalframe = 0;
    p->speed_y = 0;
    p->speed_x = 0;
    p->map_pos.x = 0;
    p->map_pos.y = 0;
    g->tally_speed = 5;
    g->rings = 0;
}

void restart(game *g, player *p)
{
    reset_values(g, p);
    for (int i = 0; i < 6; i++)
        free(g->map[i]);
    free(g->map);
    if (g->level == 1)
        g->map = create_map("data/map1.txt", g);
    if (g->level == 2)
        g->map = create_map("data/map2.txt", g);
    if (g->level == 3)
        g->map = create_map("data/map3.txt", g);
    switch_music(g, g->bgm[g->level - 1]);
    g->camera_pan = (sfVector2f) {0, 0};
    destroy_entities(g);
    g->e = create_enemies((int)(g->width / 3) - 3, g->map);
    g->r = create_rings((g->width - 5) * 2, g->map);
    sfSprite_setTextureRect(g->goalsign->spr, g->goalsign->rect);
    p->obj->pos = (sfVector2f) {100, find_free_spot(g->map, 0) * 100 + 48};
    *p = create_bools(*p);
}

game create_game(void)
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    sfRenderWindow_setPosition(g.window, (sfVector2i) {500, 200});
    g.clock = sfClock_create();
    g = create_animations_game(create_values(create_art(g)));
    g.relaunch = sfFalse;
    g.map = create_map("data/map1.txt", &g);
    g.e = create_enemies((int)(g.width / 3) - 3, g.map);
    g.r = create_rings((g.width - 5) * 2, g.map);
    g.hud_font = sfFont_createFromFile("art/sonic-hud-font.ttf");
    create_sonic_title(g, 224, 320);
    g.score_text = sfText_create();
    sfText_setFont(g.score_text, g.hud_font);
    g.score_text = style_text(g.score_text);
    g.player_icon->pos = (sfVector2f) {10, W_W - 100};
    g.player_icon->rect = (sfIntRect) {48, 0, 48, 48};
    sfSprite_setPosition(g.player_icon->spr, g.player_icon->pos);
    sfSprite_setTextureRect(g.player_icon->spr, g.player_icon->rect);
    return g;
}
