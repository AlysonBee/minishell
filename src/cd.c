


#include "../inc/minishell.h"

char    *create_new_env(char *key, char *value)
{
    char *temp;
    char *second;

    temp = join(key,"=");
    second = join(temp, value);
    free(temp);
    return (second);
}


char    **swap(char **env, int first, int second)
{
    char *temp;
    char *fkey;
    char *skey;
    char **key_value;
    char **key_value2;

    key_value = split(env[first], '=');
    key_value2 = split(env[second], '=');
    fkey = create_new_env(key_value[0], key_value2[1]);
    skey = create_new_env(key_value2[0],key_value[1]);
    env[first] = fkey;
    env[second] = skey;
    temp = fkey;
    return (env);
}

char    **switch_env(char **env, char *target, char *source)
{
    int first;
    int second;
    int counter;
    char **key_value;

    counter = 0;
    while (env[counter])
    {
        key_value = split(env[counter], '=');
        if (strcmp(target, key_value[0]) == 0)
            first = counter;
        else if (strcmp(source, key_value[0]) == 0)
            second = counter;
       free2d(key_value);
       counter++;
    }
    env = swap(env, first, second);
    return (env);
}

void    print_pwds(char **env)
{
    int i = 0;
    while (env[i])
    {
        if (strncmp(env[i], "PWD", 3) == 0 || strncmp(env[i], "OLDPWD", 6) == 0)
            printf("%s\n", env[i]);
        i++; 
    }
}

char    **set_pwd(char **env)
{
    char pwd[4096];
    char *new_pwd;

    bzero(pwd, 4096);
    getcwd(pwd, 1024);

    new_pwd = create_new_env("PWD", pwd);
   // env = ft_unsetenv(env, "PWD");
    env = ft_setenv(env, new_pwd);
    return (env);
}

char    **return_home(char **env)
{
    int     counter;
    char    **key_value;
    bool    checker;

    checker = false;
    counter = 0;
    while (env[counter])
    {
        key_value = split(env[counter], '=');
        if (strcmp(key_value[0], "HOME") == 0)
        {
            chdir(key_value[1]);
            free2d(key_value);
            env = switch_env(env, "PWD", "OLDPWD");
            env = set_pwd(env); 
            checker = true;
            break;
        }
        free2d(key_value);
        counter++;
    }
    if (checker == false)
        printf("Error : HOME not set\n");
    return (env);
}

char    **change_directory(char **env, char *dir)
{
    char *value;
    char curr[1024];
    char *tmp;

    bzero(curr, 1024);
    getcwd(curr, 1024);
    env = switch_env(env, "PWD", "OLDPWD");
    value = create_new_env("PWD", curr);
    env = ft_setenv(env, value);
    return (env);
}

char    **oldpwd_to_pwd(char **env)
{
    int counter;
    char **key_value;
    bool    checker;

    checker = false;
    counter = 0;
    while (env[counter])
    {
        key_value = split(env[counter], '=');
        if (strcmp(key_value[0], "OLDPWD") == 0)
        {
            if (chdir(key_value[1]) == 0)
                checker = true;
            free2d(key_value);
            break ;
        }
        free2d(key_value);
        counter++;
    }
    if (checker == true)
        env = switch_env(env, "PWD","OLDPWD");
    return (env);
}

char    **go_back(char **env)
{
    char *back_pwd;
}

char    **run_cd(char buffer[], char **env)
{
    char    **args;
    char    *repl;

    args = split(buffer, ' ');
    if (arraylen(args) == 1)
    {
        env = return_home(env);
        print_pwds(env);
    }
    else
    {
        if (strcmp(args[1], "~") == 0 || strcmp(args[1], "~/") == 0)
        {
            repl = replace(args[1], "~", "/Users/alysonngonyam");
            chdir(repl);
        }
        else if (strcmp(args[1], "-") == 0)
            env = oldpwd_to_pwd(env);
        else if (strcmp(args[1], "..") == 0 || strcmp(args[1], "../") == 0)
            env = go_back(env);
        else
        {
            if (chdir(args[1]) != 0)
                printf("Error : you really do suck ma'guy\n");
            else
                env = change_directory(env, args[1]);
        }
    }
    free2d(args);
    return (env);
}
