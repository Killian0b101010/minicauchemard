/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 17:24:16 by dnahon           ###   ########.fr       */
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
	int				token_count;
	int				pwd_count;
	int				env_count;
}					t_t2;

typedef struct s_cmd_block
{
	char			**args;
	t_token			*tokens;
	t_t2			t2;
}					t_cmd_block;

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
int					cd_builtin(t_token *tokens, int token_count, t_env *env);
void				free_cmd_blocks(t_cmd_block *cmds, int block_count);
char				**build_cmd_args(t_token *tokens, int count);
int					fill_block(t_cmd_block *block, t_token *tokens, int start,
						int end);
t_cmd_block			*split_into_blocks(t_token *tokens, t_t2 t2,
						int *block_count);
void				print_cmd_blocks(t_cmd_block *blocks, int block_count);

#endif