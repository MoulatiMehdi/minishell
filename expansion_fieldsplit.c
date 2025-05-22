# include "expansion.h"

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
    dst->value = ft_strndup(value, len);
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
