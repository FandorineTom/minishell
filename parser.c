/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/26 19:13:04 by scopycat         ###   ########.fr       */
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
	com->no_command = com->pipe_count + 1; // надо вспомнить зачем это и как можно использовать
	com->no_arg = com->pipe_count + 1;
}

void	pars_tockens(char **line, t_command *com)
{
	// t_comd	*new;
	t_arg	*new;

	// new = com->comd; // это не нужно. потому что мы распарсиваем только одну строчку до точки запятой, где может быть только одна команда. (возможно, если будут редиректы, надо будет вернуть взад)
	if (!check_command(line, com))
			com->no_command = 0;
	if (!check_env_var(line, com))
		com->no_var = 0;
	if (!check_arg(line, com))
		com->no_arg = 0;
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
	{
		// pars_command(line, com);
		// pars_flags(line, com);
		// pars_variables(line, com);
		
		if  (check_mistakes(line, com))	
			break ; // тут возможно надо всякие экситы и прочее гавно реализовывать
		new = com->arg;
		if (!com->no_var)
			check_tockens(line, com);
		else
		{
			com->arg->arg = ft_strdup(com->env_var);
			free(com->env_var);
			com->env_var = NULL;
			com->no_var = 0;
		}
		com->arg = com->arg->next;
		init_arg(com);
		// (*line)++; // или тут это вообще не нужно, или еще нужно как  (*line)++
		// com->comd = com->comd->next;
		// init_comd(com);
	}
	// com->comd = new;
}

void	check_tockens(char **line, t_command *com)
{
	int		len;
	
	while (**line == ' ')
		(*line)++;
	len = ft_strlen_space(*line);
	if (len > ft_strlen_char(*line, ';') && !check_open_quotes(line, ft_strlen_char(*line, ';')))
		len = ft_strlen_char(*line, ';');
	if (!len)
		com->arg->no_arg = 0;
	else if (!(**line == '|') && !(**line == '"') && !(**line == '\'') && !(**line == '\\') && !(**line == '>') && !(**line == '<'))
	{
		com->arg->arg = ft_substr(*line, 0, len);
		(*line) += len;	
	}
	else if (**line == '"')
		pars_double_quotes(line, com); // это различают спецсимволы
	else if (**line == '\'')
		pars_single_quotes(line, com);
	else if (**line == '|')
		activate_pipe(line, com); // функция для пайпа
	else if (**line == '>')
		pars_redirect(line, com);
	else if (**line == '<')
		pars_reverse_redirect(line, com);
	check_pipe(line, com);
}

int		check_open_quotes(char **line, int len)
{
	int	len_qu;
	int	len_qu_2;

	len_qu = ft_strlen_char(*line, '\''); // длина будет равна или расстоянию до кавычки, или расстоянию до конца line
	if (len_qu != ft_strlen(*line))
		len_qu_2 = t_strlen_char(*line + len_qu + 1, '\''); //длина будет равна длине от следующего символа после первой кавычки до второй кавычки или до конца строки
	else 
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2) // если ; между кавычками или стоит после первой кавычки, а второй нет (возможно нужно тут переделать на только если есть обе кавычки)
		return (1);
	len_qu = ft_strlen_char(*line, '"'); // длина будет равна или расстоянию до кавычки, или расстоянию до конца line
	if (len_qu != ft_strlen(*line))
		len_qu_2 = t_strlen_char(*line + len_qu + 1, '"'); //длина будет равна длине от следующего символа после первой кавычки до второй кавычки или до конца строки
	else 
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2) // если ; между кавычками или стоит после первой кавычки, а второй нет (возможно нужно тут переделать на только если есть обе кавычки)
		return (1);
	return (0);
}

void	pars_single_quotes(char **line, t_command *com)
{
	int	len;

	len = ft_strlen_char(*line, '\'');
	// com->quotes_op = 1;
	com->arg->arg = ft_substr(*line, 1, len - 2);
	(*line) += len;
}

void	pars_double_quotes(char **line, t_command *com)
{
	int len;
	int	len_env;
	
	len = ft_strlen_char(*line, '"');
	len_env = 0;
	if (len == ft_strlen(*line))
		com->arg->arg = ft_substr(*line, 1, len - 1);
	else
	{
		com->arg->arg = ft_substr(*line, 1, len - 1);
		if (ft_strchr(com->arg->arg, '$'))
		{
			len_env = check_env_var(ft_strchr(com->arg->arg, '$'), com);
		}	
			
	}
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
			change_env_var_meaning(com);
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
		if (i - 1)
			com->no_var += 1;
		(*line) += (i - 1);
		return (i - 1);
	}
	return (0);
}

void	change_env_var_meaning(t_command *com)
{
	int	i;
	int	len;
	int	len_env;

	i = 0;
	len = ft_strlen(com->env_var);
	if (com->env_def)
	{
		while(com->env_def[i] && (ft_strncmp(com->env_def[i], com->env_var, len)) && i > -1)
		{
			i++;
			len_env = 0;
			if(com->env_def[i] && !(ft_strncmp(com->env_def[i], com->env_var, len)))
			{
				while (com->env_def[i][len_env] != '=')
					len_env++;
				if (len == len_env)
				{
					free(com->env_var);
					com->env_var = NULL;
					com->env_var = ft_strdup(com->env_def[i] + len_env);
					i = -1;
				}
			}
		}
		if (!com->env_def[i])
			com->no_var = 0; // `если переменной нет, то ничего не происходит		
	}
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

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != c)
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

char	*ft_strchr(const char *str, int sym)
{
	int i;

	i = 0;
	if (str[i] == sym)
		return ((char*)str);
	while (str[i])
	{
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
		i++;
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
	}
	return (NULL);
}
