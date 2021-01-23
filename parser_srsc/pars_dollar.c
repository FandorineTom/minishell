/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:27:49 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/23 18:49:56 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_dollar(t_command *com, size_t len_str)
{
	char	*buf;
	char	*buf_end;
	char	*tmp;

	buf = NULL;
	buf_end = NULL;
	tmp = com->comd->arg->arg;
	while (com->comd->arg->arg && *com->comd->arg->arg)
	{
		pars_dollar_2(com, len_str, &buf);
		if (*com->comd->arg->arg == '\\' && com->comd->arg->arg[1] == '$' &&
			(com->comd->arg->arg += 2))
			buf = ft_strjoin_gnl(&buf, "$");
		else if (*com->comd->arg->arg == '$')
			start_dollar(com, &buf, &buf_end);
		else if (*com->comd->arg->arg == '\\')
		{
			while (*com->comd->arg->arg == '\\' && (com->comd->arg->arg++))
				buf = ft_strjoin_gnl(&buf, "\\");
		}
	}
	com->comd->arg->arg = buf;
	free(buf_end);
	free(tmp);
}

void	pars_dollar_2(t_command *com, size_t len_str, char **buf)
{
	size_t	len_slash;
	char	*tmp;

	len_slash = ft_strlen_char(com->comd->arg->arg, '\\');
	if (len_slash < len_str && len_slash < ft_strlen_char(\
		com->comd->arg->arg, '$') && len_str != 1)
	{
		tmp = ft_substr(com->comd->arg->arg, 0, len_slash);
		*buf = ft_strjoin_gnl(buf, tmp);
		com->comd->arg->arg += len_slash;
		free(tmp);
	}
	else if (len_str == 1)
	{
		*buf = ft_substr(com->comd->arg->arg, 0, 1);
		com->comd->arg->arg += 1;
	}
	else
	{
		tmp = ft_substr(com->comd->arg->arg, 0, \
			ft_strlen_char(com->comd->arg->arg, '$'));
		*buf = ft_strjoin_gnl(buf, tmp);
		com->comd->arg->arg += ft_strlen_char(com->comd->arg->arg, '$');
		free(tmp);
	}
}

void	start_dollar(t_command *com, char **buf, char **buf_end)
{
	size_t	len_var;

	len_var = ft_strlen_space(com->comd->arg->arg);
	if (len_var > ft_strlen_char(com->comd->arg->arg, '\\'))
		len_var = ft_strlen_char(com->comd->arg->arg, '\\');
	if (len_var > ft_strlen_char(com->comd->arg->arg, '"'))
		len_var = ft_strlen_char(com->comd->arg->arg, '"');
	if (len_var > ft_strlen_char(com->comd->arg->arg, '\''))
		len_var = ft_strlen_char(com->comd->arg->arg, '\'');
	*buf_end = ft_substr(com->comd->arg->arg, len_var, \
		ft_strlen(com->comd->arg->arg) - len_var);
	com->env_var = ft_substr(com->comd->arg->arg, 1, len_var - 1);
	if (len_var > 1)
		change_env_var_meaning(com);
	*buf = ft_strjoin_gnl(buf, com->env_var);
	free(com->env_var);
	com->env_var = NULL;
	com->comd->arg->arg = *buf_end;
}
