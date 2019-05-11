/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:28:45 by maboye            #+#    #+#             */
/*   Updated: 2019/05/11 15:51:16 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# define BUFF_SIZE 4096

typedef struct	s_list
{
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

char			**ft_addtotab(char **tab, char *str);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
void			ft_bubblesort(void **add, int (*f)());

int				ft_intlen(int nb);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprime(int nb);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isupper(int c);
int				ft_isblank(int c);

char			*ft_itoa(int n);

void			ft_lstaddback(t_list **list, t_list *prev, t_list *next);
t_list			*ft_lstaddelem(t_list *prev, t_list *next);
void			ft_lstaddfront(t_list **list, t_list *prev, t_list *next);
t_list			*ft_lstat(t_list *begin_list, unsigned int nbr);
void			ft_lstdel(t_list **list);
void			ft_lstmerge(t_list **list1, t_list *list2);
size_t			ft_lstsize(t_list *list);

void			*ft_memalloc(size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);

float			ft_power(int nb, int po);

void			ft_print_tab(char **str);
void			ft_printf(int fd, const char *str, ...);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);

int				ft_quicksort(void **add, int start, int size, int (*f)());

char			*ft_readfile(char *file);
void			*ft_realloc(void *ptr, size_t new_size);
char			**ft_splitwspc(const char *str);

float			ft_sqrt(int n);

char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *str, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, size_t n);
char			*ft_strfjoin(const char *s1, const char *s2, int choose);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
char			*ft_strncat(char *dest, const char *src, size_t nb);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *str, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);

void			ft_swap(void **s1, void **s2);

char			**ft_tabcopy(const char **add);
void			ft_tabfree(void **add);
int				ft_tablen(void **add);
void			ft_tabprint(char **str);

int				ft_tolower(int c);
int				ft_toupper(int c);

int				ft_wordcount(const char *str, char c);
int				get_next_line(const int fd, char **line);

int				my_printf(int fd, const char *str, ...);
int		    	my_putchar_fd(char c, int fd);
int		 		my_putendl_fd(char const *s, int fd);
int		    	my_putnbr_fd(int n, int fd);
int				my_putstr_fd(char const *s, int fd);

#endif
