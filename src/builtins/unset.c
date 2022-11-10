#include "libft.h"
#include "builtin.h"
#include <stdio.h>

int	ft_is_setted(char **env, char *unseted, int	*i)
{
	int	exist;

	if (ft_strchr(unseted, '='))
		return (-1);
	exist = 0;
	*i = -1;
	while (env[++(*i)])
	{
		if (!ft_strncmp(unseted, env[*i], ft_findchar(unseted, '=')) && ft_findchar(env[*i], '=') == ft_findchar(unseted, '='))
			exist = 1;
	}
	return (exist);
}

char	**ft_unset_env(char **env, char *unseted, int i)
{
	int	exist;
	char	**new_env;

	exist = 0;
	new_env = malloc(sizeof(char *) * i);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(unseted, env[i], ft_findchar(unseted, '=')))
			new_env[i - exist] = ft_strdup(env[i]);
		else
			exist++;
		free(env[i]);
	}
	free(env);
	new_env[i - exist] = 0;
	return (new_env);
}

char	**built_unset(char	*unseted, char **env)
{
	char	**new_env;
	int		i;
	int		exist;

	i = 0;
	new_env = NULL;
	exist = ft_is_setted(env, unseted, &i);
	if (exist < 0)
	{
		printf("minishell: unset: `%s': not a valid identifier\n", unseted);
		return (env);
	}
	if (exist)
	{
		new_env = ft_unset_env(env,  unseted, i);
		return (new_env);
	}
	return (env);
}
