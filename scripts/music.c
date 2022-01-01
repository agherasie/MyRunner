/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** music.c
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
