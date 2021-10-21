/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:34 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 17:09:52 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	ft_error(const char *msg)
{
	write(2, "error: ", 8);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}
