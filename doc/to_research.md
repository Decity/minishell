Do we use the actual env, or do we make a copy of it?
> Make a copy of it

What does "redirections" actually do? We set the redirection token in parsing, so what's the difference
between that and redirections?
> the redirection step MIGHt not be as relevant in this project. It's mostly to check shenanigans with operators.

Confirm if the following is correct:
	All commands, including the first one, run in a child process.
	Single built in's are the exception 

figure out how to implement signals
> Have 1 volatile sig_atomic_t, if something goes wrong (or program is quit) in a child process, send signal to change this variable

figure out heredoc

consider closing fd's early
 check with: --track-fds



