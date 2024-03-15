NAME	=	minishell
SRC		=	minishell.c \
			pipes.c \
			utils/utils.c \
			utils/copy_til_squote.c \
			utils/copy_til_dquote.c \
			utils/test_utils.c \
			env/copy_env.c \
			env/copy_2d.c \
			signals/signals.c \
			strings/remove_from_2d.c \
			strings/ft_concat.c \
			strings/split_by_index.c \
			strings/concat_strings.c \
			splitting/pipe_split.c \
			splitting/space_split.c \
			expansion/line_expansion.c \
			redirection/rem_redir.c \
			redirection/open_files.c \
			execution/mod_execve.c \
			new_builtins/unset.c \
			new_builtins/export.c \
			new_builtins/env.c \
			env/ft_getenv.c

OBJ = $(SRC:.c=.o)
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
READLINE_LIB = -lreadline
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
CC				=	cc
RM 				=	rm -rf
CFLAGS			= 	-g -Wall -Wextra -Werror
all: $(LIBFT) $(NAME)
$(LIBFT):
	@make -C $(LIBFT_PATH)
	
$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(READLINE_LIB)
clean:
	@$(RM) $(OBJ)
	@make -C $(LIBFT_PATH) clean
fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean
re : fclean all
.PHONY: all fclean re bonus