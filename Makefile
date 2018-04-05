NAME = 	wolf3d

SRC = 	src/main.c \
		src/load.c \
		src/draw_something.c \
		src/raycasting.c \
		src/init.c \
		src/mouse.c \
		src/ft_move.c \
		src/key_hook.c\
		src/intro.c\
		src/xpm.c \

FLAGS = -Wall -Werror -Wextra

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc -o $@ -c $< 

$(NAME): $(OBJ)
	@echo "\033[35m(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling... Wait a sec.\033[0m"
	@make -C libft
	@gcc -g -o $(NAME) $(FLAGS) $(OBJ) libft/libft.a -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
	@echo "\033[36m(•̀ᴗ•́)و $(NAME) generated!\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[33m¯\_(ツ)_/¯ Objects removed!\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[33m(╯°□°）╯︵ ┻━┻ $(NAME) removed!\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
