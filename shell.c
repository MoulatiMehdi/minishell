/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:36:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft/libft.h"

t_ast			*ft_ast_simplecommand(t_token **token);

unsigned char	ft_shell_execute(char *str)
{
	t_token			*token;
	t_ast			*node;
	unsigned char	exit_code;

	if (str == NULL)
		return (0);
	token = tokenize(str);
	lexer(token);
	node = ft_ast_simplecommand(&token);
	exit_code = ft_execute_simplecommand(node);
	printf("status : %d\n", exit_code);
	ft_ast_free(node);
	return (exit_code);
}

unsigned char	ft_shell_interactive(void)
{
	char			*str;
	unsigned char	exit_code;

	exit_code = 0;
	rl_outstream = stderr;
	while (1)
	{
		ft_signal_bashignore();
		str = readline(SHELL_PROMPT);
		if (str == NULL)
			break ;
		exit_code = ft_shell_execute(str);
		if (*str)
			add_history(str);
		free(str);
		ft_clear();
	}
	rl_clear_history();
	write(2, "exit\n", 5);
	return (exit_code);
}

unsigned char	ft_shell_noninteractive(void)
{
	char			*str;
	unsigned char	exit_code;

    exit_code = 0;
    str = NULL;
    while (1)
    {
        str = get_next_line(STDIN_FILENO);
        if (str == NULL)
            break ;
        exit_code = ft_shell_execute(str);
        free(str);
    }
    get_next_line(-1);
    return exit_code;
}
