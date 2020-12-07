/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/07 22:20:01 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char **line, t_command *com)
{
	if (**line == ';')
	{
		(*line)++;
		free_all(com, 1); // предыдущие элементы структуры не нужны, поэтому всё зачищаем
		init_com(com);
	}
	while (**line == ' ')
		(*line)++;
	pars_pipes(*line, com);
	while (line && *line && **line && **line != ';')
		pars_tockens(line, com);
	write(1, "end of parser\n", 14); // чисто для теста, потом нужно убрать
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

	new = NULL;
	if (!check_command(line, com))
			com->no_command = 0;
	while (line && *line && **line && **line != ';')
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
			change_env_var_meaning(com);
			com->arg->arg = ft_strdup(com->env_var);
			free(com->env_var);
			com->env_var = NULL;
			com->no_var = 0;
		}
		if (com->arg->arg) // возможно это не нужно
			ft_argadd_back(&new, com->arg);
	}
	com->arg = new; // тут создается лишний лист с пустыми элементами в начале. надо найти откуда он и убрать
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

	while (**line == '\'')
	{
		len = ft_strlen_char(*line + 1, '\'');
	// com->quotes_op = 1;
		if (len)
			com->arg->arg = ft_strjoin_gnl(com->arg->arg, ft_substr(*line, 1, len));
		(*line) += len + 2;
	}
}

void	pars_double_quotes(char **line, t_command *com)
{
	size_t 	len;
	size_t	len_env;
	
	len = ft_strlen_char(*line + 1, '"');
	while (*(*line + len) == '\\')
		len = len + ft_strlen_char(*line + len + 2, '"') + 1;
	len_env = 0;
	if (len == ft_strlen(*line + 1) && (*line)[len - 1] != '"') // а что, если последний символ - кавычка?
	{
		com->arg->arg = ft_substr(*line, 1, len);
		(*line) += len + 1;
	}
	else
	{
		com->arg->arg = ft_substr(*line, 1, len); // тут возможно минус 2 надо делать
		if (ft_strchr(com->arg->arg, '$'))
			pars_dollar(com, len);
		if (ft_strchr(com->arg->arg, '\\'))
			pars_escaping(com, len); // нужно написать функцию парсинга сранного экранирования (экранировать тут уже нужно только знак экранирования и кавычку)
		(*line) += len + 2;
	}
	
}

void	pars_escaping(t_command *com, size_t len_str)
{
	char	*buf;
	// char	*buf_end;
	size_t	len_slash;

	buf = NULL;
	(void)len_str;
	// buf_end = NULL;
	while (com->arg->arg && *com->arg->arg)
	{
		len_slash = ft_strlen_char(com->arg->arg, '\\');
		buf = ft_strjoin_gnl(buf, ft_substr(com->arg->arg, 0, len_slash));
		com->arg->arg += len_slash;
		if (*com->arg->arg && *(com->arg->arg + 1))
		{
			if (*(com->arg->arg + 1) == '"' || *(com->arg->arg + 1) == '\\')
				buf = ft_strjoin_gnl(buf, ft_substr(com->arg->arg, 1, 1));
			else
				buf = ft_strjoin_gnl(buf, ft_substr(com->arg->arg, 0, 2));
			com->arg->arg += 2;
		}
	}
	com->arg->arg = buf;
}

void 	pars_dollar(t_command *com, size_t len_str)
{
	char	*buf; // сюда записываю переработанные куски.
	char	*buf_end;
	size_t	len_slash;
	size_t	len_dol;
	size_t	len_var;

	buf = NULL;
	buf_end = NULL;
	while (com->arg->arg && *com->arg->arg)
	{
		len_slash = ft_strlen_char(com->arg->arg, '\\');
		len_dol = ft_strlen_char(com->arg->arg, '$');
		if (len_slash < len_str && len_slash < len_dol)
		{
			buf = ft_strjoin_gnl(buf, ft_substr(com->arg->arg, 0, len_slash)); //тут должна скопировать до бекслеша
			com->arg->arg += len_slash;
		}
		else // если ни слеша, ни доллара, то строчка скопируется до конца
		{
			buf = ft_strjoin_gnl(buf, ft_substr(com->arg->arg, 0, ft_strlen_char(com->arg->arg, '$'))); // тут должна скопировать до знака доллар
			com->arg->arg += ft_strlen_char(com->arg->arg, '$');
		}
		if (*com->arg->arg == '\\' && com->arg->arg[1] == '$')
		{
			buf = ft_strjoin_gnl(buf, "$");
			com->arg->arg += 2; // сместила на текст после $
		}
		else if (*com->arg->arg == '$')
		{
			len_var = ft_strlen_space(com->arg->arg); // тут или до пробела, или до экранирования - что из этого будет ближе
			if (len_var > ft_strlen_char(com->arg->arg, '\\'))
				len_var = ft_strlen_char(com->arg->arg, '\\');
			buf_end = ft_substr(com->arg->arg, len_var, ft_strlen(com->arg->arg) - len_var); // тут лучше просто переместить указатель, возможно? чтобы новую память не выделять
			com->env_var = ft_substr(com->arg->arg, 1, len_var - 1);
			change_env_var_meaning(com);
			buf = ft_strjoin_gnl(buf, com->env_var);
			com->arg->arg += len_var;
			free(com->env_var);
			com->env_var = NULL;
			// free(com->arg->arg);
			com->arg->arg = buf_end;
		}
		else if (*com->arg->arg == '\\')
		{
			while (*com->arg->arg == '\\')
			{
				buf = ft_strjoin_gnl(buf, "\\");
				com->arg->arg++;
			}
		}
	}
	// if (com->arg->arg)
	// 	free(com->arg->arg);
	com->arg->arg = buf;
}

