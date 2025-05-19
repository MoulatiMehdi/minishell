/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/22 11:20:45 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"
#include "debug.h"
#include "libft/libft.h"
#include "parser.h"
#include <readline/readline.h>
#include <string.h>

t_ast	*ft_ast_simplecommand(t_token **token);
char	**ft_ast_getargs(t_ast *ast);


t_array * ft_env_create(char ** strs)
{
    size_t i;
    char * tmp;
    t_array * array;

    array= NULL;
    i = 0;
    while(strs[i])
    {
        tmp = ft_strdup(strs[i]);
        ft_collector_track(tmp);
        ft_array_push(&array,tmp);
        i++;
    }
    return array;
}

void ft_field_push(t_token * token)
{

    char * str;

    while(token)
    {
        str = ft_strndup(token->value,token->length);
        ft_collector_track(str);
        ft_array_push(&token->fields,str);
        token = token->next;
    }
}

int	main(int argc,char **argv,char **envp)
{

    t_token	*token;
    t_ast * node;
    char	*str;
    char ** strs;
    t_cmd cmd;
   
    (void) argv;
    (void) argc;
    ft_signal_bashignore();
    setvbuf(stdout, NULL, _IONBF, 0);
    rl_outstream = stderr;
    while (1)
    {
        str = readline(" \033[32mMinishell\033[0m\033[31m>\033[0m ");
        if (str == NULL)
            break ;
        token = tokenize(str);
        lexer(token);
        ft_field_push(token);
        node = ft_ast_simplecommand(&token);
        strs = ft_ast_getargs(node);
        if(strs != NULL)
        {
            cmd.name = strs[0];
            cmd.args = &strs[1];
            cmd.env = ft_env_create(envp);
           
            if(ft_strcmp(cmd.name,"echo") == 0)
                echo_cmd(&cmd);
            if(ft_strcmp(cmd.name,"cd") == 0)
                cd_cmd(&cmd);
            if(ft_strcmp(cmd.name,"unset") == 0)
                unset_cmd(&cmd);
            if(ft_strcmp(cmd.name,"exit") == 0)
                exit_cmd(&cmd,0);
            if(ft_strcmp(cmd.name,"pwd") == 0)
                pwd_cmd(&cmd);
            if(ft_strcmp(cmd.name,"env") == 0)
                env_cmd(&cmd);
            if(ft_strcmp(cmd.name,"export") == 0)
                export_cmd(&cmd);
        }
        /*ft_clear();*/
    }
    return (0);
}
