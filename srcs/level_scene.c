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

void	*level_init(t_pmContext *context, SDL_UNUSED void *vp_scene)
{
	char	buff[30];
	t_level_scene	*scene;

	scene = new_scene(sizeof(*scene), context, ASSETS"pacman_background.png", level_close, level_update);

	scene->ticks = 0;
	fill_map(&(scene->map));

	instance_ghost(&(scene->blinky),	SD_BLINKY | SD_GHOST_RIGHT, 12, 11, target_blinky, &(scene->map));
	instance_ghost(&(scene->pinky),		SD_PINKY  | SD_GHOST_RIGHT, 12, 11, target_pinky, &(scene->map));
	instance_ghost(&(scene->inky),		SD_INKY   | SD_GHOST_RIGHT, 13, 11, target_inky, &(scene->map));
	instance_ghost(&(scene->clyde),		SD_CLYDE  | SD_GHOST_RIGHT, 15, 11, target_clyde, &(scene->map));

	instance_player(&(scene->player), 14, 23);
	scene->player.map = &(scene->map);

	scene->pause = SDL_FALSE;
	scene->clone = SDL_FALSE;

	scene->player.lives = 3;

	create_text(&(scene->ready), 0xFFFF0b00, (SDL_Rect){0, 140, 16, 16}, "READY!", .14, context->font2);
	create_text(&(scene->gameover), 0xFF404b00, (SDL_Rect){0, 115, 16, 16}, "GAME OVER", .14, context->font2);
	scene->gameover.sprite._dst.x = (224 - scene->gameover.sprite._dst.w) / 2;

	size_t	i;

	i = 0;
	while (i < sizeof(scene->lives) / sizeof(*(scene->lives)))
	{
		fetch_PacManSpriteInfo(&(scene->lives[i].sprite_data), SD_PACMAN_LEFT);
		scene->lives[i]._dst = (SDL_Rect){i * 16, 16 * 16, 16, 16};
		scene->lives[i].dst = SDLX_NULL_SELF;
		scene->lives[i].current = 1;
		i++;
	}

	scene->score = 0;
	create_text(&(scene->t_score), 0xFFFFFF00, (SDL_Rect){0, -2, 16, 16}, "12345678901234567890", .08, context->font);
	create_text(&(scene->high_score), 0xFFFFFF00, (SDL_Rect){4, -2, 16, 16}, "HIGH SCORE", .08, context->font);

	SDL_itoa(context->best, buff, 10);
	create_text(&(scene->best_score), 0xFFFFFF00, (SDL_Rect){4, -2, 16, 16}, buff, .08, context->font);
	scene->best_score.sprite._dst.x = 100 - scene->best_score.sprite._dst.w;

	create_text(&(scene->play_again), 0xFFFFFF00, (SDL_Rect){224 / 2, 115 + 25, 0, 0}, "PLAY AGAIN?", .08, context->font);
	scene->play_again.sprite._dst.x = (224 - scene->play_again.sprite._dst.w) / 2;

	SDLX_Button_Init(&(scene->play_again_b), NULL, 0, (SDL_Rect){0, 0, 0, 0}, NULL);
	scene->play_again_b.trigger_fn = button_trigger_start_scene_switch;
	scene->play_again_b.trigger_box = scene->play_again.sprite._dst;
	scene->play_again_b.isGloballyActive = SDL_TRUE;
	scene->play_again_b.meta1 = level_init;
	scene->play_again_b.meta = context;

	return (NULL);
}

void	*level_close(t_pmContext *context, void *vp_scene)
{
	t_level_scene	*scene;
	SDLX_Sprite		*background;

	scene = vp_scene;
	if (context->best < scene->score)
		context->best = scene->score;

	SDL_free(scene->ready.message);
	SDL_free(scene->t_score.message);
	SDL_free(scene->gameover.message);
	SDL_free(scene->high_score.message);
	SDL_free(scene->best_score.message);
	SDL_free(scene->play_again.message);

	SDL_DestroyTexture(scene->ready.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->t_score.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->gameover.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->high_score.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->best_score.sprite.sprite_data->texture);
	SDL_DestroyTexture(scene->play_again.sprite.sprite_data->texture);

	SDL_free(scene->ready.sprite.sprite_data);
	SDL_free(scene->t_score.sprite.sprite_data);
	SDL_free(scene->gameover.sprite.sprite_data);
	SDL_free(scene->high_score.sprite.sprite_data);
	SDL_free(scene->best_score.sprite.sprite_data);
	SDL_free(scene->play_again.sprite.sprite_data);

	background = SDLX_ClearBackground();
	SDL_DestroyTexture(background->sprite_data->texture);
	SDL_free(background->sprite_data);
	SDL_free(scene);
	return (NULL);
}

void	*level_update(t_pmContext *context, void *vp_scene)
{
	int				ix;
	char			buff[10];
	t_level_scene	*scene;

	scene = vp_scene;

	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, GUIDE))
		scene->pause ^= SDL_TRUE;
	if (g_GameInput.GameInput.button_START)
		context->shouldChange = SDL_TRUE;

	if (scene->pause == SDL_FALSE && scene->ticks > 60 && scene->player.lives > 0)
	{
		catch_gesture();

		update_ghost(scene, &(scene->blinky));
		update_ghost(scene, &(scene->pinky));
		update_ghost(scene, &(scene->inky));
		update_ghost(scene, &(scene->clyde));

		update_player(scene->ticks, &(scene->player));

		scene->score += update_map(scene);

		ix = 0;
		while (ix < scene->player.lives)
		{
			SDLX_RenderQueue_Add(NULL, &(scene->lives[ix]));
			ix++;
		}
	}
	else if (scene->ticks < 60)
	{
		if (scene->ticks >= 20)	{ change_message(&(scene->ready), "3", SDL_FALSE); }
		if (scene->ticks >= 35)	{ change_message(&(scene->ready), "2", SDL_FALSE); }
		if (scene->ticks >= 50)	{ change_message(&(scene->ready), "1", SDL_FALSE); }
		scene->ready.sprite._dst.x = (224 - scene->ready.sprite._dst.w) / 2;
		SDLX_RenderQueue_Add(NULL, &(scene->ready.sprite));
	}
	scene->t_score.set = buff;
	SDL_itoa(scene->score, buff, 10);
	update_text(&(scene->t_score), sizeof(buff));
	scene->t_score.sprite._dst.x = 224 - scene->t_score.sprite._dst.w - 4;
	SDLX_RenderQueue_Add(NULL, &(scene->high_score.sprite));
	SDLX_RenderQueue_Add(NULL, &(scene->best_score.sprite));
	SDLX_RenderQueue_Add(NULL, &(scene->t_score.sprite));

	if (scene->player.dead == SDL_TRUE && scene->player.sprite.current + 1 == scene->player.sprite.sprite_data->cycle)
	{
		scene->blinky.x	= 12;
		scene->blinky.y	= 11;
		scene->pinky.x	= 12;
		scene->pinky.y	= 11;
		scene->inky.x	= 13;
		scene->inky.y	= 11;
		scene->clyde.x	= 13;
		scene->clyde.y	= 11;
	}

	if (scene->player.lives == 0)
	{
		if (scene->ticks % 10 < 7)
		{
			SDLX_RenderQueue_Add(NULL, &(scene->play_again.sprite));
			SDLX_RenderQueue_Add(NULL, &(scene->gameover.sprite));
		}
		SDLX_Button_Update_noDraw(&(scene->play_again_b));
	}

	draw_pellets(&(scene->map));
	scene->ticks++;

	return (NULL);
}
