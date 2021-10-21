/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:03:08 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 19:33:44 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define MSG_USAGE "usage: ./philo_bonus number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"

static char	parse(t_common *common, char **av)
{
	common->philos = ft_atoi(av[1]);
	common->die = ft_atoi(av[2]);
	common->eat = ft_atoi(av[3]);
	common->sleep = ft_atoi(av[4]);
	if (av[5])
		common->meals = ft_atoi(av[5]);
	else
		common->meals = INFINITE_MEALS;
	return (common->philos <= 0 || common->die <= 0 \
		|| common->eat <= 0 || common->sleep <= 0 \
		|| (av[5] && common->meals <= 0));
}

static char	init(t_common *common, t_child **children)
{
	*children = malloc(sizeof(t_child) * common->philos);
	if (!*children)
		return (ft_error("children[] allocation failed"));
	sem_unlink("ph_forks");
	sem_unlink("ph_write");
	sem_unlink("ph_total");
	common->forks = sem_open("ph_forks", O_CREAT, S_IRWXU, common->philos / 2);
	common->write = sem_open("ph_write", O_CREAT, S_IRWXU, 1);
	common->total = sem_open("ph_total", O_CREAT, S_IRWXU, 0);
	if (common->forks == SEM_FAILED || common->write == SEM_FAILED || \
		common->total == SEM_FAILED)
		return (ft_error("sem_open failed"));
	return (0);
}

static char	check_meals(t_common *common)
{
	int	count;

	common->monitor = fork();
	if (common->monitor < 0)
		return (ft_error("fork failed"));
	else if (common->monitor != 0)
		return (0);
	count = 0;
	while (count != common->philos)
	{
		sem_wait(common->total);
		count++;
	}
	sem_wait(common->write);
	printf("All philosophers have finished their meals.\n");
	exit(EXIT_SUCCESS);
	return (0);
}

static char	start(t_common *common, t_child *children)
{
	int	i;

	i = 0;
	memset(children, 0, sizeof(t_child) * common->philos);
	if (common->meals != INFINITE_MEALS && check_meals(common))
		return (EXIT_FAILURE);
	common->epoch = ft_get_time();
	while (i < common->philos)
	{
		children[i].data.who = i + 1;
		children[i].data.meals = 0;
		children[i].data.common = common;
		children[i].data.last_meal = common->epoch;
		children[i].pid = fork();
		if (children[i].pid < 0)
			return (ft_error("fork failed"));
		else if (children[i].pid == 0)
			ft_child(&children[i].data);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_common	common;
	t_child		*children;

	if (ac != 5 && ac != 6)
		return (ft_error("bad arguments\n"MSG_USAGE));
	if (parse(&common, av))
		return (1);
	children = NULL;
	if (init(&common, &children) || start(&common, children))
		return (ft_clean(&common, children));
	waitpid(-1, NULL, 0);
	ft_clean(&common, children);
}
