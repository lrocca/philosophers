/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:40:09 by lrocca            #+#    #+#             */
/*   Updated: 2021/10/01 19:45:13 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("seconds: %ld\nmicro seconds: %d\n",
		current_time.tv_sec, current_time.tv_usec);
}
