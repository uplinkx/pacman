/***************************************************************************
 * FILENAME:    level_scene.c
 * DESCRIPTION: Handles the regular level.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 20Oct2021
***************************************************************************/

#include "pacman.h"

void	*level_init(t_pmContext *context, void *vp_scene)
{
	t_level_scene	*scene;

	scene = new_scene(sizeof(*scene), context, NULL, level_close, level_update);

	scene->ticks = 0;
	fill_map(&(scene->map));

	instance_ghost(&(scene->blinky),	SD_BLINKY | SD_GHOST_RIGHT, 12, 11, target_blinky);
	instance_ghost(&(scene->pinky),		SD_PINKY  | SD_GHOST_RIGHT, 12, 11, target_pinky);
	instance_ghost(&(scene->inky),		SD_INKY   | SD_GHOST_RIGHT, 13, 11, target_inky);
	instance_ghost(&(scene->clyde),		SD_CLYDE  | SD_GHOST_RIGHT, 15, 11, target_clyde);
	scene->blinky.map = &(scene->map);
	scene->pinky.map = &(scene->map);
	scene->inky.map = &(scene->map);
	scene->clyde.map = &(scene->map);

	instance_player(&(scene->player), 14, 23);
	scene->player.map = &(scene->map);

	scene->pause = SDL_FALSE;
	scene->clone = SDL_FALSE;


	context->background = SDLX_Sprite_Static(ASSETS"pacman_background.png");
	SDLX_SetBackground(&(context->background));

	(void)vp_scene;
	return (NULL);
}

void	*level_close(t_pmContext *context, void *vp_scene)
{
	(void)context;
	(void)vp_scene;
	return (NULL);
}

void	*level_update(t_pmContext *context, void *vp_scene)
{
	t_level_scene	*scene;

	scene = vp_scene;
	if (g_GameInput.GameInput.button_GUIDE)
	{
		SDL_Log("Pressed");
		if (scene->pause == SDL_FALSE)
		{
			scene->pause = SDL_TRUE;
			SDL_Delay(140);
		}
		else
		{
			scene->pause = SDL_FALSE;
			SDL_Delay(140);
		}
	}

	if (g_GameInput.GameInput.button_START)
		context->shouldChange = SDL_TRUE;

	if (scene->pause == SDL_FALSE)
	{
		update_ghost(scene, &(scene->blinky));
		update_ghost(scene, &(scene->pinky));
		update_ghost(scene, &(scene->inky));
		update_ghost(scene, &(scene->clyde));

		update_player(scene->ticks, &(scene->player));

		update_map(scene);
	}
	draw_pellets(&(scene->map));
	scene->ticks++;

	return (NULL);
}
