/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:03:44 by gdinet            #+#    #+#             */
/*   Updated: 2020/11/05 15:53:54 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;

	if (start > ft_strlen(s))
		return ("\0");
	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
