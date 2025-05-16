#include "config.h"
# include "execution.h"
#include "parser.h"
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int ft_redirect_dup(char *filename, t_token_type type)
{
    int fd;
    int fd_dup;

    fd = -1;
    fd_dup = STDOUT_FILENO;
    if(type == TOKEN_REDIRECT_IN)
    { 
        fd = open(filename,O_RDONLY); 
        fd_dup = STDIN_FILENO;
    }
    if(type == TOKEN_REDIRECT_OUT)
        fd = open(filename,O_WRONLY | O_CREAT | O_TRUNC , 0666); 
    if(type == TOKEN_REDIRECT_APPEND)
        fd = open(filename,O_WRONLY | O_CREAT | O_APPEND, 0666); 
    if(type == TOKEN_REDIRECT_HERE)
    {
        fd = ft_heredoc_tempfile(filename);
        fd_dup = STDIN_FILENO;
    }
    if(fd >= 0)
    {
        dup2(fd, fd_dup);
        close(fd);
    }
    return fd;
}

int ft_list_redirect(t_list * redirect)
{
    t_token * token;
    int status;

    while(redirect)
    {
        token = redirect->content;
        ft_token_expand(token);
        if(token->fields == NULL || token->fields->length != 1)
        {
            ft_token_error(token, "ambigious redirection");
            return 1;
        }
        if(ft_redirect_dup(token->fields->head->content,token->type) < 0)
        {
            status = errno;
            ft_token_error(token,strerror(status));
            return status;
        }
        redirect = redirect->next;
    }
    return 0; 
}


char * ft_command_search(char * name)
{
    char * ans;
    char * pathname;
    char ** strs;
    size_t i;
    
    i = 0;
    ans = NULL;
    strs = ft_path_get();
    if(strs == NULL)
        return NULL;
    while(strs[i])
    {
        pathname = ft_path_join(strs[i++],name);
        if(ft_path_isfile(pathname))
        {
            if(access(pathname, X_OK) == 0)
            {
                free(ans);
                ans = pathname;
                break;
            }
            else if(!ans)
                ans = pathname;
        }
        if(ans != pathname) 
            free(pathname);
    }
    ft_split_free(&strs);
    return ans; 
}

int ft_execute(t_list * redirect,char * pathname,char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if(pid < 0)
        perror(SHELL_NAME": fork");
    else if(pid == 0)
    {
        status = ft_list_redirect(redirect);
        if(status != 0)
            exit(status);
        if(!pathname)
        {
            ft_perror(args[0],"command not found");
            exit(127);
        }
        execve(pathname, args,NULL);
        if(ft_path_isdir(pathname))
            ft_perror(pathname,strerror(EISDIR));
        else
            ft_perror(pathname,strerror(errno));
        exit(126);
    }
    free(pathname);
    return pid;
}

int ft_execute_file(t_list * redirect,char ** args)
{
    char * path;
    pid_t pid;
    int wstatus;

    path = NULL;
    if(args)
    {
        if(ft_strchr(args[0],'/'))
            path = args[0];
        else
            path = ft_command_search(args[0]);
    }
    if(ft_execute(redirect,path,args) < 0)
        return 0;
    waitpid(-1, &wstatus, 0);
    if(WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if(WIFSIGNALED(wstatus))
        return WTERMSIG(wstatus) + 128;
    if(WIFSTOPPED(wstatus))
        return WSTOPSIG(wstatus) + 128;
    return 0;
}
