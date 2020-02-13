/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-ram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:07 by ede-ram           #+#    #+#             */
/*   Updated: 2020/02/13 23:11:54 by jerry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef	struct	s_opt
{
	char			*key;
	char			*value;
	struct s_opt	*next;
}				t_opt;

void			ft_free_tabstr(char **tab_tofree);
char			**ft_tab_strdup(char **tabl);
char			**tab_realloc(char **tabl, char *line);

char			*ft_strconv_w(char *str);
size_t			ft_strlen_w(const char *str);
size_t			ft_strlen(const char *s);
char			*ft_to_lower(char *str);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char	*dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalnumstr(char *str);
int				ft_isdigitstr(const char *str);
int				ft_isxstr(const char *set, const char *str);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char splitchar);
int				ft_strclen(const char *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(const char *s1, const char *s2, char *tofree);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_match(const char *s1, const char *s2);
int				ft_nmatch(const char *s1, const char *s2);
int				ft_strncmp_n(const char *s1, const char *s2, size_t n);

int				ft_isalpha(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isblank(int c);
int				ft_isx(const char *set, int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memdup(const void *s, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);

void			ft_tab_strdel(char ***as);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putstrv(char **strv);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *n);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstpush(t_list **head, t_list *node);

int				ft_sqrt(int nb);
int				ft_is_prime(int nb);
int				ft_power(int nb, int power);
int				ft_factorial(int nb);

t_opt			*ft_get_opts(int ac, char **av, int *i, const char *optstr);
t_opt			*ft_create_opt(const char *name, size_t l, const char *val);
t_opt			*ft_fetch_opt(char *name, size_t size, t_opt *optlst);
int				ft_is_valid_opt(const char *opts, const char *nm, size_t len);
void			ft_inv_opt(const char *pn, const char *name, size_t len);
void			ft_bad_opt(const char *pn, const char *name, size_t len);
void			ft_print_opts(t_opt *optlst);
void			ft_free_opts(t_opt *opts);
#endif
