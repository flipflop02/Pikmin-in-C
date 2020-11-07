/*
** EPITECH PROJECT, 2018
** my h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics/Color.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Graphics/Export.h>
#include <SFML/System/Time.h>

typedef struct t_window {
    sfVideoMode mode;
    int length;
    int width;
    sfRenderWindow *window;
}t_window;

typedef struct t_pikminfield {
    int place;
    char *state;
    sfVector2f hitbox;
    sfSprite *sprite;
    sfTexture *texture;
    struct t_pikminfield *next;
    struct t_pikminfield *prev;
}t_pikminfield;

typedef struct t_character {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f hitbox;
    sfVector2f scale;
    sfVector2f pos;
}t_character;

typedef struct t_entity {
    t_pikminfield *pkmn_field;
    t_character *olimar;
}t_entity;

typedef struct t_game {
    t_window *win;
    t_entity *en;
    sfEvent event;
}t_game;

#endif
