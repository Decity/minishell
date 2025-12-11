/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:57:35 by dbakker           #+#    #+#             */
/*   Updated: 2025/12/10 20:38:44 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compare two environment variable names for sorting.
 *
 * @param[in]	a	First string to compare.
 * @param[in]	b	Second string to compare.
 *
 * @return Negative if a < b, positive if a > b, zero if equal.
 */
static int	env_strcmp(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] && b[i] && a[i] != '=' && b[i] != '=')
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	if ((a[i] == '=' || a[i] == '\0') && (b[i] == '=' || b[i] == '\0'))
		return (0);
	if (a[i] == '=' || a[i] == '\0')
		return (-1);
	return (1);
}

static void	sort_env_array(char **arr, size_t count)
{
	size_t			i;
	size_t			j;
	char			*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (env_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Create a sorted array of environment variable strings.
 *
 * @param[in]	list	Linked list of environment variables.
 *
 * @return Null-terminated array of pointers to environment strings,
 * or NULL on failure.
 *
 * @warning Caller owns free().
 */
static char	**create_sorted_array(const t_list *list)
{
	char			**arr;
	size_t			count;
	size_t			i;
	const t_list	*tmp;

	count = 0;
	tmp = list;
	while (tmp && ++count)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list && i < count)
	{
		arr[i++] = (char *)list->content;
		list = list->next;
	}
	arr[i] = NULL;
	sort_env_array(arr, count);
	return (arr);
}

static void	print_export_var(const char *env_str)
{
	char	*value;
	size_t	namelen;

	ft_putstr_fd("export ", STDOUT_FILENO);
	if (ft_strchr(env_str, '='))
	{
		namelen = env_namelen(env_str);
		write(STDOUT_FILENO, env_str, namelen);
		write(STDOUT_FILENO, "=\"", 2);
		value = (char *)env_str + namelen + 1;
		ft_putstr_fd(value, STDOUT_FILENO);
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
		ft_putendl_fd(env_str, STDOUT_FILENO);
}

/**
 * @brief Print out all environmental variables to stdout in sorted order.
 *
 * Variables with values are printed as: export NAME="VALUE"
 * Variables without values are printed as: export NAME
 *
 * @param[in]	list	Linked list of environment variables.
 *
 * @retval 0 on success.
 * @retval 1 on allocation failure.
 */
int	export_print(const t_list *list)
{
	char	**sorted;
	size_t	i;

	sorted = create_sorted_array(list);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		print_export_var(sorted[i]);
		i++;
	}
	return (free(sorted), 0);
}
