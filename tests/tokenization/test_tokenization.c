#include "../../inc/minishell.h"

char *test_inputs[] = {
	"one",
	"one two",
	"one two three",
	"one 'two three'",
	NULL
};


int	main(void)
{
	t_data data;

	ft_bzero(&data, sizeof(data));

	for(int i = 0; test_inputs[i]; i++)
	{
		data.input = test_inputs[i];
		set_tokens(&data);
		debug(&data);
	}
}