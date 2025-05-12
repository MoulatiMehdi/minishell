# include "execution.h"

int ft_command_isbuildin(char * str)
{
    size_t i;
    static char *buildins[] = {
        "echo",
        "env",
        "pwd",
        "unset",
        "export",
        "cd",
        "exit",
        NULL,
    };

    i = 0;
    while(buildins[i])
    {
        if(strcmp(buildins[i],str) == 0)
            return 1;
        i++;
    }
    return 0;
}

int ft_execute_buildin(t_list * redirect, char ** args)
{

    // TODO: CALL BUILDIN FUNCTIONS 
    ft_putstr_fd("\033[1;93m======================= UNDER DEVOLOPEMENT ==========================\033[0m\n",1);
    return 0;
}
