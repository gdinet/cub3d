/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:50:28 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/11 17:28:34 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_writenb(char *res, size_t *i, int n)
{
	if (n < -9)
		ft_writenb(res, i, n / 10);
	res[(*i)++] = '0' - (n % 10);
}

char			*ft_itoa(int n)
{
	char	*res;
	size_t	i;
	int		n_tmp;

	i = (n >= 0) ? 1 : 2;
	n_tmp = (n >= 0) ? -n : n;
	while (n_tmp < -9)
	{
		i++;
		n_tmp = n_tmp / 10;
	}
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	if (n < 0)
		res[i++] = '-';
	else
		n = -n;
	ft_writenb(res, &i, n);
	res[i] = '\0';
	return (res);
}
