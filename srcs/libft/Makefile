CC = cc 
AR = ar

CFLAGS = -Wall -Wextra -Werror -g
ARFLAGS = crs

SRCS = \
ft_array.c \
ft_array_remove.c \
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_collector.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_list_remove_if.c \
ft_list_sort.c \
ft_list_strconcat.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstremove.c \
ft_lstsize.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_sorted_list_insert.c \
ft_sorted_list_merge.c \
ft_split.c \
ft_strchr.c \
ft_strcmp.c \
ft_strconcat.c \
ft_strdup.c \
ft_stridx.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strsdup.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c

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
