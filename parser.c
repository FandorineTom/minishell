/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/19 15:00:32 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char **line, t_command *com)
{
	pars_pipes(line, com);
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
		pars_tockens(line, com);
	// pars_variables(blocks, com);
}

void	pars_pipes(char **line, t_command *com)
{
	while (line && *line && **line)
	{
		if (**line == '|')
			com->pipe_count++;
		**line++;
	}
	com->no_command = com->pipe_count + 1;
	com->no_arg = com->pipe_count + 1;
}

void	pars_tockens(char **line, t_command *com)
{
	t_comd	*new;

	new = com->comd;
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
	{
		// pars_command(line, com);
		// pars_flags(line, com);
		// pars_variables(line, com);
		if (!check_command(line, com))
			com->no_command = 0;
		if (!check_env_var(line, com))
			com->no_var = 0;
		if (!check_agr(line, com))
			com->no_arg = 0;
		if  (check_mistakes(line, com))	
			break ; // тут возможно надо всякие экситы и прочее гавно реализовывать
		**line++; // или тут это вообще не нужно, или еще нужно как  (*line)++
		com->comd = com->comd->next;
		init_comd(com);
	}
	com->comd = new;
}

int		check_command(char **line, t_command *com)
{
	if (check_which_command(line, com, "echo", 5))
		return (1);
	if (check_which_command(line, com, "cd", 3))
		return (1);
	if (check_which_command(line, com, "pwd", 4))
		return (1);
	if (check_which_command(line, com, "export", 7))
		return (1);
	if (check_which_command(line, com, "unset", 6))
		return (1);
	if (check_which_command(line, com, "env", 4))
		return (1);
	if (check_which_command(line, com, "exit", 5))
		return (1);
	if (com->no_var == 1 && check_env_var(line, com))
		{
			change_env_var_meaning(line, com);
			return(check_command(&com->env_var, com));
		}
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (0);
	while (str1[i] && str1[i] == str2[i] && i < (len - 1))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int check_which_command(char **line, t_command *com, char *command, int i)
{
	if (!(ft_strncmp(*line, command, i) || !(ft_strncmp(*line, ft_strjoin_gnl(command, " "), i))))
	{
		if (!(com->comd->cmnd = ft_strdup(command)))
				return (0); // подумать насчет кодов ошибок
		(*line) += i - 1; // свидгаюсь на пробел или на конец строки - вопрос в том, если в line это не конец строки, а перенос на новую строку?
		return (1);
	}
	return (0);
}

int check_env_var(char **line, t_command *com)
{
	int	i;

	i = ft_strlen_space(*line);
	if (**line == '$')
	{
		if (!(com->env_var = ft_substr(*line, 1, i - 1))) // скорее всего минус 1 не нужен
			return (0);
		com->no_var += 1;
		(*line) += i;
		return (1);
	}
	return (0);
}

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t count)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	if (!src && !dst)
		return (dst);
	temp1 = (unsigned char*)src;
	temp2 = (unsigned char*)dst;
	while (i < count)
	{
		temp2[i] = temp1[i];
		i++;
	}
	return (temp2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	size;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	if (start > i)
		return (ft_strdup(""));
	size = i - start;
	if (len > size)
		len = size;
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}