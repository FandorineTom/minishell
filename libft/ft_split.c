/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 02:47:46 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/21 02:48:24 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int i;
	int words;
	int marker;

	i = 0;
	words = 0;
	while (s[i])
	{
		marker = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			marker = 1;
			i++;
		}
		if (marker > 0)
			words++;
	}
	return (words);
}

static int	ft_word_len(char const *s, char c)
{
	int i;
	int len;
	int max_len;

	i = 0;
	max_len = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		if (max_len < len)
			max_len = len;
	}
	return (max_len);
}

static void	ft_strsplit(char const *s, char **str, char c)
{
	int i;
	int j;
	int k;
	int marker;

	i = 0;
	j = 0;
	while (s[i])
	{
		k = 0;
		marker = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			str[j][k++] = s[i++];
			marker++;
		}
		if (marker > 0)
			j++;
	}
}

static char	**memfree(char **str)
{
	while (*str)
		free(*str);
	free(str);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	int		words;
	int		len;
	int		i;
	char	**str;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(str = (char **)ft_calloc((words + 1), sizeof(char *))))
		return (NULL);
	len = ft_word_len(s, c);
	i = 0;
	while (i < words)
		if (!(str[i++] = (char *)ft_calloc((len + 1), sizeof(char))))
			return (memfree(str));
	ft_strsplit(s, str, c);
	return (str);
}
