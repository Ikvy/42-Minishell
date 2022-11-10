#include <stdio.h>
#include "libft.h"

void	built_pwd(char **env)
{
	int	i;

	i = -1;
	if (env)
	{
		while (ft_strncmp(env[++i], "PWD=", 4) && env[i]);
		printf("%s\n", env[i] + 4);
	}
}
