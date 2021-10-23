/***************************************************************************
 * FILENAME:    main_scene.c
 * DESCRIPTION: Handles the main menu scene
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Oct2021
***************************************************************************/

#include "pacman.h"

typedef struct	s_main_menu_scene
{
	t_text		start;
	t_text		start_h;
	SDLX_Sprite	s_transform;
	SDLX_button	start_b;

	int			ticks;
}				t_main_menu_scene;

void	*main_menu_init(t_pmContext *context, SDL_UNUSED void *vp_scene)
{
	t_main_menu_scene	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"main_menu.png", main_menu_close, main_menu_update);

	create_text(&(scene->start), 0xFFFF0b00, (SDL_Rect){0, 220, 0, 0}, "START", .15, context->font);
	create_text(&(scene->start_h), 0x444FFF00, (SDL_Rect){0, 220, 0, 0}, "START", .15, context->font);

	scene->start.sprite._dst.x = (224 - scene->start.sprite._dst.w) / 2; /* center for button's trigger box */

	SDLX_Button_Init(&(scene->start_b), NULL, 0, (SDL_Rect){0, 0, 0, 0}, NULL);
	scene->start_b.trigger_fn = button_trigger_start_scene_switch;
	scene->start_b.trigger_box = scene->start.sprite._dst;
	scene->start_b.isGloballyActive = SDL_TRUE;
	scene->start_b.sprite.sprite_data = NULL;
	scene->start_b.meta1 = level_init;
	scene->start_b.meta = context;

	scene->s_transform = scene->start.sprite;
	scene->s_transform.dst = SDLX_NULL_SELF;

	scene->ticks = 0;

	return (NULL);
}

void	*main_menu_close(SDL_UNUSED t_pmContext *context, void *vp_scene)
{
	t_main_menu_scene	*scene;
	SDLX_Sprite			*background;

	scene = vp_scene;

	SDL_free(scene->start.message);
	SDL_free(scene->start_h.message);

	SDL_DestroyTexture(scene->start.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->start_h.sprite.sprite_data->texture);

	SDL_free(scene->start.sprite.sprite_data);
	SDL_free(scene->start_h.sprite.sprite_data);

	background = SDLX_ClearBackground();
	SDL_DestroyTexture(background->sprite_data->texture);
	SDL_free(background->sprite_data);
	SDL_free(scene);

	return (NULL);
}

void	*main_menu_update(SDL_UNUSED t_pmContext *context, void *vp_scene)
{
	t_main_menu_scene	*scene;
	double				scale;

	scene = vp_scene;

	scale = (SDL_sin(scene->ticks / 2) * .04) + 1;
	scene->s_transform._dst.w = scene->start.sprite._dst.w * scale;
	scene->s_transform._dst.h = scene->start.sprite._dst.h * scale;
	scene->s_transform._dst.x = (224 - scene->s_transform._dst.w) / 2;
	scene->s_transform.sprite_data = scene->start.sprite.sprite_data;

	SDLX_Button_Update_noDraw(&(scene->start_b));
	if (scene->ticks % 10 < 7)
	{
		if (scene->start_b.isFocused == SDL_TRUE)
			scene->s_transform.sprite_data = scene->start_h.sprite.sprite_data;
		SDLX_RenderQueue_Add(NULL, &(scene->s_transform));
	}

	scene->ticks++;

	return (NULL);
}
