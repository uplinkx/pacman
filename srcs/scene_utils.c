/***************************************************************************
 * FILENAME:    scene_utils.c
 * DESCRIPTION: Has functions for scene utility.
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

void	*new_scene(size_t size, t_pmContext *context, char *background_path, void *(close)(t_pmContext *, void *), void *(update)(t_pmContext *, void *))
{
	void *result;

	result = SDL_calloc(1, size);

	SDL_assert(close != NULL);
	SDL_assert(update != NULL);

	context->close_fn = close;
	context->update_fn = update;
	context->meta = result;
	context->shouldChange = SDL_FALSE;

	if (background_path != NULL)
	{
		context->background = SDLX_Sprite_Static(background_path);
		SDLX_SetBackground(&(context->background));
	}
	else
		SDLX_SetBackground(NULL);

	return (result);
}

void	*button_trigger_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length)
{
	t_pmContext *context;

	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft))
	{
		context = vp_context;
		context->init_fn = self->meta1;
		context->shouldChange = SDL_TRUE;
	}

	return (NULL);
}

void	*button_trigger_start_scene_switch(SDLX_button *self, void *vp_context, SDL_UNUSED size_t length)
{
	t_pmContext *context;

	if (g_GameInput.GameInput.button_primleft || g_GameInput.keystate[SDL_SCANCODE_RETURN]
		|| g_GameInput.keystate[SDL_SCANCODE_SPACE])
	{
		context = vp_context;
		context->init_fn = self->meta1;
		context->shouldChange = SDL_TRUE;
	}

	return (NULL);
}
