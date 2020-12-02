/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:49:11 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/02 12:20:59 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) // нужно как-то принять переменные окружения
{
	char		*line;
	t_command	com;

	(void)argc;
	(void)argv;
	write(1, "my_minishell: ", 14); // тут надо что-то поизящнее зафигачить и чтобы оно висело
	get_next_line(0, &line);
	init_com(&com);
	com.error = 0;
	copy_env(env, &com);
	while (line && *line && !com.error)
		{
			parser(&line, &com); // тут надо прописать так, чтобы обрабатывать только до ; и потом снова вызывать парсер, а строку обрезать
			// тут исполняется одна распарсенная команда до точки с запятой и идет дальше
		}

	// work_comman(&com);
	// free_all(&com, 0);
	return (0);
}

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