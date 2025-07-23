/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 17:09:11 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_gradient(const char **text)
{
	int				i;
	int				j;
	unsigned long	width;
	int				height;

	height = -1;
	width = 0;
	while (text[++height])
		if (ft_strlen(text[height]) > width)
			width = ft_strlen(text[height]);
	i = -1;
	while (text[++i])
	{
		j = -1;
		while (text[i][++j])
		{
			put_color_char(text[i][j], get_color(i, height), 200, get_color(j,
					width));
		}
	}
}

void	print_minicauchemar(void)
{
	const char	*str[14];

	str[0] = "___  ____       _                      _";
	str[1] = "                               \n";
	str[2] = "|  \\/  (_)     (_)                 ";
	str[3] = "   | |                              \n";
	str[4] = "| .  . |_ _ __  _  ___ __ _ _   _  _";
	str[5] = "__| |__   ___ _ __ ___   __ _ _ __ \n";
	str[6] = "| |\\/| | | '_ \\| |/ __/ _` | | | |/";
	str[7] = " __| '_  \\";
	str[8] = "/ _ \\ '_ ` _ \\ / _` | '__|\n";
	str[9] = "| |  | | | | | | | (_| (_| | |_| | (__|";
	str[10] = " | | |  __/ | | | | | (_| | |   \n";
	str[11] = "\\_|  |_/_|_| |_|_|\\___\\__,_|\\__,_|\\_";
	str[12] = "__|_| |_|\\___|_| |_| |_|\\__,_|_|  \n";
	str[13] = NULL;
	put_gradient(str);
}

char	*build_gradient_prompt(const char *raw, int i, char *variable)
{
	char	*result;
	int		len;
	char	*ansi;
	char	char_str[2];
	int		rgb;

	t((result = ft_strdup(""), len = ft_strlen(raw), 0));
	while (raw[++i])
	{
		rgb = get_color(i, len);
		ansi = ft_strjoin("\e[1;38;2;", "");
		ansi = join_itoa_free(ansi, rgb);
		ansi = ft_strjoin_free(ansi, ";");
		ansi = ft_strjoin_free(ansi, variable);
		ansi = ft_strjoin_free(ansi, ";");
		ansi = join_itoa_free(ansi, 255);
		ansi = ft_strjoin_free(ansi, "m");
		char_str[0] = raw[i];
		char_str[1] = '\0';
		ansi = ft_strjoin_free(ansi, char_str);
		ansi = ft_strjoin_free(ansi, "\e[0m");
		result = ft_strjoin_free(result, ansi);
		ft_free(ansi);
	}
	return (ft_free(variable), result);
}

char	*get_prompt_and_input(void)
{
	char		cwd[10000];
	char		*raw_prompt;
	char		*styled_prompt;
	char		*input;
	static int	var = 0;

	getcwd(cwd, sizeof(cwd));
	raw_prompt = ft_strjoin("minicauchemar:", cwd);
	raw_prompt = ft_strjoin_free(raw_prompt, "$ ");
	var = getnewcolor();
	styled_prompt = build_gradient_prompt(raw_prompt, -1, ft_itoa(var));
	ft_free(raw_prompt);
	input = readline(styled_prompt);
	ft_free(styled_prompt);
	return (input);
}

int	getnewcolor(void)
{
	static int	nuance = 0;
	int			colors[12];
	int			result;

	colors[0] = 255;
	colors[1] = 220;
	colors[2] = 180;
	colors[3] = 140;
	colors[4] = 100;
	colors[5] = 80;
	colors[6] = 100;
	colors[7] = 140;
	colors[8] = 180;
	colors[9] = 220;
	colors[10] = 255;
	colors[11] = 230;
	result = colors[nuance % 12];
	nuance++;
	return (result);
}
