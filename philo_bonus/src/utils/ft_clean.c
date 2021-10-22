/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:26 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/22 15:15:57 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	ft_clean(t_common *common, t_child *children)
{
	int	i;

	i = 0;
	while (children && i < common->philos)
		kill(children[i++].pid, SIGKILL);
	sem_close(common->forks);
	sem_close(common->write);
	if (common->meals != INFINITE_MEALS)
	{
		kill(common->monitor, SIGKILL);
		sem_close(common->total);
	}
	sem_unlink("ph_forks");
	sem_unlink("ph_write");
	sem_unlink("ph_total");
	free(children);
	return (EXIT_FAILURE);
}
