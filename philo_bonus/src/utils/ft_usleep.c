/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:53 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/20 18:04:35 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(unsigned int interval)
{
	long	time;

	time = ft_get_time() + interval;
	while (ft_get_time() < time)
		usleep(interval);
}
