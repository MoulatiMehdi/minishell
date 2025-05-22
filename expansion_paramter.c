# include "expansion.h"

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
    extern char **environ;

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
