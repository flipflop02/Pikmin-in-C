/*
** Pikmin C project
** 
**
** 
*/

#include "../../include/my.h"

t_character *handle_character_movement(t_character *character){
    if (character->up == 1) {
        sfSprite_setTexture(character->sprite, character->texture_back, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y--;
    }
    if (character->down == 1) {
        sfSprite_setTexture(character->sprite, character->texture_front, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.y++;
    }
    if (character->left == 1) {
        sfSprite_setTexture(character->sprite, character->texture_left, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x--;
    }
    if (character->right == 1) {
        sfSprite_setTexture(character->sprite, character->texture_right, sfTrue);
        sfSprite_setTextureRect(character->sprite, character->rect);
        character->pos.x++;
    }
    sfSprite_setPosition(character->sprite, character->pos);
    return (character);
}

int world_event(t_game *game) {
    while (sfRenderWindow_pollEvent(game->win->window, &game->event)){
        if (game->event.type == sfEvtClosed)
            sfRenderWindow_close(game->win->window);

            if (sfKeyboard_isKeyPressed(sfKeyUp))
                game->en->olimar->up = 1;
            else
                game->en->olimar->up = 0;
            if (sfKeyboard_isKeyPressed(sfKeyDown))
                game->en->olimar->down = 1;
            else
                game->en->olimar->down = 0;
            if (sfKeyboard_isKeyPressed(sfKeyLeft))
                game->en->olimar->left = 1;
            else
                game->en->olimar->left = 0;
            if (sfKeyboard_isKeyPressed(sfKeyRight))
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
    world_event(game);
    handle_character_movement(game->en->olimar);
    draw_character(game->win->window, game->en->olimar);
}
