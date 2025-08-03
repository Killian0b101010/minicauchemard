/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 17:51:21 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/pipex.h"
# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>

# ifndef BUFFER_SIZE_CD
#  define BUFFER_SIZE_CD 4096
# endif
# ifndef ARENA_DEFAULT_CAPACITY
#  define ARENA_DEFAULT_CAPACITY 32
# endif

typedef struct arena_collector
{
	void			**arena_memory;
	size_t			capacity;
	size_t			actual_size;
	size_t			resize;
	size_t			size;
}					t_arena;

extern int			g_exit_status;
typedef struct t_env
{
	char			**envp;
	char			*home_path;
	char			*old_path;
	char			*new_path;
	char			*pwd;
	t_arena			*arena;
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
	char			*full_path;
	char			*cmd_path;
}					t_token;

typedef struct t2
{
	int				index;
	int				i;
	int				j;
	char			buff[1024];
	int				quoted;
	int				single_quotes;
	int				double_quotes;
	int				token_count;
	int				pwd_count;
	int				env_count;
	int				block_count;
	int				color;
}					t_t2;

typedef struct t_fd
{
	int				fd_in;
	int				fd_out;
	int				**pipefd;
	int				cmd_count;
	int				*pid;
	int				cmd_start;

}					t_fd;

typedef struct s_cmd_block
{
	char			**args;
	char			*cmd_path;
	char			*full_cmd;
	char			**path;
	int				**pipefd;
	int				*pid;
	int				flag_access;
	int				is_here_doc;
	int				i;
	int				split_blocks_start;
	int				split_blocks_i;
	t_token			*tokens;
	t_t2			t2;
	t_fd			*fd;
}					t_cmd_block;

typedef struct s_prompt_input
{
	char			cwd[10000];
	char			*raw_prompt;
	char			*styled_prompt;
	char			*input;
	char			*term;
}					t_prompt;

static inline void	put_color_char(char c, int r, int g, int b)
{
	ft_printf("\e[1;38;2;%i;%i;%im%c\e[m", r, g, b, c);
}

static inline int	get_color(int i, int len)
{
	return (76 + (180. * (float)i / (float)len));
}
char				**get_path_arena(t_arena *arena, char **envp);
char				*ft_itoa_arena(t_arena *arena, int n);
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
void				tokenize3(t_arena *arena, t_token *tokens, t_t2 *t2);
int					expand_tokens(t_arena *arena, t_token **tokens,
						int *capacity);
t_token				*tokenizer(t_arena *arena, char *str, int *token_count);
int					pwd(t_t2 *t2);
int					env_cmd(int index, t_env *env, t_token *tokens, t_t2 *t2);
void				ft_set_env(t_env *env, char **envp);
int					cd_builtin(t_token *tokens, int token_count, t_env *env);
void				free_cmd_blocks(t_cmd_block *cmds, int block_count);
char				**build_cmd_args(t_arena *arena, t_token *tokens,
						int count);
int					fill_block(t_arena *arena, t_cmd_block *block,
						t_token *tokens);
t_cmd_block			*split_into_blocks(t_arena *arena, t_token *tokens, t_t2 t2,
						int *block_count);
void				print_cmd_blocks(t_cmd_block *blocks, int block_count);
int					is_builtin(char *cmd);
int					exec_builtins(t_token *tokens, int token_count, t_env *env,
						t_t2 *t2);
int					export_builtin(t_env *env, t_token *tokens,
						int token_count);
int					unset(t_env *env, t_token *tokens, int token_count);
void				exit2(t_env *env);
void				execute_builtin_in_block(t_cmd_block *block, t_env *env);
void				execute_piped_commands(t_cmd_block *blocks, int block_count,
						t_env *env);
char				*expand_variables(char *str, t_env *env);
void				process_token_expansion(t_token *tokens, int token_count,
						t_env *env);
void				restore_fds(int saved_stdin, int saved_stdout);
int					execute_with_redirections(t_cmd_block *block, t_env *env);
int					execute_builtin_block(t_cmd_block *block, t_env *env);
int					handle_redirections(t_env *env, t_arena *arena,
						t_token *tokens, int token_count);
int					handle_input_redirection(t_token *tokens, int i);
int					handle_output_redirection(t_token *tokens, int i);
int					handle_append_redirection(t_token *tokens, int i);
int					handle_heredoc_redirection(t_env *env, t_arena *arena,
						t_token *tokens, int i);
int					setup_heredoc(t_env *env, t_arena *arena, char *delimiter);
char				*process_expansion_loop(char *str, t_env *env);
int					expand_variable_at_position(t_arena *arena, char *str,
						int i);
char				*get_expanded_variable_value(char *str, t_env *env, int i);
char				*append_char_to_result(t_arena *arena, char *result,
						char c);
char				*get_variable_value(char *var_name, t_env *env);
char				*create_single_char_string(t_arena *arena, char *str,
						int i);
char				*get_env_value(char *var_name, t_env *env);
char				*expand_exit_status_in_string(t_arena *arena, char *str);
void				print_minicauchemar(void);
char				*get_prompt_and_input(void);
int					process_input_line(char *input, t_env *env);
int					is_empty_input(char *input);
void				ft_handler(int sig);
void				setup_interactive_signals(void);
void				setup_child_signals(void);
int					count_quotes(char *str, int *single_quotes,
						int *double_quotes);
int					getnewcolor(void);
char				*ft_strjoin_free(char *s1, char *s2);
char				*join_itoa_free(char *str, int num);
int					verify_input(char *input, t_t2 t2);
void				execute_cmd_one(t_cmd_block *block, t_env *env);
void				exec_loop_one(t_cmd_block *block, t_env *env);
void				fork_loop_one(t_cmd_block *block, t_env *env);
t_arena				*arena_init(size_t initial_capacity);
void				*arena_alloc(t_arena *arena, size_t size_block);
void				free_arena(t_arena *arena);
char				*ft_strjoin_arena(t_arena *arena, char *s1, char *s2);
char				*ft_strdup_arena(t_arena *arena, char const *src);
char				**ft_split_arena(t_arena *arena, char const *s, char c);
void				*ft_realloc_arena(void *ptr, size_t old_size,
						size_t new_size);
void				execute_multiple_cmd(t_cmd_block *block, t_env *env);
void				if_nopath(char *str);
int					init_bc_no_env(t_env *env);
int					get_shlvl_index(char **envp);
int					*is_active_shell(int *value);
void				if_negative_fd(int i, t_fd *fd);
void				close_files(t_fd *fd);
#endif