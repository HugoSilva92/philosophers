/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:14:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 11:05:12 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

void	*checker(void *strut)
{
	t_data	*args;
	int		i;

	i = 0;
	args = (t_data *) strut;
	while (1)
	{
		if (!phi_dead(args, i))
			break ;
		i++;
		if (i == args->inp.nr_philos)
			i = 0;
	}
	return (NULL);
}

void	*fork_release(t_data *args, int i)
{
	if (pthread_mutex_unlock(&args->forks[args->phi[i].fork.left]) != 0)
		return (NULL);
	if (pthread_mutex_unlock(&args->forks[args->phi[i].fork.right]) != 0)
		return (NULL);
	args->phi[i].nr_eaten++;
	return (NULL);
}

void	*routine(void *stru)
{
	t_data	*args;
	int		i;

	args = (t_data *)stru;
	i = args->threads;
	while (1)
	{
		if (!eat_sleep_think(args, i)
			|| args->inp.nr_times_to_eat == args->phi[i].nr_eaten
			|| args->deaths)
			break ;
	}
	return (NULL);
}

void	*start_eat(t_data *args)
{
	int	i;

	i = 0;
	args->start_time = get_time();
	if (pthread_mutex_init(&args->output, NULL) != 0)
		return (NULL);
	while (i < args->inp.nr_philos)
	{
		args->threads = i;
		if (pthread_create(&args->phi[i].th, NULL, &routine, (void *)args) != 0)
			return (NULL);
		usleep(1000);
		i++;
	}
	if (pthread_create(&args->checks_death, NULL, &checker, (void *)args) != 0)
		return (NULL);
	if (!thread_joiner(args))
		return (NULL);
	mutex_destroyer(args);
	return (NULL);
}
