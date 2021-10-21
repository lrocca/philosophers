/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:14 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 19:23:07 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
			sem_wait(philo->common->write);
			exit(EXIT_FAILURE);
			return (NULL);
		}
	}
	sem_post(philo->common->total);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->common->forks);
	ft_log(philo, MSG_FORK);
	ft_log(philo, MSG_EAT);
	philo->last_meal = ft_get_time();
	ft_usleep(philo->common->eat);
	sem_post(philo->common->forks);
	philo->meals++;
}

static void	sleep_think(t_philo *philo)
{
	ft_log(philo, MSG_SLEEP);
	ft_usleep(philo->common->sleep);
	ft_log(philo, MSG_THINK);
}

static void	life_daemon(t_philo *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, check_life, philo))
	{
		sem_wait(philo->common->write);
		ft_error("pthread_create failed");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(tid))
	{
		sem_wait(philo->common->write);
		ft_error("pthread_detach failed");
		exit(EXIT_FAILURE);
	}
}

void	ft_child(t_philo *philo)
{
	life_daemon(philo);
	while (1)
	{
		eat(philo);
		if (philo->common->meals == philo->meals)
			break ;
		sleep_think(philo);
	}
	sem_post(philo->common->total);
	while (1)
		;
}
