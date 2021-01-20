/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:29:07 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/14 13:15:48 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(const char *set, const char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;

	start = 0;
	while (s1[start] && ft_isset(set, s1[start]))
		start++;
	end = (unsigned int)ft_strlen(s1) - 1;
	while (end > 0 && ft_isset(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
