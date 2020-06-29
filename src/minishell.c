
#include "../inc/minishell.h"


void    read_line(char buffer[])
{
    size_t size;
    
    bzero(buffer, 4096);
    size = read(0, buffer, 4096);
    if (size >= 4096)
        buffer[4095] = '\0';
    buffer[size - 1] = '\0'; 
}

void    minishell(char **env)
{
    char buffer[4096];

    while (42)
    {
        write(1, "$>", 2);
        read_line(buffer);
        if (strlen(buffer) == 0 || buffer[0] == '\n')
            continue ;
        if (strncmp(buffer, "unsetenv ", 9) == 0)
            env = run_unsetenv(buffer, env); 
        else if (strcmp(buffer, "env") == 0)
            print_env(env);
        else if (strncmp(buffer, "setenv ", 7) == 0)
            env = run_setenv(buffer, env);
        else if (strcmp(buffer, "cd") == 0 || strncmp(buffer, "cd ", 3) == 0)
            env = run_cd(buffer, env);
    }
}




