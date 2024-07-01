/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:55:51 by trgaspar          #+#    #+#             */
/*   Updated: 2023/11/07 23:21:40 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_count_int(long n)
{
	long	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;
	long	tmp;
	int		ten;

	tmp = n;
	sign = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		sign = 1;
	}
	ten = ft_count_int(n) + sign;
	str = malloc(sizeof(char) * ten + 1);
	if (!str)
		return (NULL);
	str[ten] = '\0';
	while (ten > 0)
	{
		str[--ten] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
