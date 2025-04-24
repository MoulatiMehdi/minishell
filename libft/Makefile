CC = cc 
AR = ar

CFLAGS = -Wall -Wextra -Werror
ARFLAGS = crs

SRCS = \
ft_array.c      ft_isdigit.c       ft_lstdelone.c  ft_lstsize.c    ft_striteri.c  ft_strmapi.c\
ft_collector.c  ft_isprint.c       ft_lstiter.c    ft_strchr.c     ft_strjoin.c   ft_strncmp.c\
ft_isalnum.c    ft_lstadd_back.c   ft_lstlast.c    ft_strconcat.c  ft_strlcat.c   ft_strnstr.c\
ft_isalpha.c    ft_lstadd_front.c  ft_lstmap.c     ft_strdup.c     ft_strlcpy.c   ft_strrchr.c\
ft_isascii.c    ft_lstclear.c      ft_lstnew.c     ft_stridx.c     ft_strlen.c    ft_strsdup.c
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
