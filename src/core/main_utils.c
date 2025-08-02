/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/02 21:33:29 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

/**
 * Affiche un texte avec un dégradé de couleurs pour créer un effet visuel.
 *
 * Cette fonction applique un dégradé de couleurs RGB sur un tableau de chaînes
 * pour créer un effet visuel attrayant lors de l'affichage:
 * - Calcule la largeur maximale du texte
 * - Applique des couleurs dégradées caractère par caractère
 * - Utilise les codes ANSI pour l'affichage coloré
 *
 * Parameters :
 * - text - Tableau de chaînes à afficher avec effet de dégradé
 *
 * Return : Aucun (void)
 */
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

/**
 * Affiche le logo ASCII "minicauchemar" avec des couleurs dégradées.
 *
 * Cette fonction affiche le titre du programme en art ASCII avec un effet
 * de dégradé coloré pour améliorer l'expérience visuelle au démarrage:
 * - Définit le texte ASCII du logo "minicauchemar"
 * - Applique l'effet de dégradé via put_gradient()
 * - Améliore l'interface utilisateur du shell
 *
 * Parameters :
 * - Aucun
 *
 * Return : Aucun (void)
 */
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

/**


 * Construit une chaîne de prompt avec des couleurs
 * dégradées pour chaque caractère.
 *
 * Cette fonction transforme un prompt brute en prompt coloré en appliquant
 * des codes ANSI pour créer un effet de dégradé visuel:
 * - Parcourt chaque caractère du prompt brut
 * - Génère des codes couleur ANSI personnalisés
 * - Assemble la chaîne finale avec les codes de couleur
 * - Libère la mémoire des variables temporaires
 *
 * Parameters :
 * - raw - Chaîne de prompt brute sans couleurs
 * - i - Index de départ pour la boucle
 * - variable - Variable pour les valeurs de couleur
 *
 * Return : Chaîne de prompt colorée avec des codes ANSI
 */
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
		ansi = ft_strdup("\001\e[1;38;2;");
		ansi = join_itoa_free(ansi, rgb);
		ansi = ft_strjoin_free(ansi, ";");
		ansi = ft_strjoin_free(ansi, variable);
		ansi = ft_strjoin_free(ansi, ";");
		ansi = join_itoa_free(ansi, 255);
		ansi = ft_strjoin_free(ansi, "m\002");
		char_str[0] = raw[i];
		char_str[1] = '\0';
		ansi = ft_strjoin_free(ansi, char_str);
		ansi = ft_strjoin_free(ansi, "\001\e[0m\002");
		result = ft_strjoin_free(result, ansi);
		ft_free(ansi);
	}
	return (ft_free(variable), result);
}

/**
 * Génère et affiche le prompt du shell, puis lit l'entrée utilisateur.
 *
 * Cette fonction gère l'interface interactive du shell en créant un prompt
 * personnalisé et coloré qui inclut le répertoire de travail actuel:
 * - Récupère le répertoire de travail courant
 * - Construit le prompt avec le nom du shell et le chemin
 * - Applique l'effet de dégradé coloré
 * - Utilise readline pour capturer l'entrée utilisateur
 *
 * Parameters :
 * - Aucun
 *
 * Return : Chaîne contenant la commande saisie par l'utilisateur
 */
char	*get_prompt_and_input(void)
{
	static int	var = 0;
	int			isactive_shell;
	t_prompt	prompt;

	getcwd(prompt.cwd, sizeof(prompt.cwd));
	prompt.input = NULL;
	prompt.raw_prompt = ft_strjoin("minicauchemar:", prompt.cwd);
	prompt.raw_prompt = ft_strjoin_free(prompt.raw_prompt, "$ ");
	prompt.term = getenv("TERM");
	isactive_shell = 2;
	is_active_shell(&isactive_shell);
	if (prompt.term && ft_strncmp(prompt.term, "(null)", 6) != 0)
	{
		var = getnewcolor();
		prompt.styled_prompt = build_gradient_prompt(prompt.raw_prompt, -1,
				ft_itoa(var));
		prompt.input = readline(prompt.styled_prompt);
		isactive_shell = 1;
		is_active_shell(&isactive_shell);
		ft_free(prompt.styled_prompt);
	}
	else
		t((prompt.input = readline(prompt.raw_prompt), isactive_shell = 1,
				is_active_shell(&isactive_shell), 0));
	return (ft_free(prompt.raw_prompt), prompt.input);
}

/**
 * Génère une nouvelle couleur pour le prompt en cyclant à travers une palette.
 *
 * Cette fonction utilise une palette prédéfinie de couleurs et retourne
 * une nouvelle couleur à chaque appel pour varier l'apparence du prompt:
 * - Utilise une variable statique pour mémoriser l'état
 * - Cycle à travers un tableau de 12 couleurs prédéfinies
 * - Retourne à la première couleur après la dernière
 * - Assure une variation visuelle continue
 *
 * Parameters :
 * - Aucun
 *
 * Return : Valeur entière représentant une couleur RGB
 */
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
