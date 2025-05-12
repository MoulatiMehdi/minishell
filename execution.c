# include "execution.h"

int ft_execute_andor(t_ast * ast)
{
    if(ast == NULL)
        return 0;
    return 0;
}


int ft_execute_simplecommand(t_ast * ast)
{
    char ** args;
    int status; 
    if(ast == NULL)
        return 0;
    status = 0;
    args = ft_ast_getargs(ast); 
    if (args && ft_command_isbuildin(args[0]))
        status = ft_execute_buildin(ast->redirect, args);
    else 
        status = ft_execute_file(ast->redirect, args);
    free(args);
    return status;
}
