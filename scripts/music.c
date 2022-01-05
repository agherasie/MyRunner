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
    sfMusic_stop(g->boss_music);
    for (int i = 0; i < 3; i++)
        sfMusic_stop(g->bgm[i]);
}

void toggle_music(game *g)
{
    int volume = sfMusic_getVolume(g->title_music) == 0? 100: 0;
    sfMusic_setVolume(g->title_music, volume);
    sfMusic_setVolume(g->finish_music, volume);
    sfMusic_setVolume(g->boss_music, volume);
    for (int i = 0; i < 3; i++)
        sfMusic_setVolume(g->bgm[i], volume);
}

void switch_music(game *g, sfMusic *music)
{
    if (sfMusic_getStatus(music) == sfPlaying)
        return;
    sfMusic_stop(g->title_music);
    sfMusic_stop(g->finish_music);
    sfMusic_stop(g->boss_music);
    for (int i = 0; i < 3; i++)
        sfMusic_stop(g->bgm[i]);
    sfMusic_play(music);
}

game create_music(game g)
{
    g.bgm[0] = sfMusic_createFromFile("art/sound/rooftoprun.wav");
    g.bgm[1] = sfMusic_createFromFile("art/sound/iceparadise.wav");
    g.bgm[2] = sfMusic_createFromFile("art/sound/gangstasparadise.wav");
    for (int i = 0; i < 3; i++)
        sfMusic_setLoop(g.bgm[i], sfTrue);
    g.title_music = sfMusic_createFromFile("art/sound/liveandlearn.wav");
    g.finish_music = sfMusic_createFromFile("art/sound/stage-clear.wav");
    g.boss_music = sfMusic_createFromFile("art/sound/eggman.ogg");
    sfMusic_setLoop(g.title_music, sfTrue);
    sfMusic_setLoop(g.finish_music, sfFalse);
    sfMusic_setLoop(g.boss_music, sfTrue);
    g.select_sound = sfMusic_createFromFile("art/sound/select.wav");
    return g;
}