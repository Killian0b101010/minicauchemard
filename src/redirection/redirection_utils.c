/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 21:50:57 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

/**
 * Gère une redirection d'entrée (<) en redirigeant stdin vers un fichier.
 *
 * Cette fonction configure une redirection d'entrée en ouvrant le fichier
 * spécifié et en redirigeant stdin vers ce fichier:
 * - Ouvre le fichier en mode lecture seule
 * - Vérifie que le fichier existe et est accessible
 * - Utilise dup2() pour rediriger stdin vers le fichier
 * - Ferme le descripteur temporaire
 * - Affiche une erreur si l'ouverture échoue
 *
 * Parameters :
 * - tokens - Tableau des tokens contenant la commande
 * - i - Index du token de redirection dans le tableau
 *
 * Return : 0 en cas de succès, -1 si erreur
 */
int	handle_input_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_RDONLY);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close2(fd);
	return (0);
}

/**
 * Gère une redirection de sortie (>) en redirigeant stdout vers un fichier.
 *
 * Cette fonction configure une redirection de sortie en créant/tronquant
 * le fichier spécifié et en redirigeant stdout vers ce fichier:
 * - Ouvre/crée le fichier en mode écriture avec troncature
 * - Définit les permissions à 0644 (rw-r--r--)
 * - Utilise dup2() pour rediriger stdout vers le fichier
 * - Ferme le descripteur temporaire
 * - Affiche une erreur si l'ouverture échoue
 *
 * Parameters :
 * - tokens - Tableau des tokens contenant la commande
 * - i - Index du token de redirection dans le tableau
 *
 * Return : 0 en cas de succès, -1 si erreur
 */
int	handle_output_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close2(fd);
	return (0);
}

/**
 * Gère une redirection en mode append (>>) en ajoutant à la fin d'un fichier.
 *
 * Cette fonction configure une redirection de sortie en mode ajout
 * pour préserver le contenu existant du fichier:
 * - Ouvre/crée le fichier en mode écriture avec append
 * - Définit les permissions à 0644 si création nécessaire
 * - Utilise dup2() pour rediriger stdout vers le fichier
 * - Ferme le descripteur temporaire
 * - Préserve le contenu existant du fichier
 *
 * Parameters :
 * - tokens - Tableau des tokens contenant la commande
 * - i - Index du token de redirection dans le tableau
 *
 * Return : 0 en cas de succès, -1 si erreur
 */
int	handle_append_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close2(fd);
	return (0);
}

/**

 * Gère une redirection heredoc (<<) en
 * configurant l'entrée depuis un délimiteur.
 *
 * Cette fonction configure un heredoc en utilisant setup_heredoc()
 * pour créer une source d'entrée temporaire:
 * - Utilise setup_heredoc() pour créer un pipe avec l'entrée collectée
 * - Redirige stdin vers le descripteur retourné par setup_heredoc()
 * - Ferme le descripteur temporaire après redirection
 * - Permet à la commande de lire depuis l'entrée du heredoc
 *
 * Parameters :
 * - tokens - Tableau des tokens contenant la commande
 * - i - Index du token de redirection dans le tableau
 *
 * Return : 0 en cas de succès, -1 si erreur
 */
int	handle_heredoc_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = tokens[i].heredoc_fd;
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close2(fd);
	return (0);
}
