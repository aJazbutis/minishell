/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:44:04 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:16:08 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				ij;
}				t_list;

typedef struct s_llst
{
	void			*content;
	struct s_llst	*next;
	struct s_llst	*prev;
	int				ij;
}				t_llst;

long long		ft_atoll(const char *str);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);

char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));
int				ft_lst_isasc(t_list *lst);
int				ft_lst_isdsc(t_list *lst);

void			**ft_free_tab(char **tab);
char			**ft_sort_tab(char **tab);
/*char			**ft_cp_tab(char **tab, int i);*/
char			*ft_utoa(unsigned int n);
char			*ft_utobase(unsigned int n, char *base_to);
char			*ft_ultobase(unsigned long n, char *base_to);
char			*ft_add_prfx(char *prfx, char *s2);

t_llst			*ft_llstnew(void *content);
void			ft_llstadd_back(t_llst **lst, t_llst *new);
void			ft_llstadd_front(t_llst **lst, t_llst *new);
int				ft_llstsize(t_llst *lst);
t_llst			*ft_llstlast(t_llst *lst);
void			ft_llstclear(t_llst **lst, void (*del)(void *));

int				ft_extension_is_ok(char *ext, char *name);
#endif
