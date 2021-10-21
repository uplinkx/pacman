/***************************************************************************
 * FILENAME:    main.c
 * DESCRIPTION: Entry point for Pacman
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Feb2021
***************************************************************************/

#include "pacman.h"

#ifdef EMCC
 # include <emscripten.h>
#endif

void	pacman_initalize(t_pmContext *gContext)
{
	gContext->ticks = 0;

	init_input_mappers();

	srand(0x9AC533D);

	gContext->shouldQuit = SDL_FALSE;
	gContext->shouldChange = SDL_TRUE;

	gContext->init_fn = level_init;
}

void	main_loop(void *v_cxt)
{
	t_pmContext		*gContext;

	gContext = v_cxt;
	if (gContext->shouldChange == SDL_TRUE)
	{
		gContext->init_fn(gContext, gContext->meta);
		gContext->shouldChange = SDL_FALSE;
	}

	gContext->shouldQuit = input_entry(&(g_GameInput));
	if (gContext->shouldQuit == SDL_TRUE)
		return ;

	gContext->update_fn(gContext, gContext->meta);

	if (gContext->shouldQuit != SDL_TRUE && SDLX_discrete_frames(&(gContext->ticks)) != EXIT_FAILURE)
	{
		SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_TRUE);
		SDLX_ScreenReset(SDLX_GetDisplay()->renderer, NULL);
	}
	gContext->rQueue.index = 0;
}

#include <stdio.h>

int	main(void)
{
	t_pmContext	gContext;

	SDLX_GetDisplay();
	printf("Testing\n");
	pacman_initalize(&(gContext));

#ifdef EMCC
	emscripten_set_main_loop_arg(main_loop, (void *)&(gContext), 0, SDL_TRUE);
#else
	while (gContext.shouldQuit == SDL_FALSE)
		main_loop(&(gContext));
#endif
	return (EXIT_SUCCESS);
}
