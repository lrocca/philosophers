/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:55:50 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/20 18:06:23 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	ft_clean(t_common *common, t_thread *threads)
{
	int	i;

	i = 0;
	while (threads && i < common->philos)
		pthread_mutex_destroy(&threads[i++].fork);
	pthread_mutex_destroy(&common->exit);
	pthread_mutex_destroy(&common->write);
	pthread_mutex_destroy(&common->total_m);
	free(threads);
	return (EXIT_FAILURE);
}
