/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:49:55 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 21:21:58 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (check_command(&com->env_var, com));
	}
	com->comd->flag->no_flag = 0;
	return (0);
}

int		check_echo_flag(char **line, t_command *com)
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
		flag = check_flag_n((*line) + i + 1, quotes);
	if (flag && ((*line) += flag + i))
		com->comd->flag->flag = ft_strdup("-n");
	else
		com->comd->flag->no_flag = 0;
	return (1);
}

int		check_flag_n(char *line, int quotes)
{
	int	i;

	i = 0;
	while (line[i] == 'n')
		i++;
	if ((quotes == 0 && line[i] != ' ' && line[i] != '\0') || (quotes == 2 &&
		line[i] != '"') || (quotes == 1 && line[i] != '\''))
		return (0);
	if (quotes)
		i++;
	if (line[i] != ' ' && line[i] != '\0')
		return (0);
	while (line[i] == ' ')
		i++;
	if (line[i] == '"' || line[i] == '\'')
		define_quotes(&quotes, line, i++);
	else
		quotes = 0;
	if (line[i] == '-')
		i += check_flag_n(line + i + 1, quotes) + 1;
	if (line[i] == '\0')
		i++;
	return (i);
}

void	define_quotes(int *quotes, char *line, int i)
{
	if (line[i] == '"')
		*quotes = 2;
	if (line[i] == '\'')
		*quotes = 1;
}

int		check_which_command(char **line, t_command *com, char *command, int i)
{
	char	*buf;
	char	*buf_2;
	
	buf = ft_strdup(command);
	buf_2 = ft_strdup(command);
	if (!(ft_strncmp(*line, command, i)) || !(ft_strncmp(*line, \
		(buf = ft_strjoin_gnl(&buf, " ")), i)) ||
		!(ft_strncmp(*line, (buf_2 = ft_strjoin_gnl(&buf_2, ";")), i)))
	{
		if (!(com->comd->cmnd = ft_strdup(command)))
			return (0);
		(*line) += i - 1;
		free(buf);
		free(buf_2);
		return (1);
	}
	free(buf);
	free(buf_2);
	return (0);
}
