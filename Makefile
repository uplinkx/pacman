NAME = index.html

MEM_CHECK = -fsanitize=address
FLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes/
LIBRARIES = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="['png']"
SKELE_HTML = --shell-file srcs/skeleton.html

PRELOAD_FILES =							\
	assets/


PRELOAD = --preload-file $(PRELOAD_FILES)

SDLX_DIR = SDLX/
SRCS_DIR = srcs/

BIN_DIR = bin/

SRCS_NAMES =		\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))		\
	background		\
	extra_texture	\
	ghost_sprite	\
	ghost			\
	input			\
	main 			\
	map				\
	player			\
	update			\

SDLX_NAMES = 			\
	SDLX_background		\
	SDLX_init			\
	SDLX_input			\
	SDLX_ticks			\
	SDLX_render_queue	\
	SDLX_render			\
	SDLX_utils			\

C_FILES =				\
	$(SRCS_NAMES) 		\

SRCS = $(addsuffix .c, $(addprefix srcs/, $(C_FILES)))

all: $(NAME)

$(NAME):
	emcc $(FLAGS) $(INCLUDES) $(LIBRARIES) $(PRELOAD) $(SRCS) $(SKELE_HTML) -o $(NAME)

run: all
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
