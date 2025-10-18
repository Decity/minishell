#include "minishell.h"

// TODO: check if inside quotes
int	validate_token_str(char *str)
{
	size_t	i;
	size_t	count_consecutive;
	uint8_t	curr;
	uint8_t	next;

	i = 0;
	count_consecutive = 0;
	while (str[i])
	{
		curr = get_token_type(&str[i]);
		next = get_token_type(&str[i + 1]);

		if (is_redirection(&str[i]))
		{
			count_consecutive++;

			if (next == TYPE_PIPE)
				return (FAILURE);
			
			// Check if redirection has a target
			if (has_redirection_target(&str[i]) == false)
				return (FAILURE);

			// Check if the there's a mismatch in symbols. i.e.: >< or <> 
			if (get_redirection_type(&str[i + 1]) && curr != next)
				return (FAILURE);

			// Check if there's three redirection tokens in a row
			if (count_consecutive == 3)
				return (FAILURE);
		}
		else if (curr == TYPE_PIPE && has_redirection_target(&str[i]) == false)
			return (FAILURE);
		else
			count_consecutive = 0;

		i++;
	}
	return (SUCCESS);
}

/**
*	@brief Checks whether the current redirection has a target (i.e. in or outfile to redirect to)
*/
bool	has_redirection_target(char *str)
{
	size_t	i;

	i = 1;
	// Skip the redirection token(s)
	while (str[i] && is_redirection(&str[i]))
		i++;
	// Skip whitespace
	while (str[i] && ft_isspace(str[i]))
		i++;
	
	if (str[i] && (get_redirection_type(&str[i]) == 0 && get_token_type(&str[i]) != TYPE_PIPE))
		return (true);
	return (false);
}

void	validate_quotes(char *str)
{
	uint8_t	in_quote;
	size_t	i;
	size_t	count;

	in_quote = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		in_quote = get_quote_type(&str[i]);
		if (in_quote)
			count++;
		while (str[i] != in_quote)
			i++;
		if (str[i] == in_quote)
			count++;
		i++;


	}

}