/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:40:32 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/13 19:18:21 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define MSG_DIE	"died"
# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"

typedef struct s_common
{
	long	epoch;
	int		philos;
	int		die;
	int		eat;
	int		sleep;
	int		meals;
}	t_common;

typedef struct s_philo
{
	t_common	*common;
	long		last_meal;
	int			who;
	int			meals;
}	t_philo;

typedef struct s_thread
{
	t_philo			data;
	pthread_t		tid;
	pthread_mutex_t	fork;
}	t_thread;

void	*ft_thread(void *philo);

/* utils */
int		ft_atoi(const char *str);
char	ft_error(const char *msg);
long	ft_get_time(void);
void	ft_log(t_philo *philo, char *message);
void	ft_usleep(unsigned int interval);

#endif
