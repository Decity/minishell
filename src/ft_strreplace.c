#include "../inc/minishell.h"

static void	replace(char *result, const char *base_str, const char *pattern, const char *replacement)
{
	size_t			i;
	size_t			j;
	size_t			k;
	const size_t	len_base = ft_strlen(base_str);
	const size_t	len_pattern = ft_strlen(pattern);

	i = 0;
	j = 0;
	while (i < len_base)
	{
		if (i <= len_base - len_pattern && ft_strncmp(&base_str[i], pattern, len_pattern) == 0)
		{
			k = 0;
			while (k < ft_strlen(replacement))
				result[j++] = replacement[k++];
			i += len_pattern;
		}
		else
			result[j++] = base_str[i++];
	}
}

/**
 * @brief Returns a new string by replacing @p `pattern` in @p `base_str` with @p `replacement`
 *
 * @param base_str The base string in which replacements will occur
 * @param pattern The pattern that will be replaced
 * @param replacement The string that will replace the pattern
 */
char	*ft_strreplace(const char *base_str, const char *pattern, const char *replacement)
{
	char	*result;
	size_t	len_base;
	size_t	len_pattern;
	size_t	len_replacement;
	size_t	len_result;

	if (!base_str || !pattern || !replacement)
		return (NULL);

	len_base = ft_strlen(base_str);
	len_pattern = ft_strlen(pattern);
	len_replacement = ft_strlen(replacement);

	if (len_pattern == 0)
		return (ft_strdup(base_str));

	len_result = len_base + ft_count_occurrences(base_str, pattern) * (len_replacement - len_pattern);

	result = ft_calloc(len_result + 1, sizeof(char));
	if (!result)
		return (NULL);

	replace(result, base_str, pattern, replacement);
	return (result);
}