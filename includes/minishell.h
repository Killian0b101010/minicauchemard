/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:05:06 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 18:45:37 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE_CD
#  define BUFFER_SIZE_CD 4096
# endif

# ifndef ARENA_DEFAULT_CAPACITY
#  define ARENA_DEFAULT_CAPACITY 32
# endif

# ifndef NEWLINE_SYNTAX
#  define NEWLINE_ERR_PRE "minicauchemar: syntax error near unexpected token "
#  define NEWLINE_ERR_SUF "`newline\'\n"
# endif

# ifndef PIPE_SYNTAX
#  define PIPE_SYNTAX "minicauchemar: syntax error near unexpected token `|\'\n"
# endif

# ifndef CMD_NOT_FOUND
#  define CMD_NOT_FOUND "minicauchemar: Command '' not found\n"
# endif

# ifndef STATE_NORMAL
#  define STATE_NORMAL 0
# endif

# ifndef STATE_SINGLE
#  define STATE_SINGLE 1
# endif

# ifndef STATE_DOUBLE
#  define STATE_DOUBLE 2
# endif

extern int			g_exit_status;

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
typedef struct arena_collector
{
	void			**arena_memory;
	size_t			capacity;
	size_t			actual_size;
	size_t			resize;
	size_t			size;
}					t_arena;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	char			*full_path;
	char			*cmd_path;
	int				heredoc_fd;
}					t_token;

typedef struct t_env
{
	char			**envp;
	char			*home_path;
	char			*old_path;
	char			*new_path;
	char			*pwd;
	t_arena			*arena;
	t_token			*tokens;
}					t_env;
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
	int				block_count;
	int				color;
}					t_t2;

typedef struct t_fd
{
	int				**pipefd;
	int				cmd_count;
	int				*pid;

}					t_fd;

