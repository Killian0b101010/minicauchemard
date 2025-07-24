/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:13:26 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/24 21:44:35 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	execute_cmd(char *cmd, char **envp);
void	exec_loop(char *cmd, char **envp, t_data *ex);
int	cd_builtin(t_token *tokens, int token_count, t_env *env);


void exec_other(char *cmd,char **envp)
{
    
}