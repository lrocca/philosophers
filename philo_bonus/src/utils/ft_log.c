/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:46 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 17:29:12 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_log(t_philo *philo, char *message)
{
	sem_wait(philo->common->write);
	printf("%.10ld %d %s\n", \
		ft_get_time() - philo->common->epoch, philo->who, message);
	sem_post(philo->common->write);
}
