/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/01 17:21:56 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char **line, t_command *com)
{
	pars_pipes(*line, com);
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
		pars_tockens(line, com);
	write(1, "end of parser\n", 14);
	// pars_variables(blocks, com);
}

void	pars_pipes(char *line, t_command *com)
{
	while (line && *line)
	{
		if (*line == '|')
			com->pipe_count++;
		line++;
	}
	com->no_command = com->pipe_count + 1; // надо вспомнить зачем это и как можно использовать
	com->no_arg = com->pipe_count + 1;
}

void	pars_tockens(char **line, t_command *com)
{
	t_arg	*new;

	new = com->arg;
	if (!check_command(line, com))
			com->no_command = 0;
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
	{
		// if  (check_mistakes(line, com))	
		// 	break ; // тут возможно надо всякие экситы и прочее гавно реализовывать
		init_arg(com);
		if (!check_env_var(line, com))
			com->no_var = 0;
		if (!com->no_var)
			check_tockens(line, com);
		else
		{
			com->arg->arg = ft_strdup(com->env_var);
			free(com->env_var);
			com->env_var = NULL;
			com->no_var = 0;
		}
		ft_argadd_back(&new, com->arg);
	}
	com->arg = new;
}

void	check_tockens(char **line, t_command *com)
{
	size_t	len;
	
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
	// else if (**line == '|')
	// 	activate_pipe(line, com); // функция для пайпа
	// else if (**line == '>')
	// 	pars_redirect(line, com);
	// else if (**line == '<')
	// 	pars_reverse_redirect(line, com);
	// check_pipe(line, com);
}

int		check_open_quotes(char **line, size_t len)
{
	size_t	len_qu;
	size_t	len_qu_2;

	len_qu = ft_strlen_char(*line, '\''); // длина будет равна или расстоянию до кавычки, или расстоянию до конца line
	if (len_qu != ft_strlen(*line))
		len_qu_2 = ft_strlen_char(*line + len_qu + 1, '\''); //длина будет равна длине от следующего символа после первой кавычки до второй кавычки или до конца строки
	else 
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2) // если ; между кавычками или стоит после первой кавычки, а второй нет (возможно нужно тут переделать на только если есть обе кавычки)
		return (1);
	len_qu = ft_strlen_char(*line, '"'); // длина будет равна или расстоянию до кавычки, или расстоянию до конца line
	if (len_qu != ft_strlen(*line))
		len_qu_2 = ft_strlen_char(*line + len_qu + 1, '"'); //длина будет равна длине от следующего символа после первой кавычки до второй кавычки или до конца строки
	else 
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2) // если ; между кавычками или стоит после первой кавычки, а второй нет (возможно нужно тут переделать на только если есть обе кавычки)
		return (1);
	return (0);
}

void	pars_single_quotes(char **line, t_command *com)
{
	size_t	len;

	len = ft_strlen_char(*line + 1, '\'');
	// com->quotes_op = 1;
	com->arg->arg = ft_substr(*line, 1, len);
	(*line) += len;
}

void	pars_double_quotes(char **line, t_command *com)
{
	size_t 	len;
	size_t	len_env;
	char	*buf;
	size_t	len_buf;
	char	*buf_2;
	
	len = ft_strlen_char(*line + 1, '"');
	len_env = 0;
	if (len == ft_strlen(*line + 1) && (*line)[len - 1] != '"') // а что, если последний символ - кавычка?
		com->arg->arg = ft_substr(*line, 1, len - 1);
	else
	{
		com->arg->arg = ft_substr(*line, 1, len); // тут возможно минус 2 надо делать
		while ((len_buf = ft_strlen(ft_strchr(com->arg->arg, '$'))))
		{
			buf = ft_strchr(com->arg->arg, '$');
			len_env = check_env_var(&buf, com); // тут я посчитала длину переменной окружения вместе с долларом
			buf = ft_substr(com->arg->arg, 0, len - len_buf);
			buf_2 = ft_substr(com->arg->arg, ft_strlen(buf) + len_env + 1, len_buf - len_env + 2); // возможно тут нужно сделать -1
			change_env_var_meaning(com);
			if (com->no_var)
			{
				free(com->arg->arg);
				com->arg->arg = NULL;
				com->arg->arg = ft_strjoin_gnl(buf, com->env_var);
				com->arg->arg = ft_strjoin_gnl(com->arg->arg, buf_2);
				free(buf_2);
			}
		}
	}
	(*line) += len;
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
	if (!(ft_strncmp(*line, command, i)) || !(ft_strncmp(*line, ft_strjoin_gnl(ft_strdup(command), " "), i)))
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
	size_t	i;

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

void	copy_env(char **env, t_command *com)  // взять листы из либы и просто пушить в конец
{
	t_env	*new;
	t_env	*buf;
	size_t	i;
	size_t	len;
	size_t	len_2;
	
	i = 0;
	len = 0;
	buf = com->env_def;
	while(env && env[i])
	{
		new = (t_env*)malloc(sizeof(t_env));
		new->env = NULL;
		new->meaning = NULL;
		new->next = NULL;
		len = ft_strlen_char(env[i], '=');
		len_2 = ft_strlen(env[i]);
		new->env = ft_substr(env[i], 0, len);
		new->meaning = ft_substr(env[i], len + 1, len_2 - (len + 1));
		ft_envadd_back(&buf, new);
		i++;
	}
	com->env_def = buf;
}

void	change_env_var_meaning(t_command *com) // нужно переписать
{
	size_t	i;
	size_t	len;
	// size_t	len_env;
	t_env	*new;

	i = 0;
	new = com->env_def;
	len = ft_strlen_space(com->env_var);
	while(com->env_def)
	{
		if (!(ft_strncmp(com->env_def->env, com->env_var, len)))
		{
			free(com->env_var);
			com->env_var = NULL;
			com->env_var = ft_strdup(com->env_def->meaning);
			break ;
		}
		com->env_def = com->env_def->next;
	}
	if (!com->env_def)
		com->no_var = 0;
	com->env_def = new;
}



size_t	ft_strlen_space(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

size_t	ft_strlen_char(char *str, char c)
{
	size_t	i;

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

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*bonus;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus)
	{
		while (bonus->next)
			bonus = bonus->next;
		bonus->next = new;
	}
	else
		*lst = new;
}

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*bonus;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus)
	{
		while (bonus->next)
			bonus = bonus->next;
		bonus->next = new;
	}
	else
		*lst = new;
}