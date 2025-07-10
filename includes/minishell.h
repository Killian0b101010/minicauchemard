/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 22:22:00 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/pipex.h"
# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
typedef struct t_env
{
	char			**envp;
	char			*home_path;
	char			*old_path;
	char			*new_path;
	char			*pwd;
}					t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	SYNTAX_ERROR
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
}					t_token;

typedef struct t2
{
	int				index;
	int				i;
	int				j;
	char			buff[10000];
	int				quoted;
	int				args;
	int				pwd_count;
	int				env_count;
}					t_t2;

int					echo(t_token *tokens, int token_count);
void				t(int a);
int					is_space(char c);
void				*realloc2(void *ptr, size_t old_size, size_t new_size);
void				print_syntax_error(char *value);
void				free_tokens(t_token *tokens, int count);
t_token_type		get_token_type(char *str);
void				tokenize(char *str, t_t2 *t2);
void				tokenize2(char *str, t_t2 *t2);
void				tokenize3(t_token *tokens, t_t2 *t2);
int					expand_tokens(t_token **tokens, int *capacity);
t_token				*tokenizer(char *str, int *token_count);
int					pwd(t_t2 *t2);
int					env_cmd(int index, t_env *env, t_token *tokens, t_t2 *t2);
void				set_env(t_env *env, char **envp);

#endif