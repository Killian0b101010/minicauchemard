/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 20:29:18 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/10 20:29:19 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../includes/pipex.h"
# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>

# define BUFFER_SIZE 30
typedef struct t_env
{
	char			**envp;
	char			*home_path;
	char			*old_path;
	char			*new_path;
	char			*pwd;
}					t_envv;

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
}					t_t2;

void				echo(t_token *tokens, int token_count);
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

#endif