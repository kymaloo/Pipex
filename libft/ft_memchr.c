/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:56:03 by trgaspar          #+#    #+#             */
/*   Updated: 2023/11/07 23:23:44 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_cast;
	unsigned char	c_cast;
	size_t			i;

	i = 0;
	s_cast = (unsigned char *)s;
	c_cast = (unsigned char)c;
	while (i < n)
	{
		if (s_cast[i] == c_cast)
			return (&s_cast[i]);
		i++;
	}
	return (0);
}
