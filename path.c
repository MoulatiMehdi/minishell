# include "execution.h"

char * ft_path_join(char * p1,char *p2)
{
    char * str;
    size_t len1;
    size_t len2;

    len1 = ft_strlen(p1);
    len2 = ft_strlen(p2);
    str = malloc(len1 + len2 + 2UL);
    if(str == NULL)
        return NULL;
    ft_memcpy(str,p1,len1);
    str[len1] = '/';
    ft_memcpy(&str[len1 + 1UL],p2,len2);
    str[len1 + len2 + 1UL] = '\0';
    return str;
}

bool ft_path_isdir(char * pathname)
{
    struct stat data;

    return (stat(pathname,&data) == 0 && S_ISDIR(data.st_mode));
}

bool ft_path_isfile(char * pathname)
{
    struct stat data;

    return (stat(pathname,&data) == 0 && !S_ISDIR(data.st_mode));
}

char ** ft_path_get()
{
    char * value;
    char ** strs;
    value = getenv("PATH");
    if(value == NULL)
        return NULL;
    strs = ft_split(value, ":");
    if(strs && strs[0] == NULL)
    {
        free(strs);
        strs = NULL;
    }
    return strs;
}

