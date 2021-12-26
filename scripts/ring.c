/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** ring.c
*/

#include "my_runner.h"

void update_rings(game *g, player *p)
{
    animate_object(g, g->ring, g->ring_anim, &g->ring_frame);
    sfSprite_setTextureRect(g->ring->spr, g->ring->rect);
    for (int i = 0; g->r[i].is_null == sfFalse; i++) {
        if (g->r[i].is_collected == sfFalse) {
            if (g->paused == sfFalse && p->goal_reached == sfFalse)
                g->r[i].pos.x -= g->camera_pan_speed;
            sfSprite_setPosition(g->ring->spr, g->r[i].pos);
            sfRenderWindow_drawSprite(g->window, g->ring->spr, NULL);
        }
    }
}

ring *create_rings(int ring_count, char **map)
{
    ring *r = malloc(sizeof(enemy) * (ring_count + 1));
    r[ring_count] = (ring) {(sfVector2f) {-100, 0}, sfFalse, sfTrue};
    for (int i = 0; i < ring_count; i++) {
        int random_value = range(i * 50 + 225, i * 50 + 225);
        int free_spot = 0;
        int map_pos_x = random_value / 100;
        if (random_value % 100 > 50)
            map_pos_x++;
        free_spot = find_free_spot(map, map_pos_x);
        r[i].pos = (sfVector2f) {random_value, free_spot * 100};
        r[i].is_collected = sfFalse;
        r[i].is_null = sfFalse;
    }
    return r;
}