typedef struct s_cmd_block
{
	char			**args;
	char			*cmd_path;
	char			*full_cmd;
	char			**path;
	int				flag_access;
	int				is_here_doc;
	int				i;
	int				split_start;
	int				split_blocks_i;
	t_env			*env;
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

// ===== src/core/ =====
// main.c
int					*is_active_shell(int *value);
int					*get_signal_received(int *signal_received);

// main_utils.c
void				print_minicauchemar(void);
char				*get_prompt_and_input(void);
int					count_quotes(char *str, int *single_quotes,
						int *double_quotes);
int					getnewcolor(void);
char				*ft_strjoin_free(char *s1, char *s2);
char				*join_itoa_free(char *str, int num);

// main_utils2.c
void				execute_multiple_cmd(t_cmd_block *block, t_env *env);
int					init_bc_no_env(t_env *env);
int					get_shlvl_index(char **envp);

// ===== src/execution/ =====
// execute_commands.c
void				ifcmd_notvalid(int i, t_cmd_block *blocks, t_env *env);
void				execute_child_command(int i, t_cmd_block *blocks,
						t_env *env);
pid_t				child_process2(int i, t_cmd_block *blocks, t_env *env);
void				exec_loop_one(t_cmd_block *block, t_env *env);
void				exec_if_executable(t_cmd_block *block, t_env *env);

// execution_pipes.c
void				setup_child_pipes(int i, t_cmd_block *blocks);
void				init_pipes2(int i, t_fd *fd, t_arena *arena);
void				init_pipex(t_arena *arena, t_cmd_block *blocks, t_t2 t2,
						t_fd *fd);
void				close_unused_pipes(t_fd *fd, int i);
void				close_all_fds(t_fd *fd);

// execution_processing.c
void				execute_cmd2(t_cmd_block *blocks, t_env *env);
void				process_commands(t_cmd_block *blocks, t_env *env,
						int block_count, int i);
int					process_input_line(char *input, t_env *env);
int					is_executable_file(const char *path);
void				if_nopath(char *str);

// execution_utils.c
int					verify_input(char *input, int *single_quotes,
						int *double_quotes);
void				flagaccesscheck(t_cmd_block *blocks, t_env *env);
int					is_command_valid_for_exec(t_cmd_block *block, t_env *env);
int					has_heredoc_in_block(t_token *tokens, int token_count);

// path.c
char				**get_path_arena(t_arena *arena, char **envp);
int					is_abs_path(char *cmd);

// builtins/cd.c
int					cd_builtin(t_token *tokens, int token_count, t_env *env);

// builtins/echo.c
int					echo(t_token *tokens, int token_count);

// builtins/env.c
int					env_cmd(int index, t_env *env, t_token *tokens, t_t2 *t2);
void				ft_set_env(t_env *env, char **envp);

// builtins/exec_builtins.c
int					is_builtin(char *cmd);
int					execute_builtin_block(t_cmd_block *block, t_env *env);

// builtins/exit.c
void				exit2(t_env *env);
void				exit_builtin(t_cmd_block *block, t_env *env);

// builtins/export.c
int					export_builtin(t_env *env, t_token *tokens,
						int token_count);
void				ft_error_export(char *var_name);

// builtins/pwd.c
int					pwd(t_t2 *t2);

// builtins/unset.c
int					unset(t_env *env, t_token *tokens, int token_count);

// ===== src/expansion/ =====
// expansion.c
char				*expand_variables(char *str, t_env *env);
void				process_token_expansion(t_token *tokens, int token_count,
						t_env *env);

// expansion_helpers.c
char				*process_variable_expansion(char *str, t_env *env, int *i,
						char *result);
char				*process_expansion_loop(char *str, t_env *env);
char				*copy_escaped_variable(char *str, int *i, t_env *env,
						char *result);

// expansion_utils.c
char				*get_expanded_variable_value(char *str, t_env *env, int i);
char				*append_char_to_result(t_arena *arena, char *result,
						char c);
int					expand_variable_at_position(t_arena *arena, char *str,
						int i);
char				*expand_exit_status_in_string(t_arena *arena, char *str);
int					append_escaped_exit_status(t_arena *arena, char **result,
						int i);
int					append_expanded_exit_status(t_arena *arena, char **result,
						char *exit_str, int i);
int					is_escaped_exit_status(const char *str, int i, int len);

// expansion_utils2.c
char				*get_variable_value(char *var_name, t_env *env);
char				*create_single_char_string(t_arena *arena, char *str,
						int i);
char				*get_env_value(char *var_name, t_env *env);

// ===== src/malloc/ =====
// arena_collector.c
t_arena				*arena_init(size_t initial_capacity);
void				*arena_alloc(t_arena *arena, size_t size_block);
void				free_arena(t_arena *arena);

// split_arena.c
char				**ft_split_arena(t_arena *arena, char const *s, char c);

// utils_arena.c
char				*ft_strjoin_arena(t_arena *arena, char *s1, char *s2);
char				*ft_strdup_arena(t_arena *arena, char const *src);
char				*ft_itoa_arena(t_arena *arena, int n);
void				*ft_realloc_arena(void *ptr, size_t old_size,
						size_t new_size);

// ===== src/parsing/ =====
// tokenizer.c
void				free_tokens(t_token *tokens, int count);
t_token_type		get_token_type(char *str);
void				tokenize(char *str, t_t2 *t2);
void				tokenize2(char *str, t_t2 *t2);
t_token				*tokenizer(t_arena *arena, char *str, int *token_count);

// syntax_parsing.c
int					parse_syntax(t_token *tokens, int token_count);
int					pipe_syntax(t_token *tokens, t_t2 t2);
int					verify_token_syntax(t_token *tokens, t_t2 *t2);

// tokenizer_utils.c
void				tokenize3(t_arena *arena, t_token *tokens, t_t2 *t2);
int					expand_tokens(t_arena *arena, t_token **tokens,
						int *capacity);
void				rm_null_tokens(t_token *tokens, int *token_count);
int					count_quotes(char *str, int *single_quote,
						int *double_quote);
void				update_quote_state(char c, int *state, int *single_quote,
						int *double_quote);

// ===== src/redirection/ =====
// redirection_utils.c
int					handle_input_redirection(t_token *tokens, int i);
int					handle_output_redirection(t_token *tokens, int i);
int					handle_append_redirection(t_token *tokens, int i);
int					handle_heredoc_redirection(t_token *tokens, int i);

// redirections.c
int					setup_heredoc(t_env *env, t_arena *arena, char *delimiter);
int					handle_redirections(t_token *tokens, int token_count);
int					preprocess_heredocs(t_env *env, t_token *tokens,
						int token_count);

// ===== src/signal/ =====
// handler.c
void				ft_handler(int sig);
void				ft_handler_sigquit(int sig);
void				ft_handler_heredoc(int sig);

// handler2.c
void				setup_interactive_signals(void);
void				setup_heredoc_signals(void);
void				setup_child_signals(void);
void				process_commands_signal(t_cmd_block *blocks, int i);
void				ft_handler_sigquit(int sig);
void				ft_handler_heredoc(int sig);

// ===== src/utils/ =====
// utils.c
void				t(int a);
int					is_space(char c);
void				directory_error(char *cmd);
void				print_syntax_error(char *value);
int					count_pipes(t_token *tokens, int token_count);

// utils2.c
int					fill_block(t_arena *arena, t_cmd_block *block,
						t_token *tokens);
t_cmd_block			*split_into_blocks(t_arena *arena, t_token *tokens, t_t2 t2,
						int *block_count);
void				print_cmd_blocks(t_cmd_block *blocks, int block_count);
void				close_inherited_fds(void);

// utils3.c
char				**build_cmd_args(t_arena *arena, t_token *tokens,
						int count);
int					is_empty_input(char *input);
void				close2(int fd);
void				restore_fds(int saved_stdin, int saved_stdout);

#endif