/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelle <ebelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:15:33 by ebelle            #+#    #+#             */
/*   Updated: 2025/12/11 19:34:55 by ebelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*init_setup_head_node(void)
{
	char	*empty_node;
	t_list	*node;

	empty_node = ft_strdup("");
	if (empty_node == NULL)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	node = ft_listnew(empty_node);
	if (node == NULL)
	{
		free(empty_node);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (node);
}

/**
 * @brief Initialize shell data structure
 *
 * Sets up environment variables, current directory, checks if running
 * interactively, and configures signal handlers.
 *
 * @param[out] data Shell data structure to initialize
 */
void	init(t_data *data)
{
	extern const char	**environ;
	t_list				*node;

	node = init_setup_head_node();
	ft_bzero(data, sizeof(t_data));
	data->envp = array_to_llist(environ);
	ft_listadd_front(&data->envp, node);
	data->directory.pwd = getcwd(NULL, 0);
	if ((*environ && data->envp == NULL) || data->directory.pwd == NULL)
	{
		perror("minishell");
		exit_cleanup(data, EXIT_FAILURE);
	}
	setup_signals_interactive();
}

static void	set_prompt(t_data *data)
{
	if (data->exit_status)
		printf(PROMPT_ERROR_EXIT);
	data->input = readline(PROMPT_DEFAULT);
}

/**
 * @brief Read input from user or stdin
 *
 * Uses readline for interactive mode, get_next_line for pipes/files.
 * Exits on EOF, returns FAILURE for empty input, adds to history if valid.
 *
 * @param[in,out] data Shell data structure
 *
 * @return SUCCESS if valid input received, FAILURE if empty input
 */
uint8_t	set_input(t_data *data)
{
	size_t	len;

	set_prompt(data);
	if (g_signal == SIGINT)
	{
		data->exit_status = 130;
		g_signal = 0;
	}
	if (!data->input)
		exit_cleanup(data, 0);
	if (!data->input[0] || ft_strlen(data->input) == 0)
		return (free(data->input), FAILURE);
	len = 0;
	while (data->input[len] && ft_isspace(data->input[len]))
		len++;
	if (data->input[len] == '\0')
		return (free(data->input), FAILURE);
	add_history(data->input);
	return (SUCCESS);
}
