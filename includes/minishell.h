/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 17:37:29 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/pipex.h"
# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE_CD
#  define BUFFER_SIZE_CD 4096
# endif

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
	char			buff[1024];
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
int					count_pipes(t_token *tokens, int token_count);
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
int					is_builtin(char *cmd);
int					exec_builtins(t_token *tokens, int token_count, t_env *env,
						t_t2 *t2);
int					export(t_env *env, t_token *tokens, int token_count);
int					unset(t_env *env, t_token *tokens, int token_count);
void				exit2(void);
void				execute_builtin_in_block(t_cmd_block *block, t_env *env);
void				execute_piped_commands(t_cmd_block *blocks, int block_count,
						t_env *env);
char				*expand_variables(char *str, t_env *env);
void				process_token_expansion(t_token *tokens, int token_count,
						t_env *env);
void				restore_fds(int saved_stdin, int saved_stdout);
int					execute_with_redirections(t_cmd_block *block, t_env *env);
int					execute_builtin_block(t_cmd_block *block, t_env *env);
int					handle_input_redirection(t_token *tokens, int i);
int					handle_output_redirection(t_token *tokens, int i);
int					handle_append_redirection(t_token *tokens, int i);
int					handle_heredoc_redirection(t_token *tokens, int i);
int					setup_heredoc(char *delimiter);
char				*process_expansion_loop(char *str, t_env *env);
int					expand_variable_at_position(char *str, int i);
char				*get_expanded_variable_value(char *str, t_env *env, int i);
char				*append_char_to_result(char *result, char c);
char				*get_variable_value(char *var_name, t_env *env);
char				*create_single_char_string(char *str, int i);
char				*get_env_value(char *var_name, t_env *env);
void				print_minicauchemar(void);
char				*get_prompt_and_input(void);
int					process_input_line(char *input, t_env *env);
int					is_empty_input(char *input);

#endif