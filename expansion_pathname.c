# include "expansion.h"

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
}
