/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:18:35 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/18 18:55:20 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->common->write);
	printf("%.10ld %d %s\n", \
		ft_get_time() - philo->common->epoch, philo->who, message);
	pthread_mutex_unlock(&philo->common->write);
}
