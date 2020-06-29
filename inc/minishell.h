


#ifndef _MINISHELL_
#define _MINISHELL_

#include <stdbool.h>
#include "../alylibc/inc/lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// env.c

void    print_env(char **env);

// minishell.c

void    minishell(char **env);

// unsetenv.c

char    **run_unsetenv(char buffer[], char **env);
char    **ft_unsetenv(char **env, char *to_remove);

// setenv.c

char    **run_setenv(char buffer[], char **env);
char    **ft_setenv(char **env, char *to_add);

// cd.c

char    **run_cd(char buffer[], char **env);


#endif
