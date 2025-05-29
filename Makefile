CC = cc 
AR = ar
RM = rm

CCFLAGS = -Wall -Wextra -Werror  -g
ARFLAGS = crs
RMFLAGS = -rf

DEPS = libft
LIBFT = $(DEPS)/libft.a 
SRCS = \
	ast.c \
	builtins_utils.c \
	builtins_utils1.c \
	cd_cmd.c \
	echo_cmd.c \
	env.c \
	env_cmd.c \
	env_utils.c \
	env_value.c \
	error.c \
	execution_args.c \
	execution_ast.c \
	execution_buildin.c \
	execution_file.c \
	execution_pipeline.c \
	execution_pipeline_utils.c \
	execution_redirect.c \
	exit_cmd.c \
	expansion.c \
	expansion_diren.c \
	expansion_fieldsplit.c \
	expansion_paramter.c \
	expansion_pathname.c \
	expansion_pattern.c \
	expansion_quotejoin.c \
	export_cmd.c \
	ft_command_execute.c \
	heredoc.c \
	lexer.c \
	main.c \
	parser.c \
	parser_ast.c \
	parser_redirect.c \
	path.c \
	pwd_cmd.c \
	shell.c \
	signal.c \
	signal_handler.c \
	status.c \
	token.c \
	token_char.c \
	token_unbalance.c \
	tokenizer.c \
	unset_cmd.c \
	word.c \
	word_handle.c \
	word_split.c 
HEADS = \
	builtins.h \
	config.h \
	env.h \
	execution.h \
	expansion.h \
	lexer.h \
	parser.h \
	status.h \
	tokenizer.h \
	tokenizer_init.h \
	word.h 

OBJS = $(SRCS:.c=.o)
NAME = minishell

all : $(NAME) 

$(NAME) : $(OBJS) $(LIBFT) 
	$(CC) $(CCFLAGS) $^ -o $@ -lft -Llibft  -lreadline -I$(DEPS)
 
$(LIBFT) :  
		make -C libft --no-print-directory
%.o : %.c $(HEADS) 
	$(CC) $(CCFLAGS) -c $< -o $@ -I$(DEPS) 

clean : 
	$(RM) $(RMFLAGS) $(OBJS)
	make clean -C libft --no-print-directory

fclean : clean 
	$(RM) $(RMFLAGS) $(NAME)
	make fclean -C libft --no-print-directory

re : fclean all

.PHONY : all fclean clean re sanitize
.SECONDARY : $(OBJS)
