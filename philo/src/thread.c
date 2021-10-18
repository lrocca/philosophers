/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:46:56 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/18 20:26:35 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_life(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (!philo->finish)
	{
		if (ft_get_time() - philo->last_meal > philo->common->die \
			&& !philo->finish)
		{
			ft_log(philo, MSG_DIE);
			pthread_mutex_unlock(&philo->common->exit);
			return (NULL);
		}
	}
	return (NULL);
}

static void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork);
	ft_log(philo, MSG_FORK);
	pthread_mutex_lock(philo->lfork);
}

static void	eat(t_philo *philo)
{
	ft_log(philo, MSG_EAT);
	ft_usleep(philo->common->eat);
	philo->last_meal = ft_get_time();
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
		ft_error("pthread_create failed");
		pthread_mutex_unlock(&philo->common->exit);
		return (1);
	}
	if (pthread_detach(tid))
	{
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
	if (philo->who % 2)
		ft_usleep((float)philo->common->eat * 0.1 + 1);
	while (philo->common->meals == -1 || philo->common->meals > philo->meals)
	{
		pick_forks(philo);
		eat(philo);
		if (philo->common->meals == philo->meals)
		{
			philo->finish = 1;
			pthread_mutex_lock(&philo->common->total);
			philo->common->vtotal++;
			pthread_mutex_unlock(&philo->common->total);
		}
		sleep_think(philo);
	}
	return (NULL);
}
