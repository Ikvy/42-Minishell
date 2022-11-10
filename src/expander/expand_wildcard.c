#include <dirent.h>
#include "libft.h"

char **ft_new_size(char **cmd)

char	**ft_expand_wildcard(char **cmd, struct dirent *entry, DIR folder)
{
	char **ret;

	ret = ft_new_size(cmd);
}
