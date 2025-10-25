/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:00:00 by elie              #+#    #+#             */
/*   Updated: 2025/10/22 17:19:09 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *tests_basic[] = {
	"echo hi",
	"echo hi bye",
	"echo",
	NULL
};

char *tests_quotes[] = {
	"echo \"\"",
	"echo \"hi\"",
	"echo 'hi'",
	"echo 'hi'bye",
	"echo hi'bye'",
	"echo \"hi\"bye",
	"echo hi\"bye\"",
	"echo \"'hi'\"",
	"echo hi'bye'hi\"bye\"",
	"echo \"\"\"\"",
	"echo ''''",
	"echo \"'\"'\"'",
	NULL
};

char *tests_redir[] = {
	"echo hi > out",
	"echo hi < in > out",
	"echo hi<in > out",
	"echo hi<in>out",
	"echo hi >> out",
	"echo hi>>out",
	NULL
};

char *tests_redir_quotes[] = {
	"echo \"hi\" > out",
	"echo 'hi' > out",
	"echo \"hi\" < in",
	"echo \"hi\">\"out\"",
	"echo 'hi'>'out'",
	"cat < \"in\" > \"out\"",
	"cat <'in'>'out'",
	"echo \"hi > out\"",
	"echo 'hi < in'",
	"echo \"hi\" >> \"out\"",
	NULL
};

char *tests_pipes[] = {
	"echo hi | bye",
	"echo hi|bye",
	"echo hi | cat",
	"echo hi | cat | grep h",
	"echo hi|cat|grep h",
	"ls | grep test | wc -l",
	"cat file | sort | uniq",
	NULL
};

char *tests_pipes_redir[] = {
	"echo hi | cat > out",
	"cat < in | grep h",
	"cat < in | grep h > out",
	"echo hi > out | cat",
	"cat < in | grep h | wc > out",
	"echo hi|cat<in>out",
	"cat<in|grep h>out|wc",
	"echo hi>out|bye",
	"echo hi<in>out|bye",
	NULL
};

char *tests_pipes_quotes[] = {
	"echo \"hi\" | cat",
	"echo 'hi' | cat",
	"echo \"hi | cat\"",
	"echo 'hi | cat'",
	"echo \"hi\"|cat|grep \"h\"",
	"echo 'hi'|cat|grep 'h'",
	"cat \"file\" | grep 'pattern'",
	NULL
};

char *tests_pipes_quotes_redir[] = {
	"echo \"hi\" | cat > \"out\"",
	"cat < \"in\" | grep \"h\" > \"out\"",
	"echo 'hi'|cat<'in'>'out'",
	"cat \"file\" | grep 'pattern' > output",
	"echo \"test\" < 'in' | cat > \"out\"",
	"cat<\"in\"|grep 'h'|wc>'out'",
	NULL
};

char *tests_whitespace[] = {
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
	NULL
};

char *tests_heredoc[] = {
	"cat << EOF",
	"cat <<EOF",
	"cat << \"EOF\"",
	"cat <<'EOF'",
	NULL
};

char *tests_expansion[] = {
	"echo $USER",
	"echo \"$USER\"",
	"echo '$USER'",
	NULL
};

char *tests_edge[] = {
	"echo hi;bye",
	NULL
};

char *tests_fail_quotes[] = {
	"echo \"hi",
	"echo 'hi",
	"echo \"hi'",
	"echo 'hi\"",
	"echo \"hello world",
	"echo 'hello world",
	"cat \"file",
	"cat 'file",
	NULL
};

char *tests_fail_redir[] = {
	"echo >",
	"echo <",
	"echo < ",
	"echo > ",
	"echo >>",
	"echo <<",
	"echo > < out",
	"echo < > in",
	"echo hi ><out",
	"echo hi <>out",
	"echo hi >><<out",
	"echo hi>>>out",
	"echo hi< <<in",
	"echo hi> >>out",
	"echo hi< <<in",
	"echo hi>> >out",
	"echo hi<< <in",
	"echo hi>>> out",
	"echo hi<<< in",
	NULL
};

char *tests_fail_pipes[] = {
	"|",
	"||",
	"|| ",
	"| |",
	" | | | ",
	"|||",
	"echo |",
	"echo | | cat",
	"echo ||",
	"echo |||",
	"echo hi |",
	"echo | | cat",
	"echo hi | | cat",
	"echo hi|| |bye",
	"echo hi|||bye",
	"echo hi||| bye",
	"echo hi||| bye",
	NULL
};

char *tests_fail_mixed[] = {
	"echo \"hi | cat",
	"echo 'hi > out",
	"echo \"hi\" | ",
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

void	run_tests(char **tests, char *category)
{
	t_data	data;
	int		i;

	if (category)
		printf("\n=== %s ===\n\n", category);
	i = 0;
	while (tests[i])
	{
		ft_memset(&data, 0, sizeof(t_data));
		data.input = ft_strdup(tests[i]);
		printf("Input:  %s\n", tests[i]);
		set_tokens(&data);
		printf("Tokens: ");
		print_tokens(data.tokens);
		printf("\n");
		cleanup_data(&data);
		i++;
	}
}

int	main(void)
{
	run_tests(tests_basic, "Basic Commands");
	run_tests(tests_quotes, "Quotation");
	run_tests(tests_redir, "Redirection");
	run_tests(tests_redir_quotes, "Redirection with Quotes");
	run_tests(tests_pipes, "Pipes");
	run_tests(tests_pipes_redir, "Pipes with Redirection");
	run_tests(tests_pipes_quotes, "Pipes with Quotes");
	run_tests(tests_pipes_quotes_redir, "Pipes with Quotes and Redirection");
	run_tests(tests_whitespace, "Whitespace Handling");
	run_tests(tests_heredoc, "Heredoc");
	run_tests(tests_expansion, "Variable Expansion");
	run_tests(tests_edge, "Edge Cases");
	run_tests(tests_fail_quotes, "FAIL - Unclosed Quotes");
	run_tests(tests_fail_redir, "FAIL - Invalid Redirections");
	run_tests(tests_fail_pipes, "FAIL - Invalid Pipes");
	run_tests(tests_fail_mixed, "FAIL - Mixed Invalid Cases");
	return (0);
}