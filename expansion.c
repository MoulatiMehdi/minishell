/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/17 19:36:37 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"
#include "tokenizer_init.h"
#include "word.h"

<<<<<<< Updated upstream
extern char **environ;

int is_valid_var_name(char c)
{
	return (c == '_' || ft_isalpha(c));
}
int is_valid_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

char *get_env_value(const char *var_name, size_t len)
{
	int i;

	if (var_name == NULL || len <= 0)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}

void expand_param(t_word *word)
{
	size_t i;
	ssize_t len;

	if (word->type == WORD_QUOTE_SINGLE || word->type == WORD_WILDCARD)
		return;
	i = 0;
	len = 0;
	char *new_value = ft_calloc(1, 1);
	// ! example -> "Hello $USER"
	while (i < word->length)
	{
		len = 0;
		if (word->value[i] == '$' && is_valid_var_name(word->value[i + 1]))
		{
			i++;
			while (i + len < word->length && is_valid_char(word->value[len + i]))
				len++;
			ft_strconcat(&new_value, get_env_value(&word->value[i], len));
		}
		else
		{
			len++;
			while (i + len < word->length && word->value[i + len] && word->value[i + len] != '$')
				len++;
			ft_strnconcat(&new_value, &word->value[i], len);
		}
		i += len;
	}
	word->value = new_value;
	word->length = ft_strlen(new_value);
}

int is_joinable(t_word *word)
{
	size_t i;

	if (!word || word->type == WORD_WILDCARD)
	// TODO need to go back here for the wildcard char.
		return (0);
	i = 0;
	while (i < word->length)
	{
		if (ft_strchr(IFS, word->value[i]))
			return (0);
		i++;
	}
	return (1);
}


void join_quotes(t_word *head)
{
	t_word *curr = head;
	t_word *next;
	char *joined;

	while (curr && curr->next)
	{
		next = curr->next;
		if (is_joinable(curr) && is_joinable(next))
		{
			joined = ft_strjoin(curr->value, next->value);
			if (!joined)
				return;
			curr->value = joined;
			curr->length = ft_strlen(joined);
			curr->type = WORD_QUOTE_SINGLE;
			curr->next = next->next;
			ft_free((void *)next->value);
			ft_free(next);
		}
		else
			curr = curr->next;
	}
}

int is_ifs(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}
int is_field_splitting_required(t_word *word)
{
	size_t i;

	i = 0;
	if (!word || word->type != WORD_NONE)
		return 0;
	while (i < word->length)
	{
		if(is_ifs(word->value[i]))
			return 1;
		i++;
	}
	return 0;
}

int is_starting_with_ifs(const char *str)
{
	if (!str || !*str)
		return 0;
	return(is_ifs(*str));
}
int is_ending_with_ifs(const char *str, size_t len)
{
	if (len == 0)
		return(0);
	return (is_ifs(str[len - 1]));
}

static t_word *clone_word(t_word *src, const char *value, size_t len)
{
    t_word *dst = malloc(sizeof(*dst));
    if (!dst) return NULL;
    dst->type = src->type;
    dst->length = len;
    dst->value = strndup(value, len);
    dst->next = NULL;
    return dst;
}

void field_splitting(t_token *token, t_word *word)
{
    t_array *fields = NULL;
    t_list  *curr   = NULL;
    t_word  *w      = word;

    while (w)
    {
        if (w->type == WORD_QUOTE_SINGLE
         || w->type == WORD_QUOTE_DOUBLE
         || w->type == WORD_WILDCARD)
        {
            t_word *fw = clone_word(w, w->value, w->length);
            ft_lstadd_back(&curr, ft_lstnew(fw));
        }
        else
        {
            const char *s = w->value;
            size_t len    = w->length;
            size_t i = 0, start = 0;
            while (i < len)
            {
                if (is_ifs(s[i]))
                {
                    if (i > start)
                    {
                        t_word *fw = clone_word(w, s + start, i - start);
                        ft_lstadd_back(&curr, ft_lstnew(fw));
                    }
                    if (curr)
                    {
                        ft_array_push(&fields, curr);
                        curr = NULL;
                    }
                    while (i < len && is_ifs(s[i]))
                        i++;
                    start = i;
                }
                else
                {
                    i++;
                }
            }
            if (start < len)
            {
                t_word *fw = clone_word(w, s + start, len - start);
                ft_lstadd_back(&curr, ft_lstnew(fw));
            }
        }
        w = w->next;
    }
    if (curr)
        ft_array_push(&fields, curr);

    token->fields = fields;
}
static const char *word_type_str(t_word_type type)
{
    if (type == WORD_NONE)           return "NONE";
    if (type == WORD_QUOTE_SINGLE)   return "QUOTE_SINGLE";
    if (type == WORD_QUOTE_DOUBLE)   return "QUOTE_DOUBLE";
    if (type == WORD_WILDCARD)       return "WILDCARD";
    return "UNKNOWN";
}
int	should_expand_pathname(t_list *field)
{
	t_list	*node;
	t_word	*w;

	if (!field)
		return (0);
	node = field;
	while (node)
	{
		if (node->content)
		{
			w = node->content;
			if (w->type == WORD_WILDCARD)
				return (1);
		}
		node = node->next;
	}
	return (0);
}
void check_directory(const char *path)
{
	struct stat a;
	struct stat b;
	const char *dir_path = getcwd(NULL, 0);
	if (stat(path, &a) < 0)
		perror("stat a->");
	if (stat(dir_path, &b) < 0)
		perror("stat a->");
	
}
void to_fragments(t_word *w)
{
	t_word *curr;
	t_word *prev = NULL;
	curr = w;
	while (w)
	{
		prev = w;
		if (ft_strchr(prev->value, '/'))
			check_directory(prev->value);
		printf("[%s] ", w->value);
		printf("%s\n", word_type_str(w->type));
		w = w->next;
	}
	
	// printf("")
}

void pathname_expansion(t_token *token)
{
   t_list	*field_node;
	t_list	*frag_node;
	t_word	*w;

	if (!token || !token->fields)
		return ;
	field_node = token->fields->head;
	while (field_node)
	{
		frag_node = field_node->content;
		if (should_expand_pathname(frag_node))
		{
			while (frag_node)
			{
				if (frag_node->content)
				{
					to_fragments(frag_node->content);
				}
				frag_node = frag_node->next;
			}
		}
		field_node = field_node->next;
	}
=======
void ft_word_print(t_word * word,char * label)
{
    printf("\n*************************\n%s\n",label);
	while (word)
	{
        write(1,"- ", 2);
		write(1,word->value,word->length);
        write(1,"\n", 1);
        word = word->next;
	}

}

void print(void * p)
{
    t_list * lst;
    t_word * word;
    
    lst = p;
    while (lst)
    {
        word = lst->content;
        printf("- %s -> ",word->value);
        lst = lst->next;
    }
    printf("(NULL)\n");
>>>>>>> Stashed changes
}

void expand_token(t_token *token)
{
	t_word *token_words;
	t_word *tmp;

	token_words = ft_word_split(token);
	if (!token_words)
		return;
	tmp = token_words;
	while (tmp)
	{
		expand_param(tmp);
		tmp = tmp->next;
	}
    join_quotes(token_words);
    field_splitting(token, token_words);
	pathname_expansion(token);
}

