# minishell
я там добавила функцию очистки структур, которую использую после того, как мы выполнили соответствующую команду (т.е. дошли до точки с запятой). после этого вся структура, кроме env_def (т.е. переменные окружения) зачищается. 
почекала, вроде нормально обрабатывается на простых кейсах. 
в плане работ следующее:
1. обработка ошибок (несколько редиректов подряд, несуществующие команды и т.п.)
2. парсинг флага -n для echo (он будет лежать в структуре comd в подструктуре flag). для тех команд, которые нерукописные, флаги будут парсится не как флаги, а как аргументы (поскольку и сами команды будут парсится как аргументы).
3. пайпы и редиректы. 
4. добавить в парсере команд, чтобы капслочные команды тоже парсились. 
5. починить $, если переменной не существует
6. $?
