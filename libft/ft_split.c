/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:06:30 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/10 14:47:38 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lenword(const char *s, char c)
{
	size_t			len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static size_t	ft_nbword(const char *s, char c)
{
	size_t			nb;
	unsigned int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			nb++;
		i++;
	}
	return (nb);
}

char			**ft_split(const char *s, char c)
{
	char			**tab;
	unsigned int	i;
	int				nb;

	if (!(tab = malloc(sizeof(char *) * (ft_nbword(s, c) + 1))))
		return (NULL);
	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			if (!(tab[nb] = ft_substr(s + i, 0, ft_lenword(s + i, c))))
			{
				while (nb >= 0)
					free(tab[nb--]);
				free(tab);
				return (NULL);
			}
			nb++;
		}
		i++;
	}
	tab[nb] = NULL;
	return (tab);
}
