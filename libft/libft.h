/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:48:34 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:08:28 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "get_next_line.h"
# define FT_SIZE_MAX (size_t)~0

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef	struct		s_flags
{
	char			flag;
	int				width;
	int				precision;
	char			type;
	int				zero;
	int				wrong;
}					t_flags;

void				check_flag(const char **line, t_flags *flags);
void				check_width(const char **line, t_flags *flags, va_list args);
void				check_type(const char **line, t_flags *flags);
void				check_precision(const char **line, t_flags *flags,\
					va_list args);
void				check_length(const char **line, t_flags *flags);
int					parse_flags(const char **line, t_flags *flags, va_list args);
int					ft_printf(const char *line, ...);
int					treat_flags(t_flags *flags, va_list	args);
int					print_hexa(unsigned long n);
int					print_hexa_big(unsigned long n);
int					print_pointer(int *n);
int					print_c(t_flags *flags, va_list args);
int					print_s(t_flags *flags, va_list	args);
int					print_s_width(t_flags *flags, char *str);
int					print_s_precision(t_flags *flags, char *str, size_t w,\
					size_t p);
int					print_s_null(t_flags *flags, int w, int min);
int					print_u(t_flags *flags, va_list	args);
int					print_u_width(t_flags *flags, int count, unsigned int num);
int					print_u_precision(t_flags *flags, int count, unsigned int num);
int					print_x(t_flags *flags, va_list	args);
int					print_x_width(t_flags *flags, int count, unsigned int num);
int					print_x_precision(t_flags *flags, int count, unsigned int num);
int					count_x_len(unsigned int num);
void				init_flags(t_flags *flags);
int					print_x_big(t_flags *flags, va_list	args);
int					print_x_width_big(t_flags *flags, int count, unsigned int num);
int					print_x_precision_big(t_flags *flags, int count,\
					unsigned int num);
int					print_p(t_flags *flags, va_list args);
int					count_u_len(unsigned int num);
int					count_d_len(int num);
int					print_d(t_flags *flags, va_list args);
int					print_d_width(t_flags *flags, int count, int num);
int					print_d_precision_neg(t_flags *flags, int count, int num);
int					print_d_width_neg(t_flags *flags, int count, int num, int n);
int					print_perc(t_flags *flags);
int					print_p_null(t_flags *flags, int w);
int					ft_putnbr_unint(unsigned int n);
int					ft_putnbr(int n);
int					ft_putstr(char *s);

int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strnstr(const char *str1, const char *str2, size_t n);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcpy(char *dst, const char *src);
size_t				ft_strlen (const char *str);
size_t				ft_strnlen (const char *str, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrimwhole(char const *s1, char const *set);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
int					ft_putchar(char c);
void				ft_putendl(char *s);

#endif
