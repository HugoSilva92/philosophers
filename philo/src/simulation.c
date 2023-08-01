/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:14:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/03/22 15:23:42 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

int	cheack_times_eats(t_data *args)
{
	int	i;

	i = 0;
	while (args->inp.nr_times_to_eat >= args->phi[i].nr_eaten)
	{
		if (i == args->inp.nr_philos)
			return (1);
		if (args->deaths)
			return (0);
		if (!phi_dead(args, i))
			return (0);
		if (args->inp.nr_times_to_eat == args->phi[i].nr_eaten)
			return (0);
		i++;
	}
	return (1);
}

void	*checker(void *strut)
{
	t_data	*args;
	int		i;

	args = (t_data *) strut;
	i = 0;
	if (args->inp.nr_times_to_eat > 0)
	{
		while (!args->deaths)
		{
			if (!cheack_times_eats(args))
				break ;
		}
	}
	else
	{
		while (!args->deaths)
		{
			if (i == args->inp.nr_philos)
				i = 0;
			if (!phi_dead(args, i))
				break ;
			i++;
		}
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
	if (args->inp.nr_times_to_eat > 0)
	{
		while (args->inp.nr_times_to_eat >= args->phi[i].nr_eaten)
			eat_sleep_think(args, i);
	}
	else
	{
		while (args->deaths == 0)
		{
			if (!eat_sleep_think(args, i))
				break ;
		}
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
	usleep(1000);
	if (!thread_joiner(args))
		return (NULL);
	mutex_destroyer(args);
	return (NULL);
}
