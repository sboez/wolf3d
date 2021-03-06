/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 19:18:17 by sboez             #+#    #+#             */
/*   Updated: 2016/11/07 20:27:04 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int i;

	i = 0;
	if (n <= 0)
		return (0);
	while (n - 1 > 0 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
		n--;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
