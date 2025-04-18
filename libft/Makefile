CC = cc 
AR = ar

CFLAGS = -Wall -Wextra -Werror
ARFLAGS = crs

SRCS = \
	ft_lstadd_back.c   ft_lstclear.c   ft_lstiter.c  ft_lstmap.c  ft_lstsize.c \
	ft_lstadd_front.c  ft_lstdelone.c  ft_lstlast.c  ft_lstnew.c
OBJS = $(SRCS:.c=.o)


NAME = libft.a

all : $(NAME)

%.o : %.c libft.h
	$(CC) $(CFLAGS) $< -c -o $@

$(NAME) : $(OBJS) 
	$(AR) $(ARFLAGS) $(NAME) $?

clean : 
	rm -rf $(OBJS) 
fclean : clean 
	rm -rf $(NAME)

re : fclean all

.SECONDARY : $(OBJS)
.PHONY : all clean fclean re
