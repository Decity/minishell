#include "../inc/minishell.h"

// Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames
// (see Filename Expansion) and commands and arguments.

// Welcome to Leak-City

/**
 * @brief Performs the shell expansions
 *
 * - Expands the env variables
 * - Expands tilde
 * - Removes quotation marks
 */
void	set_shell_expansions(t_data *data)
{
	char	**arguments;
	size_t	i;

	if (DEBUG)
		printf("=== set_shell_expansions ===\n\n");

	i = 0;
	arguments = data->command->arguments;
	while (arguments[i])
	{
		expand_env_parameter(&arguments[i]);
		expand_tilde(&arguments[i]);
		remove_quotation(&arguments[i]);
		i++;
	}


	if (DEBUG)
	{
		printf("== After expansions: \n");
		printf("= args: %li\n", i);
		i = 0;
		while (arguments[i])
			printf("= [%li] %s\n", i, arguments[i]), i++;
		printf("=== END SHELL_EXPANSIONS ===\n\n");
	}
}

void	expand_env_parameter(char **str)
{
	size_t	i;
	bool	inside_single_quotes;

	inside_single_quotes = false;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
			inside_single_quotes = !inside_single_quotes;

		if (inside_single_quotes == false && (*str)[i] == '$' && is_valid_parameter(&(*str)[i])) // TODO: Is having both arg 2 and 3 in conditional worth it?
		{
			i += do_the_actual_expansion(str);
			// TODO: Handle error
		}
		i++;
	}
}

size_t	do_the_actual_expansion(char **str)
{
	char *parameter_var;
	char *parameter_name;
	char *parameter_value;
	char *new_parameter;

	parameter_var = get_parameter_var(*str);
	if (parameter_var == NULL)
		return (-1);

	parameter_name = get_parameter_name(parameter_var);
	if (parameter_name == NULL)
		return (free_and_null(&parameter_var), -1);

	parameter_value = getenv(parameter_name);
	if (parameter_value == NULL)
		return (free_and_null(&parameter_var), free_and_null(&parameter_name), -1);

	// Rewrite the str with the replacements
	new_parameter = ft_strreplace(*str, parameter_var, parameter_value);
	if (new_parameter == NULL)
		return (free_and_null(&parameter_var), free_and_null(&parameter_name), free_and_null(&parameter_value), -1);

	ft_repoint(str, new_parameter);

	return (ft_strlen(parameter_value));
}

char	*get_parameter_var(const char *str)
{
	size_t	i;
	size_t	end;
	char	*result;

	if (!str)
		return (NULL);
	i = 2;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] != '}')
		return (NULL);
	end = i + 1;
	result = (char *)malloc(end + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < end)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	expand_tilde(char **str)
{
	const char	*temp_home = "/home/team_unicode_whitespace";

	char *new_str = ft_strreplace(*str, "~", temp_home);
	ft_repoint(str, new_str);
}

bool	is_valid_parameter(const char *str)
{
	size_t	i;

	if (!str || ft_strlen(str) < 4 || str[0] != '$' || str[1] != '{')
		return (false);
	i = 2;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] == '}')
		return (true);
	return (false);
}

char	*get_parameter_name(const char *str)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*parameter_name;

	i = 2;
	start = i;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] != '}')
		return (NULL);
	end = i;
	parameter_name = ft_calloc(end - start + 1, sizeof(char));
	if (!parameter_name)
		return (NULL);
	i = 0;
	while (start < end)
		parameter_name[i++] = str[start++];
	return (parameter_name);
}

void	remove_quotation(char **str)
{
	char	*str_without_single_quotes;
	char	*str_without_either_quotes;

	str_without_single_quotes = ft_strreplace(*str, "\'", "");
	str_without_either_quotes = ft_strreplace(str_without_single_quotes, "\"", "");
	free_and_null(&str_without_single_quotes);
	ft_repoint(str, str_without_either_quotes);
}
