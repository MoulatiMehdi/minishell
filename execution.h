#ifndef EXECUTION_H
#define EXECUTION_H


# include "libft.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
    pid_t pid;
    int fd[2];
    t_ast * node;
    char ** envp; 
    char ** args;
    unsigned char exist_status;
} t_cmd;



int ft_execute_simplecommand(t_ast * ast);
#endif 
