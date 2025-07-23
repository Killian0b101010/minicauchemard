#include "../../includes/minishell.h"

static void	ft_write_rl(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	ft_handler(int sig)
{
	ft_write_rl(sig);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
