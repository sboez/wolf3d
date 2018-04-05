/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboez <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:09:44 by sboez             #+#    #+#             */
/*   Updated: 2017/09/28 21:09:53 by sboez            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (NULL);
	result = malloc(size * nmemb);
	while (i <= nmemb)
	{
		((char*)result)[i] = 0;
		i++;
	}
	return (result);
}
