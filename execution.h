/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:23 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "expansion.h"
# include "config.h"
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

void	ft_signal_bashignore(void);
void	ft_signal_init(void);

int		ft_execute_simplecommand(t_ast *ast);
int		ft_execute_buildin(t_list *redirect, char **args);
int		ft_execute_file(t_list *redirect, char **args);

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
void	ft_signal_int(int signal);
int		ft_redirect(t_list *redirect);
void	ft_heredoc_sigint(int signal);
#endif
