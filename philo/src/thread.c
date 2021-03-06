/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:46:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 18:51:21 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_life(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (1)
	{
		if (philo->meals == philo->common->meals)
			break ;
		if (ft_get_time() - philo->last_meal > philo->common->die)
		{
			ft_log(philo, MSG_DIE);
			pthread_mutex_lock(&philo->common->write);
			pthread_mutex_unlock(&philo->common->exit);
			return (NULL);
		}
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	ft_log(philo, MSG_FORK);
	pthread_mutex_lock(philo->lfork);
	ft_log(philo, MSG_EAT);
	philo->last_meal = ft_get_time();
	ft_usleep(philo->common->eat);
	philo->meals++;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

static void	sleep_think(t_philo *philo)
{
	ft_log(philo, MSG_SLEEP);
	ft_usleep(philo->common->sleep);
	ft_log(philo, MSG_THINK);
}

static char	life_daemon(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, check_life, philo))
	{
		pthread_mutex_lock(&philo->common->write);
		ft_error("pthread_create failed");
		pthread_mutex_unlock(&philo->common->exit);
		return (1);
	}
	if (pthread_detach(tid))
	{
		pthread_mutex_lock(&philo->common->write);
		ft_error("pthread_detach failed");
		pthread_mutex_unlock(&philo->common->exit);
		return (1);
	}
	return (0);
}

void	*ft_thread(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (life_daemon(philo))
		return (NULL);
	if (philo->who % 2 == 0)
		ft_usleep((float)philo->common->eat * 0.1 + 1);
	while (1)
	{
		eat(philo);
		if (philo->common->meals == philo->meals)
			break ;
		sleep_think(philo);
	}
	pthread_mutex_lock(&philo->common->total_m);
	philo->common->total_v++;
	pthread_mutex_unlock(&philo->common->total_m);
	return (NULL);
}
