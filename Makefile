NAME = minirt

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

LIBFT_DIR = libft/
LIBFT = libft/libft.a

ifeq ($(shell uname), Linux)
	MLX_DIR = mlx_Linux/
	INCS = -Iincs -Ilibft -I$(MLX_DIR) -I/usr/include
	LINKER = -L/usr/lib -Lincs -Llibft -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm -lz -lft
else
	MLX_DIR = mlx/
	INCS = -Iincs -Ilibft -Imlx
	LINKER = -Lincs -Llibft -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

SRCS_DIR = srcs/
SRCS = main.c mlx.c parsing.c parsing2.c free.c setup.c \
	vector.c ray.c hits.c utils.c hook.c render.c log.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	make re -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	# make bonus -C $(LIBFT_DIR)
	# make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKER) 
	@echo "minirt is ready"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCS)

clean:
	$(RM) $(OBJS_DIR)
	# @make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) *.dSYM
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
