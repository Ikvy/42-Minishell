#include <limits.h> 
#include <dirent.h>
#include <stdio.h>
#include "libft.h"
#include "no_random_quote.h" 
#include "../lexer/lexer.h"

char	*ft_adjust(char *cmd, int i)
{
	char	*ret;
	int		size;

	size = -1;
	while (cmd[++size])
		;
	ret = malloc(sizeof(char) * size + 1);
	size = -1;
	while (cmd[++size] && i--)
		ret[size] = cmd[size];
	ret[size++] = 0;
	free(cmd);
	return (ret);
}

char	*ft_env_chr(char *var, char **env)
{
	int		i;
	char	*ret;
	int		var_len;

	var_len = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var + 1, var_len - 1)
			&& env[i][var_len - 1] == '=')
		{
			ret = ft_strdup(env[i] + var_len);
			return (ret);
		}
	}
	return (NULL);
}

char	*ft_find_var(char *cmd, int *i, int *j, char **env)
{
	char	*var;
	char	*ret;
	char	*tmp;
	int		k;

	tmp = NULL;
	k = -1;
	var = ft_calloc(sizeof(char), ARG_MAX);
	while (cmd[*i + 1] && cmd[*i + 1] != 0 && cmd[*i + 1] != '$'
		&& cmd[*i + 1] != ' ' && cmd[*i + 1] != '"')
		var[++k] = cmd[(*i)++];
	var[++k] = cmd[(*i)];
	ret = ft_env_chr(var, env);
	if (cmd[*i] && cmd[(*i)++ + 1] == '$')
	{
		free(var);
		var = ft_find_var(cmd, i, j, env);
		if (ret)
			tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, var);
		free(tmp);
	}
	free(var);
	return (ret);
}

char	*ft_join(char *ret, char *var, int *j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(ret);
	tmp2 = ft_strjoin(tmp, var);
	ft_strlcpy(ret, tmp2, ARG_MAX);
	free(tmp2);
	(*j) += ft_strlen(var);
	free(var);
	free(tmp);
	return (ret);
}

char	*ft_expand_var(char *cmd, char **env)
{
	int		i;
	int		j;
	char	*var;
	char	*ret;

	if (!cmd || !cmd[0])
		return (NULL);
	ret = ft_calloc(sizeof(char), ARG_MAX);
	if (!ret)
		return (NULL);
	i = 0;
	j = -1;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			var = ft_find_var(cmd, &i, &j, env);
			if (var)
				ret = ft_join(ret, var, &j);
		}
		else
			ret[++j] = cmd[i++];
	}
	return (ft_adjust(ret, j + 1));
}

char	**ft_expand(char **cmd, t_ctx *ctx)
{
	int		i;
	DIR		*folder;
	char	*cpy;
//	struct dirent *entry;

	i = -1;
	folder = opendir(".");
	if (folder == NULL)
    {
        printf("Unable to read directory\n");
        return(NULL);
    }
	while(cmd[++i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			cpy = ft_expand_var(cmd[i], ctx->env);
			free(cmd[i]);
			cmd[i] = ft_strdup(cpy);
			free(cpy);
		}
		if (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\''))
		{
			cpy = ft_no_random_quote(cmd[i]);
			free(cmd[i]);
			cmd[i] = ft_strdup(cpy);
			free(cpy);
		}
/*		if (ft_strchr(cmd[i], '*'))
			cmd[i] = ft_expand_wildcard(cmd[i], entry, folder);
*/	}
	closedir(folder);
	return (cmd);
}
