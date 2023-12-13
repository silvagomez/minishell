/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:33:33 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:23:09 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_free(char **mtrx, size_t index)
{
	while (index)
	{
		index--;
		free(mtrx[index]);
	}
	return (NULL);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
		{
			words++;
			while (s[i] != 0 && s[i] != c)
				i++;
		}
	}
	return (words);
}

static char	*ft_create_substr(char **mtrx, const char *s, char c, size_t index)
{
	unsigned int	start;
	size_t			len;
	size_t			i;
	size_t			stops;

	i = 0;
	stops = 0;
	while (s[i] != 0 && stops <= index)
	{
		while (s[i] == c)
			i++;
		if (stops == index)
			start = i;
		while (s[i] != c && s[i] != 0)
			i++;
		if (stops == index)
		{
			len = i - start;
			mtrx[index] = ft_substr(s, start, len);
			if (!mtrx[index])
				return (ft_free(mtrx, index));
		}
		stops++;
	}
	return (mtrx[index]);
}

char	**ft_split(char const *s, char c)
	{
	char	**mtrx;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	mtrx = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!mtrx)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		mtrx[i] = ft_create_substr(mtrx, s, c, i);
		if (mtrx[i] == NULL)
			return (free (mtrx), NULL);
		i++;
	}
	mtrx[i] = NULL;
	return (mtrx);
}
