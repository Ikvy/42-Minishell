#include <stdio.h>
#include "libft.h"

//opt 1 = export
//opt 0 = env

void	built_env(char **env, int opt)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (opt)
			{
				printf("declare -x ");
				printf("%s", env[i]);
				printf("\n");
			}
			else if (ft_strchr(env[i], '=') || opt)
			{
				printf("%s", env[i]);
				if (!ft_strchr(env[i], '='))	
					printf("=''");
				printf("\n");
			}
			i++;
		}
	}
}
