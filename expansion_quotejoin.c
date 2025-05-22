#include "expansion.h"

int is_joinable(t_word *word)
{
	size_t i;

	if (!word || word->type == WORD_WILDCARD)
	// TODO need to go back here for the wildcard char.
		return (0);
	if (word->type == WORD_QUOTE_DOUBLE || word->type == WORD_QUOTE_SINGLE)
		return (1);
	i = 0;
	while (i < word->length)
	{
		if (ft_strchr(IFS"*", word->value[i]))
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
