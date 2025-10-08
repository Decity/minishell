#include "../inc/minishell.h"

size_t	ft_count_occurrences(const char *base_str, const char *pattern)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i <= ft_strlen(base_str) - ft_strlen(pattern))
	{
		if (ft_strncmp(&base_str[i], pattern, ft_strlen(pattern)) == 0)
		{
			count++;
			i += ft_strlen(pattern);
		}
		else
			i++;
	}
	return (count);
}
