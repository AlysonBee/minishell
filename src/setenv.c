


#include"../inc/minishell.h"


// setenv KEY=VALUE

char    **ft_setenv(char **env, char *to_add)
{
    int counter;
    char **values;
    char **key_value;
    bool checker;

    checker = false;
    values = split(to_add, '=');
    counter = 0;
    while (env[counter])
    {
        key_value = split(env[counter], '=');
        if (strcmp(key_value[0], values[0]) == 0)
        {
            checker = true;
            free(env[counter]);
            env[counter] = strdup(to_add);
            break;
        }
        counter++;
    }
    if (checker == false)
        env = arraypush(env, to_add);
    return (env);
}

char    **run_setenv(char buffer[], char **env)
{
    char **args;

    args = split(buffer, ' ');
    if (arraylen(args) == 2 && strchr(args[1], '='))
        env = ft_setenv(env, args[1]);
    else
        printf("You're shit (and nobody loves you)\n");
    return (env);
}

