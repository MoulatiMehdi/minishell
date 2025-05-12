#ifndef EXECUTION_H
#define EXECUTION_H


# include "expansion.h"
# include "config.h"
#include "libft.h"
#include "tokenizer.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
# include "libft.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

#include "libft.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void ft_signal_bashignore();
void ft_signal_init();

int ft_execute_simplecommand(t_ast * ast);
int ft_execute_buildin(t_list * redirect, char ** args);
int ft_execute_file(t_list * redirect,char ** args);

char ** ft_ast_getargs(t_ast * ast);
int ft_command_isbuildin(char * str);

bool ft_path_isdir(char * pathname);
bool ft_path_isfile(char * pathname);
char * ft_path_join(char * p1,char *p2);
char ** ft_path_get();

void ft_perror(char *name,char * msg);
void ft_token_error(t_token * token,char * msg);

unsigned char ft_shell_interactive();
unsigned char ft_shell_noninteractive();
#endif 
