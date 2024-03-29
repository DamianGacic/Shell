/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:43:44 by dgacic            #+#    #+#             */
/*   Updated: 2023/01/19 10:43:48 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *) malloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (*s && n > 0)
	{
		*p = *s;
		p++;
		s++;
		i++;
		n--;
	}
	*p = '\0';
	p = p - i;
	return (p);
}
