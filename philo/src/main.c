/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:40:09 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/13 19:37:44 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	error_usage(void)
{
	printf("usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
	return (1);
}

static void	init_from_argv(t_common *common, char **av)
{
	common->epoch = ft_get_time(); /* can be moved to main after allocation if needed */
	common->philos = ft_atoi(av[1]);
	common->die = ft_atoi(av[2]);
	common->eat = ft_atoi(av[3]);
	common->sleep = ft_atoi(av[4]);
	common->meals = -1;
	if (av[5])
	{
		common->meals = ft_atoi(av[5]);
		if (common->meals == 0)
			exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	t_common	common;
	t_thread	*threads;
	int			i;

	if (ac != 5 && ac != 6)
		return (error_usage());
	init_from_argv(&common, av);
	i = 0;
	threads = malloc(sizeof(t_thread) * common.philos);
	while (i < common.philos)
	{
		threads[i].data.who = i + 1;
		threads[i].data.common = &common;
		pthread_mutex_init(&threads[i].fork, NULL);
		pthread_create(&threads[i].tid, NULL, ft_thread, &threads[i].data);
		pthread_detach(threads[i].tid);
		i++;
	}
}
