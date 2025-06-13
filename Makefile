CC = cc 
AR = ar
RM = rm

CCFLAGS = -Wall -Wextra -Werror
ARFLAGS = crs
RMFLAGS = -rf

DEPS = srcs/libft
LIBFT = $(DEPS)/libft.a 


SRCS = \
./srcs/tokenizer/token.c \
./srcs/tokenizer/tokenizer.c \
./srcs/tokenizer/token_char.c \
./srcs/tokenizer/token_unbalance.c \
./srcs/tokenizer/lexer.c \
./srcs/main.c \
./srcs/execution/execution_ast.c \
./srcs/execution/execution_file.c \
./srcs/execution/execution_args.c \
./srcs/execution/shell.c \
./srcs/execution/execution_pipeline.c \
./srcs/execution/execution_buildin.c \
./srcs/execution/execution_pipeline_utils.c \
./srcs/execution/ft_command_execute.c \
./srcs/execution/execution_redirect.c \
./srcs/expansion/expansion_pathname.c \
./srcs/expansion/expansion.c \
./srcs/expansion/expansion_diren.c \
./srcs/expansion/word_split.c \
./srcs/expansion/word.c \
./srcs/expansion/word_handle.c \
./srcs/expansion/expansion_fieldsplit.c \
./srcs/expansion/expansion_quotejoin.c \
./srcs/expansion/path.c \
./srcs/expansion/expansion_pattern.c \
./srcs/expansion/expansion_paramter.c \
./srcs/utils/env_value.c \
./srcs/utils/error.c \
./srcs/utils/env.c \
./srcs/utils/status.c \
./srcs/utils/env_utils.c \
./srcs/signal/signal.c \
./srcs/signal/signal_handler.c \
./srcs/parser/parser_ast.c \
./srcs/parser/ast.c \
./srcs/parser/heredoc.c \
./srcs/parser/parser_redirect.c \
./srcs/parser/parser.c \
./srcs/builtins/echo_cmd.c \
./srcs/builtins/unset_cmd.c \
./srcs/builtins/builtins_utils1.c \
./srcs/builtins/cd_cmd.c \
./srcs/builtins/env_cmd.c \
./srcs/builtins/builtins_utils.c \
./srcs/builtins/pwd_cmd.c \
./srcs/builtins/exit_cmd.c \
./srcs/builtins/export_cmd.c

HEADS = \
	./includes/builtins.h \
	./includes/config.h \
	./includes/env.h \
	./includes/execution.h \
	./includes/expansion.h \
	./includes/lexer.h \
	./includes/parser.h \
	./includes/status.h \
	./includes/tokenizer.h \
	./includes/tokenizer_init.h \
	./includes/word.h 

OBJS = $(SRCS:.c=.o)
NAME = minishell

all : $(NAME) 

$(NAME) : $(OBJS) $(LIBFT) 
	$(CC) $(CCFLAGS) $^ -o $@ -lft -L$(DEPS)  -lreadline -I$(DEPS) -I./includes/
 
$(LIBFT) :  
		@make -C $(DEPS) --no-print-directory
%.o : %.c $(HEADS) 
	$(CC) $(CCFLAGS) -c $< -o $@ -I$(DEPS) -I./includes/

clean : 
	$(RM) $(RMFLAGS) $(OBJS)
	@make clean -C $(DEPS) --no-print-directory

fclean : clean 
	$(RM) $(RMFLAGS) $(NAME)
	@make fclean -C $(DEPS) --no-print-directory

re : fclean all

.PHONY : all fclean clean re
.SECONDARY : $(OBJS)
