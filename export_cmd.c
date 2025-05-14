#include "builtins.h"
#include <stdlib.h>
#include <string.h>

int print_export(t_array *env)
{
    if (!env)
        return (1);
    t_list *curr = env->head;
    while (curr)
    {
        printf("declare -x %s\n", (char *)curr->content);
        curr = curr->next;
    }
    return (0);
}



int is_valid_var_name(char c)
{
    return (c == '_' || ft_isalpha(c));
}

int is_valid_char(char c)
{
    return (c == '_' || ft_isalnum(c));
}

int is_valid_identifier(const char *var)
{
    int i;
    if (!var || var[0] == '\0')
        return (0);
    if (!is_valid_var_name(var[0]))
        return (0);
    i = 1;
    while (var[i] && var[i] != '=')
    {
        if (!is_valid_char(var[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_add_env(char *key, char *value, t_array *env)
{
    char *prefix;
    char *kv;

    if (!key || !value)
        return;
    prefix = ft_strjoin(key, "=");
    free(key);
    kv = ft_strjoin(prefix, value);
    free(prefix);
    free(value);
    ft_array_push(&env, kv);
}


void ft_update_env(char *key, char *value, t_array *env)
{
    t_list *node;
    char *prefix;
    char *new_var;

    if (!key || !value || !env)
        return;
    node = ft_get_env(key, env);
    if (node)
    {
        prefix = ft_strjoin(key, "=");
        if (!prefix)
        {
            free(key);
            free(value);
            return;
        }
        new_var = ft_strjoin(prefix, value);
        free(prefix);
        free(node->content);
        node->content = new_var;
        free(key);
        free(value);
    }
    else
        ft_add_env(key, value, env);
}

void print_export_error(char *arg)
{
    if (!arg)
        return;
    ft_putstr_fd("export: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putendl_fd(": not a valid identifier", 2);
}

int ft_is_var_exist(char *var, t_array *env)
{
    char   *key;
    t_list *node;
    int     exists;

    if (!var || !env)
        return (1);
    key = get_var_key(var);          
    if (!key)
        return (1);
    node   = ft_get_env(key, env);   
    exists = (node == NULL);         
    free(key);
    return (exists);
}


int export_cmd(t_cmd *cmd)
{
    int     (i), (status);
    char    (*arg),(*key), (*value);

    if (!cmd)
        return (1);
    if (!cmd->args)
        return (print_export(cmd->env));
    status = 0;
	i = 0;
    while (cmd->args[i])
    {
        arg = cmd->args[i];
        if (!is_valid_identifier(arg))
        {
            print_export_error(arg);
            status = 1;
        }
		else{
			key = get_var_key(arg);
			value = get_var_value(arg);
			if (!value)
            value = ft_strdup("");
			if (ft_is_var_exist(arg, cmd->env))
            ft_add_env(key, value, cmd->env);
			else
            ft_update_env(key, value, cmd->env);
		}
		i++;
    }
    return (status);
}
