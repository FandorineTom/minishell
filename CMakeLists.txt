cmake_minimum_required(VERSION 3.17)
project(merge_proj C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(headers)
include_directories(libft)

add_executable(merge_proj
        headers/get_next_line.h
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
#        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        libft/ft_lstclear.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstlast.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putnbr_unint.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strcat_bonus.c
#        libft/ft_strchr.c
        libft/ft_strcmp_bonus.c
        libft/ft_strcpy_bonus.c
#        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
#        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncat_bonus.c
#        libft/ft_strncmp.c
        libft/ft_strncpy_bonus.c
        libft/ft_strnlen_bonus.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strstr_bonus.c
        libft/ft_strtrim.c
        libft/ft_strtrimwhole_bonus.c
#        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/libft.h
        check_mistakes.c
        cmd_cd.c
        cmd_echo.c
        cmd_env.c
        cmd_exit.c
        cmd_export.c
        cmd_pwd.c
        cmd_start.c
        cmd_unset.c
        error.c
        free_struct.c
        ft_itoa.c
        get_next_line.c
        get_next_line.h
        get_next_line_utils.c
        inits.c
        main.c
        minishell.c
        minishell.h
        pars_command.c
        pars_dollar.c
        pars_env.c
        pars_escaping.c
        pars_lib_utils.c
        pars_pipes.c
        pars_redirect.c
        pars_structs_utils.c
        pars_tockens.c
        parse_quotes.c
        parser.c
        redirect.c
        signal.c
        sys_mistakes_utils.c)
