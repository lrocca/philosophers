/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:40:09 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/18 20:30:59 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	print_usage(void)
{
	return (printf("usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"));
}

static char	init(t_common *common, t_thread **threads, char **av)
{
	int	i;

	common->philos = ft_atoi(av[1]);
	common->die = ft_atoi(av[2]);
	common->eat = ft_atoi(av[3]);
	common->sleep = ft_atoi(av[4]);
	common->meals = -1;
	if (av[5])
		common->meals = ft_atoi(av[5]);
	*threads = malloc(sizeof(t_thread) * common->philos);
	if (!*threads)
		return (ft_error("threads[] allocation failed"));
	common->epoch = ft_get_time();
	i = 0;
	while (i < common->philos)
	{
		(*threads)[i].data.who = i + 1;
		(*threads)[i].data.finish = 0;
		(*threads)[i].data.common = common;
		(*threads)[i].data.last_meal = common->epoch;
		if (pthread_mutex_init(&(*threads)[i].fork, NULL))
			return (ft_error("pthread_mutex_init failed"));
		i++;
	}
	return (0);
}

static void	*check_meals(void *ptr)
{
	t_common *common;

	common = ptr;
	while (1)
		if (common->vtotal != common->meals)
			break ;
	pthread_mutex_lock(&common->write);
	printf("All philosophers have finished their meals.\n");
	pthread_mutex_unlock(&common->write);
	pthread_mutex_unlock(&common->exit);
	return (NULL);
}

static char	start(t_common *common, t_thread *threads)
{
	int			i;
	pthread_t	tid;

	i = 0;
	tid = 0;
	if (pthread_mutex_init(&common->exit, NULL) || \
		pthread_mutex_init(&common->write, NULL) || \
		pthread_mutex_init(&common->total, NULL))
		return (ft_error("pthread_mutex_init failed"));
	pthread_mutex_lock(&common->exit);
	if (common->meals != -1 && \
		(pthread_create(&tid, NULL, check_meals, &common) \
		|| pthread_detach(tid)))
		return (ft_error("check_meals failed to start"));
	while (i < common->philos)
	{
		threads[i].data.rfork = &(threads[i].fork);
		threads[i].data.lfork = &(threads[(i + 1) % common->philos].fork);
		if (pthread_create(&tid, NULL, ft_thread, &threads[i].data))
			return (ft_error("pthread_create failed"));
		if (pthread_detach(tid))
			return (ft_error("pthread_detach failed"));
		i++;
	}
	return (0);
}

static char	clean(t_common *common, t_thread *threads)
{
	int	i;

	i = 0;
	while (threads && i < common->philos)
		pthread_mutex_destroy(&threads[i++].fork);
	pthread_mutex_destroy(&common->exit);
	pthread_mutex_destroy(&common->write);
	pthread_mutex_destroy(&common->total);
	free(threads);
	return (-1);
}

int	main(int ac, char **av)
{
	t_common	common;
	t_thread	*threads;

	threads = NULL;
	if (ac != 5 && ac != 6)
		return (ft_error("bad arguments") && print_usage());
	if (init(&common, &threads, av) || start(&common, threads))
		return (clean(&common, threads));
	pthread_mutex_lock(&common.exit);
	pthread_mutex_lock(&common.write);
	clean(&common, threads);
}
