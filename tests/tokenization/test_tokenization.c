/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by elie              #+#    #+#             */
/*   Updated: 2025/10/20 12:00:54 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *tests[] = {
	"echo hi",
	"echo hi bye",

	// quotation
	"echo \"\"",
	"echo \"hi\"",
	"echo 'hi'",
	"echo 'hi'bye",
	"echo \"'hi'\"",

	// redirection
	"echo hi > out",
	"echo hi < in > out",
	"echo hi<in > out",
	"echo hi<in>out",
	"echo hi|bye",
	"echo hi | bye",
	"echo hi>out|bye",
	"echo hi<in>out|bye",

	// redirection and quotation
	"echo \"hi\" > out",
	"echo 'hi' > out",
	"echo \"hi\" < in",
	"echo \"hi\">\"out\"",
	"echo 'hi'>'out'",
	"cat < \"in\" > \"out\"",
	"cat <'in'>'out'",
	"echo \"hi > out\"",
	"echo 'hi < in'",

	// pipes
	"echo hi | cat",
	"echo hi | cat | grep h",
	"echo hi|cat|grep h",
	"ls | grep test | wc -l",
	"cat file | sort | uniq",

	// pipes and redirection
	"echo hi | cat > out",
	"cat < in | grep h",
	"cat < in | grep h > out",
	"echo hi > out | cat",
	"cat < in | grep h | wc > out",
	"echo hi|cat<in>out",
	"cat<in|grep h>out|wc",

	// pipes and quotation
	"echo \"hi\" | cat",
	"echo 'hi' | cat",
	"echo \"hi | cat\"",
	"echo 'hi | cat'",
	"echo \"hi\"|cat|grep \"h\"",
	"echo 'hi'|cat|grep 'h'",
	"cat \"file\" | grep 'pattern'",

	// pipes, quotes, and redirection
	"echo \"hi\" | cat > \"out\"",
	"cat < \"in\" | grep \"h\" > \"out\"",
	"echo 'hi'|cat<'in'>'out'",
	"cat \"file\" | grep 'pattern' > output",
	"echo \"test\" < 'in' | cat > \"out\"",
	"cat<\"in\"|grep 'h'|wc>'out'",

	// whitespace
	"",
	"   ",
	"\t",
	"\t\t\t",
	"  \t  \t  ",
	"echo    hi    bye",
	"echo\thi",
	"echo  \t  hi  \t  bye",
	"  echo hi  ",
	"\techo hi\t",
	"  \t  echo  \t  hi  \t  ",
	"echo   >   out",
	"echo\t>\tout",
	"echo  \t  >  \t  out",
	"echo   |   cat",
	"echo\t|\tcat",
	"echo  \t  |  \t  cat",
	"echo   <   in   >   out",
	"echo\t<\tin\t>\tout",

	// edge cases
	"echo",
	"echo \"\"\"\"",
	"echo ''''",
	"echo \"'\"'\"'",
	"echo hi>>>out",
	"echo hi<<<in",
	"|||",
	"echo hi|||bye",
	"echo hi &",
	"echo hi;bye",
	"echo $USER",
	"echo \"$USER\"",
	"echo '$USER'",
	"echo ~",
	"echo \"~\"",
	"echo '~'",

	// heredoc
	"cat << EOF",
	"cat <<EOF",
	"cat << \"EOF\"",
	"cat <<'EOF'",

	// append redirection
	"echo hi >> out",
	"echo hi>>out",
	"echo \"hi\" >> \"out\"",

	NULL
};

char *tests_fail[] = {
	// unclosed quotes
	"echo \"hi",
	"echo 'hi",
	"echo \"hi'",
	"echo 'hi\"",
	"echo \"hello world",
	"echo 'hello world",
	"cat \"file",
	"cat 'file",

	// invalid redirections
	"echo >",
	"echo <",
	"echo >>",
	"echo <<",
	"echo > < out",
	"echo < > in",
	"> out",
	"< in",
	"| cat",
	"echo |",
	"echo | | cat",
	"echo ||",
	"echo |||",

	// invalid pipes
	"|",
	"| echo hi",
	"echo hi |",
	"echo | | cat",
	"echo hi | | cat",

	// mixed invalid cases
	"echo \"hi | cat",
	"echo 'hi > out",
	"echo \"hi\" | ",
	"echo < ",
	"echo > ",

	// multiple consecutive operators
	"echo hi ><out",
	"echo hi <>out",
	"echo hi >><<out",

	NULL
};

void	print_tokens(char **tokens)
{
	int	i;

	if (!tokens)
	{
		printf("[NULL]\n");
		return ;
	}
	printf("[");
	i = 0;
	while (tokens[i])
	{
		printf("%s", tokens[i]);
		if (tokens[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
}

int	main(void)
{
	t_data data;

	for (int i = 0; tests[i]; i++)
	{
		ft_memset(&data, 0, sizeof(t_data));
		data.input = ft_strdup(tests[i]);
		printf("Input:  %s\n", tests[i]);
		set_tokens(&data);
		printf("Tokens: ");
		print_tokens(data.tokens);
		printf("\n");
		cleanup_data(&data);
	}

	printf("\n=== Testing Invalid Cases ===\n\n");

	for (int i = 0; tests_fail[i]; i++)
	{
		ft_memset(&data, 0, sizeof(t_data));
		data.input = ft_strdup(tests_fail[i]);
		printf("Input: \"%s\"\\n", tests_fail[i]);
		set_tokens(&data);
		printf("Tokens: ");
		print_tokens(data.tokens);
		printf("\n");
		cleanup_data(&data);
	}

	return (0);
}