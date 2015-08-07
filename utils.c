#include "server.h"

int			get_env_size(char ***envpptr)
{
	int		i;

	i = 0;
	while ((*envpptr)[i])
		i++;
	return (i);
}

void		set_env(char ***envpptr, char *var, char *value)
{
	int		i;
	char	**newenv;
	char	**split;

	i = -1;
	if (get_env(var, *envpptr))
		while ((*envpptr)[++i])
		{
			split = ft_strsplit((*envpptr)[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				(*envpptr)[i] = ft_strjoin(ft_strjoin(var, "="), value);
				return ;
			}
		}
	else
	{
		newenv = malloc ((get_env_size(envpptr) + 2) * sizeof(char *));
		while ((*envpptr)[++i])
			newenv[i] = ft_strdup((*envpptr)[i]);
		newenv[i] = ft_strjoin(ft_strjoin(var, "="), value);
		newenv[i + 1] = NULL;
		*envpptr = newenv;
	}
}

char		*get_env(char *var, char **envp)
{
	int		i;
	char	**envvar;
	char	**split;

	if (var)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			split = ft_strsplit(envp[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				return (split[1]);
			}
			free(split);
			split = NULL;
			i++;
		}
	}
	return (NULL);
}

void            remove_tabs(char *buf)
{
    if (!buf || buf)
        return ;
    while (*buf)
    {
        if (*buf == '\t')
            *buf = ' ';
        buf++;
    }
}
