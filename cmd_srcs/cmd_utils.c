/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:53:08 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 15:25:14 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_my(char *cmd, t_command *com)
{
	const char	*my_str[7] = {"echo", "cd", "pwd", "export", "unset", "env",
							"exit"};
	int			i;
	int			cmd_num;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(cmd, my_str[i]))
			cmd_num = i;
	if (cmd_num == 0)
		com->com_ret = cmd_echo(com);
	else if (cmd_num == 1)
		com->com_ret = cmd_cd(com);
	else if (cmd_num == 2)
		com->com_ret = cmd_pwd(com);
	else if (cmd_num == 3)
		com->com_ret = cmd_export(com);
	else if (cmd_num == 4)
		com->com_ret = cmd_unset(com);
	else if (cmd_num == 5)
		com->com_ret = cmd_env(com);
	else if (cmd_num == 6)
		com->com_ret = cmd_exit(com);
}

int		struct_len(t_env *tmp)
{
	int		len;

	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**envp_to_mass(t_command *com)
{
	char	**envp;
	char	*tmp_line;
	t_env	*tmp;
	int		i;

	tmp = com->env_def;
	if (!(envp = (char **)ft_calloc(sizeof(char *), struct_len(tmp) + 1)))
		return ((error_message2(strerror(errno))));
	tmp = com->env_def;
	i = 0;
	while (tmp)
	{
		if (tmp->meaning)
		{
			if (!(tmp_line = ft_strjoin(tmp->env, "=")))
				return (error_message2(strerror(errno)));
			if (!(envp[i] = ft_strjoin(tmp_line, tmp->meaning)))
				return (error_message2(strerror(errno)));
			free(tmp_line);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**transfer_to_mass(t_command *com)
{
	char	**args;
	t_arg	*tmp_a;
	int		len;
	int		i;

	len = 0;
	i = 0;
	tmp_a = com->comd->arg;
	while (tmp_a)
	{
		len++;
		tmp_a = tmp_a->next;
	}
	if (!(args = (char **)ft_calloc(sizeof(char *), len + 1)))
		return (error_message2(strerror(errno)));
	tmp_a = com->comd->arg;
	while (tmp_a)
	{
		if (!(args[i++] = ft_strdup(tmp_a->arg)))
			return (error_message2(strerror(errno)));
		tmp_a = tmp_a->next;
	}
	args[i] = NULL;
	return (args);
}
