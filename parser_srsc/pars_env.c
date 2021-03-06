/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:27:57 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/27 17:30:59 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_env_var(char **line, t_command *com)
{
	size_t	i;

	skip_spaces(line);
	i = ft_strlen_space(*line);
	if (i > ft_strlen_char(*line, '\''))
		i = ft_strlen_char(*line, '\'');
	if (i > ft_strlen_char(*line, '='))
		i = ft_strlen_char(*line, '=');
	if (i > ft_strlen_char(*line, '"'))
		i = ft_strlen_char(*line, '"');
	if (i > ft_strlen_char(*line, ';'))
		i = ft_strlen_char(*line, ';');
	if (i > ft_strlen_char(*line, '\\'))
		i = ft_strlen_char(*line, '\\');
	if (i > ft_strlen_char(*line + 1, '$') + 1)
		i = ft_strlen_char(*line + 1, '$') + 1;
	if (**line == '$')
	{
		if (!(com->env_var = ft_substr(*line, 1, i - 1)))
			return (0);
		if (i == 1)
			com->comd->arg->arg = ft_strdup("$");
		if (i - 1)
			com->no_var += 1;
		(*line) += i;
		return (i - 1);
	}
	return (0);
}

void	copy_env(char **env, t_command *com)
{
	t_env	*new;
	t_env	*buf;
	size_t	i;
	size_t	len;
	size_t	len_2;

	i = 1;
	len = ft_strlen_char(env[0], '=');
	len_2 = ft_strlen(env[0]);
	com->env_def->env = ft_substr(env[0], 0, len);
	com->env_def->meaning = ft_substr(env[0], len + 1, len_2 - (len + 1));
	buf = com->env_def;
	while (env && env[i])
	{
		new = (t_env*)malloc(sizeof(t_env));
		new->env = NULL;
		new->meaning = NULL;
		new->next = NULL;
		len = ft_strlen_char(env[i], '=');
		len_2 = ft_strlen(env[i]);
		new->env = ft_substr(env[i], 0, len);
		new->meaning = ft_substr(env[i++], len + 1, len_2 - (len + 1));
		ft_envadd_back(&buf, new);
	}
	com->env_def = buf;
}

void	change_env_var_meaning(t_command *com)
{
	size_t	len;
	t_env	*new;

	new = com->env_def;
	len = ft_strlen_space(com->env_var);
	while (com->env_def)
	{
		if (!(ft_strncmp(com->env_def->env, com->env_var, len + 1)) && len)
		{
			free(com->env_var);
			com->env_var = NULL;
			com->env_var = ft_strdup(com->env_def->meaning);
			break ;
		}
		com->env_def = com->env_def->next;
	}
	if (!com->env_def)
		no_such_env(com, len);
	com->env_def = new;
}

void	no_such_env(t_command *com, size_t len)
{
	com->no_var = 0;
	if (!ft_strncmp("?", com->env_var, len))
	{
		free(com->env_var);
		com->env_var = NULL;
		if (g_c_flag == 1)
			com->com_ret = 1;
		g_c_flag = 0;
		com->env_var = ft_itoa((int)com->com_ret);
	}
	else
	{
		free(com->env_var);
		com->env_var = NULL;
		com->env_var = ft_strdup("");
	}
}

void	change_env(t_command *com)
{
	change_env_var_meaning(com);
	com->comd->arg->arg = ft_strdup(com->env_var);
	free(com->env_var);
	com->env_var = NULL;
	com->no_var = 0;
}
