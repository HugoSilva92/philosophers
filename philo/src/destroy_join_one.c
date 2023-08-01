/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_join_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:15:12 by huolivei          #+#    #+#             */
/*   Updated: 2023/03/27 17:17:27 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

void	*one_philo(t_data *args)
{
	if (pthread_mutex_init(&args->output, NULL) != 0)
		return (NULL);
	args->start_time = get_time();
	print(args, 0, FORK);
	usleep(args->inp.time_die * 1000);
	print(args, 0, "Died");
	mutex_destroyer(args);
	return (NULL);
}

void	mutex_destroyer(t_data *args)
{
	int	i;

	i = 0;
	while (i < args->inp.nr_philos)
		pthread_mutex_destroy(&args->forks[i++]);
	pthread_mutex_destroy(&args->output);
}

int	thread_joiner(t_data *args)
{
	int	i;

	i = 0;
	while (i < args->inp.nr_philos)
	{
		if (pthread_join(args->phi[i].th, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(args->checks_death, NULL) != 0)
		return (0);
	return (1);
}
