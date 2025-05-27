/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 09:25:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "config.h"
# include "expansion.h"
# include "libft.h"
# include "libft/libft.h"
# include "parser.h"
# include "status.h"
# include "tokenizer.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_pipe_ctx
{
	int		in_fd;
	pid_t	last_pid;
}			t_pipe_ctx;

// pipeline utils:
int			count_cmds(t_ast *ast);
void		redirect_fds(int in_fd, int out_fd);
int			wait_for_all(pid_t last_pid);
void		run_pipeline(t_ast *ast, t_pipe_ctx *ctx);

int			ft_execute_simplecommand(t_ast *ast);
int			ft_execute_andor(t_ast *ast);
int			ft_execute_pipeline(t_ast *ast);
int			ft_execute_buildin(t_list *redirect, char **args);
int			ft_execute_file(t_list *redirect, char **args);

char		*ft_command_search(char *name);

void		ft_ast_expand(t_ast *ast);
char		**ft_ast_getargs(t_ast *ast);
int			ft_command_isbuildin(char *str);

void		ft_shell_interactive(void);
void		ft_shell_noninteractive(void);
bool		ft_shell_isinteractive(void);

int			ft_redirect(t_list *redirect);

void		ft_signal_child(void);
void		ft_signal_parent(void);

void		ft_sigint_heredoc(int signal);
void		ft_sigint_noiteractive(int signal);
void		ft_sigint_heredoc(int signal);
void		ft_sigint_prompt(int signal);

bool		ft_path_isdir(char *pathname);
bool		ft_path_isfile(char *pathname);
char		*ft_path_join(char *p1, char *p2);
char		**ft_path_get(void);

void		ft_perror(char *name, char *msg);
void		ft_token_error(t_token *token, char *msg);
void		ft_command_execute(t_list *redirect, char *pathname, char **args);

void		ft_subshell_child(t_ast *ast, t_ast *child);

#endif
