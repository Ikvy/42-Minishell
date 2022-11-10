#include "libft.h"
#include <stdio.h> 

int	ft_findchar(char *str, char c)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (i);
}

void	is_deja_vu(int *tmp, int *i, char *exported, char **env)
{
	while (env[++(*i)])
	{
		if (!ft_strncmp(exported, env[*i], ft_findchar(exported, '=')) && ft_findchar(exported, '=') == ft_findchar(env[*i], '='))
			*tmp = 1;
	}
	if (*tmp)
		(*i)--;
}

char	**built_export(char	*exported, char	**env)
{
	int		i;
	int		tmp;
	char	**new_env;

	i = -1;
	tmp = 0;
	is_deja_vu(&tmp, &i, exported, env);
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
	{
		if (tmp && !ft_strncmp(exported, env[i], ft_findchar(exported, '=')) && ft_findchar(env[i], '=') == ft_findchar(exported, '='))
			new_env[i] = ft_strdup(exported);
		else
			new_env[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	if (!tmp)
		new_env[i++] = ft_strdup(exported);
	new_env[i] = 0;
	return (new_env);
}
