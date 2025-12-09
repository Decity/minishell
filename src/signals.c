/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:45:00 by elie              #+#    #+#             */
/*   Updated: 2025/12/09 11:34:00 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

/**
 * @brief Handle SIGINT (Ctrl+C) in interactive mode
 *
 * Clears the current readline input line and displays a new prompt.
 *
 * @param[in] sig Signal number
 */
void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Handle SIGINT (Ctrl+C) during command execution
 *
 * Prints a newline to display output properly.
 *
 * @param[in] sig Signal number
 */
void	handle_sigint_executing(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Configure signal handlers for interactive mode
 *
 * Sets up SIGINT handler to clear input line, ignores SIGQUIT.
 */
void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_interactive;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * @brief Configure signal handlers for command execution mode
 *
 * Sets up SIGINT handler for running commands, ignores SIGQUIT.
 */
void	setup_signals_executing(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_executing;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * @brief Restore default signal handlers
 *
 * Resets SIGINT and SIGQUIT to their default behavior.
 */
void	restore_signals_default(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}
