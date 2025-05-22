/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/22 19:42:50 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "expansion.h"
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

//	pipeline utils
//  void collect_cmds(t_ast *ast, t_ast **cmds, int ncmds);

int		ft_execute_simplecommand(t_ast *ast);
int		ft_execute_pipeline(t_ast *ast);
int		ft_execute_buildin(t_list *redirect, char **args);
int		ft_execute_file(t_list *redirect, char **args);
void	ft_exec_external(t_ast *cmd, char **args);

char	**ft_ast_getargs(t_ast *ast);
int		ft_command_isbuildin(char *str);

bool	ft_path_isdir(char *pathname);
bool	ft_path_isfile(char *pathname);
char	*ft_path_join(char *p1, char *p2);
char	**ft_path_get(void);

void	ft_perror(char *name, char *msg);
void	ft_token_error(t_token *token, char *msg);

void	ft_shell_interactive(void);
void	ft_shell_noninteractive(void);
int		ft_redirect(t_list *redirect);
void	ft_heredoc_sigint(int signal);

void	ft_signal_int(int signal);
void	ft_signal_child(void);
void	ft_signal_parent(void);
#endif
