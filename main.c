/*
** EPITECH PROJECT, 2021
** RUNNER
** File description:
** main.c
*/

#include "my_runner.h"

#define W_W 800
#define W_H 600
#define FPS 60

typedef struct sprite {
    sfSprite *spr;
    sfTexture *text;
    sfIntRect rect;
    sfVector2f scale;
    sfVector2f pos;
    float speed_x, speed_y;
    sfBool deceleration;
} sprite;

void keyboard_events(game *g, sprite *p)
{
    while (sfRenderWindow_pollEvent(g->window, &g->event)) {
        if (g->event.type == sfEvtClosed)
            sfRenderWindow_close(g->window);
        if (g->event.type == sfEvtKeyPressed) {
            if (g->event.key.code == sfKeyRight) {
                if (p->scale.x < 0) {
                    p->scale.x *= -1;
                    p->pos.x -= p->rect.width * 2;
                }
                p->deceleration = sfFalse;
                if (p->speed_x < 0)
                    p->speed_x = 0;
                p->speed_x += 0.2f;
                if (p->speed_x >= 6)
                    p->speed_x = 6;
            }
            if (g->event.key.code == sfKeyLeft) {
                if (p->scale.x > 0) {
                    p->scale.x *= -1;
                    p->pos.x += p->rect.width * 2;
                }
                p->deceleration = sfFalse;
                if (p->speed_x > 0)
                    p->speed_x = 0;
                p->speed_x -= 0.2f;
                if (p->speed_x <= -6)
                    p->speed_x = -6;
            }
        }
        if (g->event.type == sfEvtKeyReleased) {
            if (g->event.key.code == sfKeyRight || g->event.key.code == sfKeyLeft) {
                p->deceleration = sfTrue;
            }
        }
    }
}

sprite create_player()
{
    sprite player;
    player.spr = sfSprite_create();
    player.rect.left = 42;
    player.rect.top = 16;
    player.rect.height = 56;
    player.rect.width = 32;
    player.scale.x = 2;
    player.scale.y = 2;
    sfSprite_setTextureRect(player.spr, player.rect);
    player.text = sfTexture_createFromFile("sonic.png", NULL);
    sfSprite_setTexture(player.spr, player.text, sfFalse);
    player.speed_x = 0;
    player.speed_y = 0;
    player.pos.x = 0;
    player.pos.y = 0;
    return player;
}

void update_player(sprite *p, game *g)
{
    sfSprite_setScale(p->spr, p->scale);
    if (p->pos.y < 500) {
        p->speed_y += 0.5f;
    }
    if (p->pos.y > 500) {
        p->speed_y = 0;
        p->pos.y = 500;
    }
    p->pos.x += p->speed_x;
    p->pos.y += p->speed_y;
    if (p->deceleration == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= 0.2f;
        if (p->speed_x < 0)
            p->speed_x += 0.2f;
        if (p->speed_x >= -0.1f && p->speed_x <= 0.1f) {
            p->speed_x = 0;
            p->deceleration = sfFalse;
        }
    }
    printf("speed_x = %f\nspeed_y = %f\n", p->speed_x, p->speed_y);
    sfSprite_setPosition(p->spr, p->pos);
    sfRenderWindow_drawSprite(g->window, p->spr, NULL);
}

void update(game *g, sprite *p)
{
    while (sfRenderWindow_isOpen(g->window)) {
        g->time = sfClock_getElapsedTime(g->clock);
        if (g->time.microseconds > 1000) {
            sfClock_restart(g->clock);
            sfRenderWindow_display(g->window);
            sfRenderWindow_clear(g->window, sfWhite);
            keyboard_events(g, p);
            update_player(p, g);
        }
    }
    return;
}

game create_game()
{
    game g;
    sfVideoMode mode = {W_W, W_H, 32};
    g.window = sfRenderWindow_create(mode, "my_runner", sfClose, NULL);
    g.clock = sfClock_create();
    return g;
}

int launch_game()
{
    game g = create_game();
    sprite p = create_player();
    sfRenderWindow_setMouseCursorVisible(g.window, sfTrue);
    sfRenderWindow_setFramerateLimit(g.window, FPS);
    update(&g, &p);
    return EXIT_SUCCESS;
}

void print_file(char *filepath, int buffsize)
{
    int fp = open(filepath, O_RDONLY);
    char buff[buffsize];
    if (fp != -1) {
        read(fp, buff, buffsize);
        my_putstr(buff);
        close(fp);
    }
    return;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        return launch_game();
    } else if (ac == 2) {
        if (my_strcmp(av[1], "-h") == 0)
            print_file("readme", 1000);
        if (my_strcmp(av[1], "-c") == 0)
            print_file("credits", 2100);
    }
}