int		check_command(char **line, t_command *com)
{
	if (check_which_command(line, com, "echo", 5))
		return (check_echo_flag(line, com));
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

int		check_echo_flag(char **line, t_command *com) // тут еще долбанные кавычки
{
	int	i;
	int	flag;
	int	quotes;

	i = 0;
	flag = 0;
	quotes = 0;
	while ((*line)[i] == ' ')
		i++;
	if ((*line)[i] == '"' || (*line)[i] == '\'')
	{
		if ((*line)[i] == '"')
			quotes = 2;
		if ((*line)[i] == '\'')
			quotes = 1;
		i++;
	}	
	if ((*line)[i] == '-')
		flag = check_flag_n((*line) + i + 1, quotes); // возвращается длина, занимаемая флагом (до конца ковычек)
	if (flag)
	{
		com->comd->flag->flag = (char *)malloc(3);
		com->comd->flag->flag[0] = '-';
		com->comd->flag->flag[1] = 'n';
		com->comd->flag->flag[2] = '\0';
		(*line) += flag + i;
	}
	else
		com->comd->flag->no_flag = 0;
	// if ((*line)[i] == '-' && (*line)[i + 1] == 'n') // && ((*line)[i + 2] == 'n' || (*line)[i + 2] == ' '))
	// {
	// 	i += 2;
	// 	while ((*line)[i] == 'n')
	// 		i++;
	// 	com->comd->flag->flag = (char *)malloc(3);
	// 	com->comd->flag->flag[0] = '-';
	// 	com->comd->flag->flag[1] = 'n';
	// 	com->comd->flag->flag[2] = '\0';
	// }	
	return (1);
}

int	check_flag_n(char *line, int quotes) // приходит линия, начиная с n (где то нужно прибавлять, только если ноль не вернула функция)
{
	int	i;

	i = 0;
	while (line[i] == 'n')
		i++;
	if (quotes == 0 && line[i] != ' ')
		return (0);
	if (quotes == 2 && line[i] != '"')
		return (0);
	if (quotes == 1 && line[i] != '\'')
		return (0);
	if (quotes)
		i++;
	if (line[i] != ' ')
		return (0);
	while (line[i] == ' ')
		i++;
	if (line[i] == '"' || line[i] == '\'')
	{
		if (line[i] == '"')
			quotes = 2;
		if (line[i] == '\'')
			quotes = 1;
		i++;
	}
	else
		quotes = 0;
	if (line[i] == '-')
		i += check_flag_n(line + i + 1, quotes) + 1; // если кавычек нет, то + 1 не нужен
	return (i);
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

	while (**line == ' ')
		(*line)++;
	i = ft_strlen_space(*line);
	if (i > ft_strlen_char(*line, '\''))
		i = ft_strlen_char(*line, '\'');
	if (i > ft_strlen_char(*line, '"'))
		i = ft_strlen_char(*line, '"');
	if (**line == '$')
	{
		if (!(com->env_var = ft_substr(*line, 1, i - 1))) // скорее всего минус 1 не нужен
			return (0);
		if (i - 1)
			com->no_var += 1;
		(*line) += i;
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
	{
		com->no_var = 0;
		if (!ft_strncmp("?", com->env_var, len))
		{
			free(com->env_var);
			com->env_var = NULL;
			com->env_var = ft_strdup("0");
		}
		else
		{
			free(com->env_var);
			com->env_var = NULL;
			com->env_var = ft_strdup("");
		}
		
	}
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