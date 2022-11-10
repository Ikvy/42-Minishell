#include "libft.h"
#include <stdio.h>

void	ft_count(int *counter, int *state, int quote_type)
{
	(*counter)++;
	if (*counter % 2 != 0)
		*state = quote_type;
	else
		*state = 0;
}

int	ft_malloc_without_quotes(char *cmd)
{
	int	count_squotes;
	int	count_dquotes;
	int	state;
	int	i;

	state = 0;
	count_dquotes = 0;
	count_squotes = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && state != 2)
			ft_count(&count_squotes, &state, 1);
		else if (cmd[i] == '"' && state != 1)
			ft_count(&count_dquotes, &state, 2);
	}
	return (count_dquotes + count_squotes);
}

void	ft_skip(int new_state, int *state)
{
	if (*state == new_state)
		*state = 0;
	else
		*state = new_state;
}

char	*ft_no_random_quote(char *cmd)
{
	char	*ret;
	int		state;
	int		i;
	int		j;

	state = 0;
	j = -1;
	i = 0;
	ret = malloc(sizeof(char)
			* (ft_strlen(cmd) - ft_malloc_without_quotes(cmd) + 1));
	while (cmd[i])
	{
		if (cmd[i] == '\'' && state != 2)
			ft_skip(1, &state);
		else if (cmd[i] == '"' && state != 1)
			ft_skip(2, &state);
		else
			ret[++j] = cmd[i];
		if (cmd[i])
			i++;
	}
	ret[j + 1] = 0;
	return (ret);
}
