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
	gContext->init_fn = level_init;
	gContext->init_fn = main_menu_init;
	gContext->update_fn = NULL;
	gContext->close_fn = NULL;

	gContext->meta = NULL;

	gContext->shouldQuit = SDL_FALSE;
	gContext->shouldChange = SDL_TRUE;

	TTF_Init();
	gContext->font = TTF_OpenFont(ASSETS"pixel_font.ttf", 150);
	gContext->font2 = TTF_OpenFont(ASSETS"yoster-island.regular.ttf", 120);

	g_GameInput.key_mapper.map_arr = pacman_key_map(&(g_GameInput.key_mapper.amount));
	g_GameInput.pad_mapper.map_arr = pacman_pad_map(&(g_GameInput.pad_mapper.amount));
	srand(0x9AC533D);
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

	SDLX_record_input(NULL);
	gContext->shouldQuit = SDLX_poll();
	SDLX_GameInput_Mouse_Fill(&(g_GameInput), SDL_TRUE);
	SDLX_KeyMap(&(g_GameInput.key_mapper), g_GameInput.keystate);
	if (gContext->shouldQuit == SDL_TRUE)
		return ;

	gContext->update_fn(gContext, gContext->meta);

	if (gContext->shouldQuit != SDL_TRUE && SDLX_discrete_frames(NULL) != EXIT_FAILURE)
	{
		SDLX_RenderQueue_Flush(NULL, SDLX_GetDisplay()->renderer, SDL_TRUE);
		SDLX_ScreenReset(SDLX_GetDisplay()->renderer, NULL);
	}
}

int	main(void)
{
	t_pmContext	gContext;

	SDLX_GetDisplay();
	pacman_initalize(&(gContext));

#ifdef EMCC
	emscripten_set_main_loop_arg(main_loop, (void *)&(gContext), 0, SDL_TRUE);
#else
	while (gContext.shouldQuit == SDL_FALSE)
		main_loop(&(gContext));
#endif
	return (EXIT_SUCCESS);
}
