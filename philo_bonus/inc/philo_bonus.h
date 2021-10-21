/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:16:44 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/21 19:27:47 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>

# define MSG_DIE	"died"
# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"

# define INFINITE_MEALS	-1

typedef struct s_common
{
	sem_t	*forks;
	sem_t	*write;
	sem_t	*total;
	long	epoch;
	int		philos;
	int		die;
	int		eat;
	int		sleep;
	int		meals;
	pid_t	monitor;
}	t_common;

typedef struct s_philo
{
	t_common	*common;
	long		last_meal;
	int			who;
	int			meals;
}	t_philo;

typedef struct s_child
{
	t_philo	data;
	pid_t	pid;
}	t_child;

void	ft_child(t_philo *philo);

/* utils */
int		ft_atoi(const char *str);
char	ft_clean(t_common *common, t_child *child);
char	ft_error(const char *msg);
long	ft_get_time(void);
void	ft_log(t_philo *philo, char *message);
void	ft_usleep(unsigned int interval);

#endif
