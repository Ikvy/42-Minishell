/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:33:40 by alevasse          #+#    #+#             */
/*   Updated: 2022/09/22 10:07:06 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>

// LIBFT

typedef struct s_list
{
	int				value;
	int				index;
	int				place;
	struct s_list	*next;
}					t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);

int			ft_strlen(const char *s);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strcat(char *dst, const char *src);
char		*ft_strncat(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(char const *s, int c);
char		*ft_strrchr(char const *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(char const *haystack, char const *needle, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_strdel(char **as);
char		*ft_strnew(size_t size);

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, void const *src, size_t n);
void		*ft_memmove(void *dst, void const *src, size_t n);
void		*ft_memchr(void const *s, int c, size_t n);
int			ft_memcmp(void const *s1, void const *s2, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memalloc(size_t size);
void		*ft_realloc(void *ptr, size_t size);
int			ft_free_tab(char **split);
int			ft_free_n_tab(char **split, size_t len);

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
long int	ft_atol(const char *str);
char		*ft_itoa(int n);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar(char c);
void		ft_putstr(const char *s);
void		ft_putnbr(int n);
void		ft_putendl(char *s);
void		ft_putnbr_base(unsigned int n, char *base);

t_list		*ft_lstnew(int nb);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst);

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	5

# endif

char		*get_next_line(int fd);
int			ft_strchr_gnl(const char *s, int c);
char		*ft_substr_gnl(char *s, unsigned int start, size_t len);
void		ft_add_buff(char **ret, char *buff);
char		*ft_get_line(char **ret);

// PRINTF

typedef struct s_flags
{
	int	plus;	
	int	minus;	
	int	zero;	
	int	space;	
	int	sharp;
	int	dot;
}		t_flags;

typedef struct s_opts
{
	t_flags	flags;
	int		wdt;
	int		prc;
}			t_opts;

int			ft_printf(const char *fmt, ...);
int			ft_fprintf(int fd, const char *fmt, ...);
int			ft_parser(int fd, const char *fmt, va_list args);
int			ft_define_args(int fd, const char *fmt, va_list args, int *i);
t_opts		ft_get_opts(const char *fmt, int *i);
int			ft_is_flag(char c);
void		ft_add_flags(t_flags *flags, char c);

int			ft_conv_char(int fd, int c, t_opts opts);
int			ft_conv_str(int fd, char *s, t_opts opts);
int			ft_conv_int(int fd, int n, t_opts opts);
int			ft_conv_uint(int fd, unsigned int n, t_opts opts);
int			ft_conv_hex(int fd, unsigned int n, t_opts opts, int upper);
int			ft_conv_ptr(int fd, unsigned long n, t_opts opts);

int			ft_putchar_size(char c);
int			ft_putchar_size_fd(char c, int fd);
int			ft_putstr_size(const char *s);
int			ft_putstr_size_fd(char *s, int fd);
int			ft_strlen_int(const char *s);
char		*ft_insert_str(char *s, char *ins, int pos);
char		*ft_itoa_unsigned(unsigned int n);
char		*ft_itoa_hex(unsigned int n, int upper);
char		*ft_itoa_ptr(unsigned long n);

#endif
