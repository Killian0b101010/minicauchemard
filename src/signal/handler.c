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
void	ft_handler2(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
