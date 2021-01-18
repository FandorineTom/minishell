/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:49:11 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/18 12:22:37 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
void	check_parser(t_command com)
{
	int i = 0;
	
	if (com.comd->cmnd)
		printf("command is %s\n", com.comd->cmnd);
	else
		printf("no command\n");
	if (com.comd->flag->flag)
		printf("flag is %s\n", com.comd->flag->flag);
	else
		printf("no flag\n");
	if (com.comd->arg)
	{
		while (com.comd->arg->next)
		{
			i++;
			printf("argument %d = |%s|\n", i, com.comd->arg->arg);
			// com.comd->arg->previous = com.comd->arg;
			com.comd->arg = com.comd->arg->next;
		}
		i++;
		printf("argument %d = |%s|\n", i, com.comd->arg->arg);
	}
	else
		printf("no arguments\n");
	while (com.comd->arg && com.comd->arg->previous)
		com.comd->arg = com.comd->arg->previous;
}

int	minishell_loop(t_command * com)
{
	char	*tmp;
	char	*line;

	if (g_c_flag)
		free_all(com, 1);
	g_c_flag = 0;
	while (1) // тут может быть на какой-то сигнал прекращение цикла записать
	{
		write(1, "our_minishell_almost_work: ", 27); // тут надо что-то поизящнее зафигачить и чтобы оно висело и выводилось после (может, тупо, while (1))
		if (!(get_next_line(0, &line)))
			ctrl_d(com);
		com->error = 0;
		check_mistakes(&line, com);
		tmp = line;
		save_stdin_out();
		while (line && *line && !com->error)
		{
			if (!com->error)
				parser(&line, com); 
			start_redirect(com);
			if (!com->error)
				cmd_start(com);
			if (*line == ';' && *(line + 1) == '\0')
				break ;
		}
		return_stdin_out();
		free_all(com, 1);
		activate_pipe(NULL, NULL);
		init_com(com);
		free(tmp);
		tmp = NULL;
		// work_comman(&com);
	}
}

int	main(int argc, char **argv, char **env) // нужно как-то принять переменные окружения
{
	// char		*line;
	t_command	com;
	// char		*tmp;

	(void)argc;
	(void)argv;
	init_com(&com);
	init_env_d(&com);
	// init_env_def(com.env_def);
	copy_env(env, &com);
	com.com_ret = 0;
	g_c_flag = 0;
	g_b_flag = 0;
	signal_handler(&com);
	minishell_loop(&com);
	// while (1) // тут может быть на какой-то сигнал прекращение цикла записать
	// {
	// 	write(1, "our_minishell_almost_work: ", 27); // тут надо что-то поизящнее зафигачить и чтобы оно висело и выводилось после (может, тупо, while (1))
	// 	get_next_line(0, &line);
		
	// 	// init_com(&com);
	// 	com.com_ret = 0;
	// 	com.error = 0;
	// 	// copy_env(env, &com); // может это можно вынести из цикла (только тогда надо заранее инициализировать ком)
	// 	check_mistakes(&line, &com);
	// 	tmp = line;
	// 	save_stdin_out();
	// 	while (line && *line && !com.error)
	// 	{
	// 		if (!com.error)
	// 			parser(&line, &com); // тут надо прописать так, чтобы обрабатывать только до ; и потом снова вызывать парсер, а строку обрезать
	// 		// if (com.comd->redir && com.comd->redir->r_redir)
	// 		// 	file_open(&com);
	// 		start_redirect(&com);
	// 		// check_parser(com); // это просто для проверки парсера
	// 		if (!com.error)
	// 			cmd_start(&com);
	// 		// if (com.comd->redir && com.comd->redir->r_redir)
	// 		// 	file_close(&com);                           я закрываю их сразу же после использования, предлагаю здесь убрать
	// 		if (*line == ';' && *(line + 1) == '\0')
	// 			break ;
	// 		// возможно тут нужно поработать с пайпами, т.е если есть правый, то закрыть, открыть fd
	// 		// тут исполняется одна распарсенная команда до точки с запятой и идет дальше
	// 		// а тут возможно нужно переоткрыть пайпы
	// 		//тут нужно вернуть fdшники на свои места
	// 	}
	// 	return_stdin_out();
	// 	free_all(&com, 1);
	// 	activate_pipe(NULL, NULL);
	// 	init_com(&com);
	// 	free(tmp);
	// 	tmp = NULL;
	// 	// work_comman(&com);
	// }
	free_all(&com, 0);
	return (0);
}

// void	function(int signal) // нужно написать функцию function_signal2, которая в зависимости от кода будет печатать промпт
// {
// 	printf("%d\n", signal);
// 	if (signal == 2)
// 		signal(SIGINT, function_signal2);
// 	if (signal == 3)
// 		signal(SIGOUT, function_signal2);

// }
// изменение в дочернем процессе не меняет ничего в родительском
// в парсере нужно сделать, если есть переменная окружения, то 
// сравнить с имеющимися - и если она равна команде, то заполнить команду
// как сделать командную строку, чтобы туда набивать команды и парсить?
// кавычки
// экранирование (без кавычек экранирует всё, в двойных кавычках - выборочно, в одинарных - ничего)
// $
// одинарные vs двойные кавычки (двойные - позволяют считывать переменные 
// внутри, одинарные тупо считывают как текст - не работает ни экранирование, ни доллар, ничего)
// если одинарные внурти двойных - одинарные не работают
// если двойные внутри одинарных - тоже не срабоют
// предусмотреть случай, когда нет парной кавычки - это андефайн, но чтобы не было сеги
// в двойных кавычках экранируется - двойная кавычка, знак экранирования, $ (есть еще, но них забивают)
// чем отличается | от ;?
// тест case export $abc=12345 ; echo $abc
// в какой момент заменять переменные на их значения? (в парсере), но парсер отрабатывается несколько раз
// разделитель только пробел и спецсимволы, кавычки не разделители и e''cho == echo
// пайп в кавычках - не работает как пайп. т.е. сплит лесом - просто парсим до ; и внутри ищем пайпы
// когда встречаем пайп, вызываем функцию, которая делит fdшники и куда-то записывает и команда 
// выполняется не в терминал, а в другой фд
// после отработки строки команды с пайпами нужно вернуть оригинальный фд на родину
// если редирект и пайп, то пайп отработает, только если редирект не в его сторону
// в двойных кавычках экранирование срабатывает только на само себя и на $ (и на двойную кавычку). остальное обрабатывать не надо
// экранирование двойной кавычки
