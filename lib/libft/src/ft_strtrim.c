/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:13 by ebelle            #+#    #+#             */
/*   Updated: 2025/04/29 12:38:12 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static int	in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (in_set(s1[start], set) && s1[start])
		start++;
	while (end > start && in_set(s1[end - 1], set))
		end--;
	str = ft_calloc((end - start + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 1);
	return (str);
}

// int main(void)
// {
//     const char *tests[] = {
//         "   Hello, World!   ",
//         "---Hello---",
//         "   ",
//         "",
//         "abcHelloabc",
//         "abcabcabc",
//         NULL
//     };
//     const char *sets[] = {
//         " ",
//         "-",
//         " ",
//         " ",
//         "abc",
//         "abc",
//         NULL
//     };

//     for (int i = 0; tests[i]; i++)
//     {
//         const char *s1 = tests[i];
//         const char *set = sets[i];
//         char *result = ft_strtrim(s1, set);

//         printf("Test: %u\n", i + 1);
//         printf("  Str: \"%s\"\n", s1);
//         printf("  Set: \"%s\"\n", set);
//         printf("  Result: \"%s\"\n\n", result);

//         free(result);
//     }

//     return 0;
// }