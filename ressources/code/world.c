/*
** Pikmin C project
** 
**
** 
*/

#include "../../include/my.h"

void draw_pikmin(sfRenderWindow *window, t_pikminfield *pkmn_field) {
    t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") != 0)
            sfRenderWindow_drawSprite(window, pkmn_field->sprite, NULL);
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") != 0)) {
        sfRenderWindow_drawSprite(window, pkmn_field->sprite, NULL);
    }
    pkmn_field = &begin;
}

sfVector2f getDistanceFromCaptain(t_character *chara, t_pikminfield *pikmin) {
    sfVector2f res;
    int i = 0;
    int j = 0;
    for (; pikmin->pos.x + i < chara->pos.x + 30; i++);
    for (; pikmin->pos.y + j < chara->pos.y + 30; j++);
    res.x = i;
    res.y = j;
    //printf("%d %d\n", i, j);
    return (res);
}

void following(t_character *chara, t_pikminfield *pikmin) {
    sfVector2f dist;
    int i = 0;
    int j = 0;
    for (; pikmin->pos.x + i < chara->pos.x; i++);
    for (; pikmin->pos.y + j < chara->pos.y; j++);
    for (; pikmin->pos.x + i > chara->pos.x; i--);
    for (; pikmin->pos.y + j > chara->pos.y; j--);
    if (i > 0)
        pikmin->pos.x++;
    if (i < 0)
        pikmin->pos.x--;
    if (j > 0)
        pikmin->pos.y++;
    if (j < 0)
        pikmin->pos.y--;
    sfSprite_setPosition(pikmin->sprite, pikmin->pos);
}

void handle_state(t_game *game, t_pikminfield *pkmn_field) {
        t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (pkmn_field->state == 1)
            following(game->en->olimar, pkmn_field);
    }
    if ((pkmn_field->next == NULL)) {
        if (pkmn_field->state == 1)
            following(game->en->olimar, pkmn_field);
            
    }
    pkmn_field = &begin;
}

t_pikminfield *add_new_pikmin(t_pikminfield *pkmn_field, char *type) {
    t_pikminfield begin = *(pkmn_field);
    for (; pkmn_field->next != NULL; pkmn_field = pkmn_field->next) {
        if (strcmp(pkmn_field->type,"NONE") == 0) {
            pkmn_field->type = strdup(type);
            pkmn_field->state = 1;
            printf("Added %d pikmin\n", pkmn_field->place);
            break;
        }
    }
    if ((pkmn_field->next == NULL) && (strcmp(pkmn_field->type,"NONE") == 0)) {
        printf("Found none on %d\n", pkmn_field->place);
        pkmn_field->type = strdup(type);
        pkmn_field->state = 1;
        printf("Added %d pikmin\n", pkmn_field->place);
    }
    pkmn_field = &begin;
    return (pkmn_field);
}

t_character *handle_character_movement(t_character *character){
    if (character->up == 1) {
        sfSprite_setTexture(character->sprite, character->texture_back, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y = character->pos.y - 2;
    }
    if (character->down == 1) {
        sfSprite_setTexture(character->sprite, character->texture_front, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y = character->pos.y + 2;
    }
    if (character->left == 1) {
        sfSprite_setTexture(character->sprite, character->texture_left, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x = character->pos.x - 2;
    }
    if (character->right == 1) {
        sfSprite_setTexture(character->sprite, character->texture_right, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x = character->pos.x + 2;
    }
    sfSprite_setPosition(character->sprite, character->pos);
    return (character);
}

int world_event(t_game *game) {
    while (sfRenderWindow_pollEvent(game->win->window, &game->event)){
        if (game->event.type == sfEvtClosed)
            sfRenderWindow_close(game->win->window);
        if (game->event.type == sfEvtKeyPressed) {
            if (sfKeyboard_isKeyPressed(sfKeyP))
                add_new_pikmin(game->en->pkmn_field, "red");
        }

        if (sfKeyboard_isKeyPressed(sfKeyZ))
            game->en->olimar->up = 1;
        else
            game->en->olimar->up = 0;
        if (sfKeyboard_isKeyPressed(sfKeyS))
            game->en->olimar->down = 1;
        else
            game->en->olimar->down = 0;
        if (sfKeyboard_isKeyPressed(sfKeyQ))
            game->en->olimar->left = 1;
        else
            game->en->olimar->left = 0;
        if (sfKeyboard_isKeyPressed(sfKeyD))
            game->en->olimar->right = 1;
        else
            game->en->olimar->right = 0;
        sfSprite_setPosition(game->en->olimar->sprite, game->en->olimar->pos);

    }
}

int draw_character(sfRenderWindow *window, t_character *olimar)
{
    sfRenderWindow_drawSprite(window, olimar->sprite, NULL);
}

int world(t_game *game)
{
    printf("Beeeeeeeeem\n");
    world_event(game);
    handle_character_movement(game->en->olimar);
    handle_state(game, game->en->pkmn_field);
    draw_character(game->win->window, game->en->olimar);
    draw_pikmin(game->win->window, game->en->pkmn_field);
}
