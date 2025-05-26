/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:47:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/23 17:56:51 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "libft/libft.h"
# include "word.h"
# include <readline/readline.h>
# include <signal.h>

typedef enum e_ast_type
{
	AST_AND_OR,
	AST_OR,
	AST_AND,
	AST_PIPE,
	AST_SIMPLE_COMMAND,
	AST_COMMAND,
	AST_PIPELINE,
	AST_SUBSHELL,
	AST_UNKNOWN,
}						t_ast_type;

typedef struct s_ast
{
	t_ast_type			type;
	t_list				*args;
	t_list				*redirect;
	t_list				*children;
}						t_ast;

t_ast					*ft_ast_new(t_ast_type ast_type);
t_ast					*ft_ast_andor(t_token **token);
t_ast					*ft_ast_redirect(t_token **token, t_ast *node);
t_ast					*parser(t_token *token);
char					*ft_heredoc(t_token *token, char *delimiter);
t_list					*ft_ast_push(t_ast *parent, t_ast *child);
int						ft_heredoc_tempfile(char *str);

volatile sig_atomic_t	*ft_sigint_recieved(void);
void					ft_signal_int(int signal);
void					ft_signal_quit(int signal);
void					ft_signal_bashignore(void);
void					ft_heredoc_sigint(int signal);
t_list					*ft_list_token_push(t_list **head, t_token *token);
void					ft_signal_noninteractive(void);
#endif // !PARSER_H
