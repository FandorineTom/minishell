/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 22:15:26 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/14 21:56:08 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	size_t	index;
	int		words;

	index = 0;
	words = 0;
	while (s[index])
	{
		while (s[index] == c)
			index++;
		if (s[index] != c && s[index] != '\0')
			words++;
		while (s[index] && s[index] != c)
			index++;
	}
	return (words);
}

static int	ft_words_maxlen(char const *s, char c)
{
	int		maxlen;
	int		len;
	size_t	index;

	maxlen = 0;
	index = 0;
	while (s[index])
	{
		len = 0;
		while (s[index] == c)
			index++;
		while (s[index] && s[index] != c)
		{
			len++;
			index++;
		}
		if (len > maxlen)
			maxlen = len;
	}
	return (maxlen);
}

static void	ft_actually_split(char const *s, char c, char **result)
{
	size_t	index;
	size_t	i;
	size_t	j;

	index = 0;
	i = 0;
	while (s[index])
	{
		j = 0;
		while (s[index] == c)
			index++;
		while (s[index] && s[index] != c)
		{
			result[i][j] = s[index];
			index++;
			j++;
		}
		i++;
	}
}

static char	**free_mem(char **str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;
	int		words_len;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * words + 1)))
		return (NULL);
	result[words] = NULL;
	i = 0;
	words_len = ft_words_maxlen(s, c);
	while (i < words)
	{
		if (!(result[i] = ft_calloc((words_len + 1), sizeof(char))))
			return (free_mem(result));
		i++;
	}
	ft_actually_split(s, c, result);
	return (result);
}
