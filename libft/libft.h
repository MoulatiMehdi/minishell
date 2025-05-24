/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:10 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/03 18:11:48 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# define BUFFER_SIZE 1

# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_array
{
	size_t			length;
	t_list			*head;
	t_list			*last;
}					t_array;

char				*get_next_line(int fd);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
long				ft_stridx(char *str, char c);
char				*ft_strndup(const char *src, size_t n);

char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_strsdup(char **map);
char				*ft_strnjoin(char const *s1, char const *s2, size_t len);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strconcat(char **target, char const *str);
void				ft_strnconcat(char **target, char const *str, size_t len);
void				ft_free(void *addr);
void				*ft_malloc(size_t size);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstnew_track(void *content);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

char				*ft_strjoin_track(char const *s1, char const *s2);
char				*ft_strnjoin_track(char const *s1, char const *s2,
						size_t len);
char				*ft_strdup_track(const char *s1);
char				*ft_strndup_track(const char *src, size_t n);

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_list_strconcat(t_list *list, char *str);

void				ft_sorted_list_merge(t_list **head1, t_list *head2,
						int (*cmp)(void *s1, void *s2));
void				ft_sorted_list_insert(t_list **head, void *content,
						int (*cmp)(void *s1, void *s2));
void				ft_list_sort(t_list **head, int (*cmp)(void *s1, void *s2));

int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *s, int fd);
int					ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_split_free(char ***strs);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

void				*ft_calloc(size_t count, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strstr(char *str, char *to_find);
char				*get_next_line(int fd);
char				**ft_split(char const *s, char *charset);
char				**ft_strs_dup(char **map);

t_array				*ft_array_new(void);
void				*ft_array_push(t_array **array, void *content);

int					ft_clear(void);
void				ft_free(void *addr);
void				*ft_malloc(size_t size);
int					ft_strcmp(char *s1, char *s2);
void				*ft_collector_track(void *addr);
#endif
