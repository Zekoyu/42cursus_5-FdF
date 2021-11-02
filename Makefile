SRCS = 	fdf.c \
		colors_utils.c \
		colors_utils_2.c \
		mlx_utils.c \
		parsing.c \
		render.c \
		render_utils.c \
		handle_errors.c \
		key_handlers.c

SRCS_BONUS = 	fdf_bonus.c \
				colors_utils_bonus.c \
				colors_utils_2_bonus.c \
				mlx_utils_bonus.c \
				parsing_bonus.c \
				render_bonus.c \
				render_utils_bonus.c \
				handle_errors_bonus.c \
				key_handlers_bonus.c

LIBFT = ./libft/libft.a

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef INCLUDE_BONUSES
OBJS_LIST = $(OBJS_BONUS)
else
OBJS_LIST = $(OBJS)
endif

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Imlx

# $< = first prerequisite (= xxxx.c = c files)
# $(<:.c=.o) = xxxx.c to xxxx.o (simply changes .c to .o on file name)
# -I = search for headers in this directory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS_LIST) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_LIST) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

bonus:		
	$(MAKE) INCLUDE_BONUSES=1

$(LIBFT):
	$(MAKE) -C libft

all:		$(NAME)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:		clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)


re:			fclean all

.PHONY:	all clean fclean re bonus