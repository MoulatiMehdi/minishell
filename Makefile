CC = cc 
AR = ar
RM = rm

CCFLAGS = -Wall -Wextra   -fsanitize=address -g
ARFLAGS = crs
RMFLAGS = -rf

DEPS = libft
LIBFT = $(DEPS)/libft.a 
SRCS = $(wildcard *.c) 
OBJS = $(SRCS:.c=.o)
NAME = tokenizer


all : $(NAME) 

$(NAME) : $(OBJS) $(LIBFT) 
	$(CC) $(CCFLAGS) $^ -o $@ -lft -Llibft  -lreadline $(addprefix -I,$(DEPS))
 
$(LIBFT) :  
		make -C libft --no-print-directory
%.o : %.c 
	$(CC) $(CCFLAGS) -g -c $< -o $@ $(addprefix -I,$(DEPS)) 

clean : 
	$(RM) $(RMFLAGS) $(OBJS)
	make clean -C libft --no-print-directory

fclean : clean 
	$(RM) $(RMFLAGS) $(NAME)
	make fclean -C libft --no-print-directory

re : fclean all

.PHONY : all fclean clean
.SECONDARY : $(OBJS)
