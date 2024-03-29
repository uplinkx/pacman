/***************************************************************************
 * FILENAME:    update.c
 * DESCRIPTION: Pacman common game update code.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 09Feb2021
***************************************************************************/

#include "pacman.h"

int		update_map(t_level_scene *scene)
{
	int	p_x;
	int	p_y;
	int	score;

	score = 0;
	p_x = scene->player.x;
	p_y = scene->player.y;

	if (scene->map[p_y][p_x] == '.')
	{
		scene->map[p_y][p_x] = ' ';
		// if (SDLX_XboxController_link(0) != NULL)
		// 	SDL_GameControllerRumble(SDLX_XboxController_link(0), 0x0100, 0xFF00, 30);
		score += 10;
	}
	if (scene->map[p_y][p_x] == 'P')
	{
		scene->blinky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(scene->blinky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		scene->pinky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(scene->pinky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		scene->inky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(scene->inky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		scene->clyde.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(scene->clyde.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		scene->map[p_y][p_x] = ' ';
		scene->fright_ticks = 70;
		score += 100;
	}

	if (scene->fright_ticks > 0)
		scene->fright_ticks--;

	return (score);
}
