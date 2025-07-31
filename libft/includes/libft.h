/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:13:54 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/30 21:42:28 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./ft_printf.h"
# include "./get_next_line.h"
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>

int					ft_isalpha(unsigned char c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(unsigned char c);
int					ft_isprint(int c);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_ispunct(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
size_t				ft_strlen(const char *s);
size_t				ft_strnlen(const char *s, size_t maxlen);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putstr(char *str);
char				*ft_strstr(const char *str, const char *to_find);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_realloc(void *ptr, size_t size);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *str, int fd);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, unsigned int n);
char				*ft_strdup(const char *src);
int					ft_intlen(int n);
int					ft_abs(int n);
int					ft_max(int a, int b);
int					ft_min(int a, int b);
int					ft_nmax(int a, int b);
int					ft_nmin(int a, int b);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_putnbr_fd(int n, int fd);
void				*ft_malloc(size_t size);
void				ft_free(void *ptr);
void				ft_putendl_fd(char *s, int fd);
long				ft_atol(const char *str);
long long			ft_atoll(const char *str);
int					ft_atoi_strict(const char *str);
long				ft_atol_strict(const char *str);
long long			ft_atoll_strict(const char *str);
char				*ft_strrev(char *str);
char				*ft_strchrnul(const char *str, int c);
int					*ft_intcpy(int *src, int *dst, size_t size);
void				ft_intsort(int *arr, size_t size);
int					*ft_arrdup(int *arr, size_t size);
int					ft_is_palindrome(char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strcat(char *dest, const char *src);
void				ft_free_split(char **split);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_lst);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif