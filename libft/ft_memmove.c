/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:27:00 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/14 12:59:07 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int i;

	if (src > dst || src + len < dst)
		return (ft_memcpy(dst, src, len));
	i = (int)len - 1;
	while (i >= 0)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i--;
	}
	return (dst);
}
