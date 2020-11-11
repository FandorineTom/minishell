/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:42:00 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/17 17:02:45 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_struct
{
	int				fd;
	char			*leftovers;
	struct s_struct	*next;
}					t_struct;

int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					freemem(t_struct **list, int fd, int res, char **str);
int					delnode(t_struct **list, int fd);
int					actually_gnl(int fd, char **line, char **leftovers);
int					to_return(char **line, char **leftovers, int ret);
int					append_line(char **line, char **leftovers);
t_struct			*new_list(int fd);

#endif
