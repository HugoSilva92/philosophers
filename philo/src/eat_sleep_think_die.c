/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:12:04 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 11:03:34 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

int	phi_dead(t_data *args, int i)
{
	if (get_time() > args->phi[i].time_die)
	{
		print (args, i, "died");
		args->deaths++;
		return (0);
	}
	return (1);
}

void	phi_sleep(t_data *args, int i)
{
	print(args, i, SLEEP);
	usleep(args->inp.time_sleep * 1000);
}

int	eat(t_data *args, int i)
{
	if (pthread_mutex_lock(&args->forks[args->phi[i].fork.left]) != 0)
		return (0);
	print(args, i, FORK);
	if (pthread_mutex_lock(&args->forks[args->phi[i].fork.right]) != 0)
		return (0);
	print(args, i, FORK);
	print(args, i, EAT);
	args->phi[i].time_die = get_time() + args->inp.time_die;
	usleep(args->inp.time_eat * 1000);
	fork_release(args, i);
	return (1);
}

int	eat_sleep_think(t_data *args, int i)
{
	if (!eat(args, i))
		return (0);
	if (args->inp.nr_times_to_eat != args->phi[i].nr_eaten)
	{
		phi_sleep(args, i);
		print(args, i, THINK);
	}
	return (1);
}

void	*print(t_data *args, int i, char *str)
{
	long long	curr;

	curr = get_time() - args->start_time;
	if (args->deaths != 0 || args->inp.nr_times_to_eat == args->phi[i].nr_eaten)
		return (NULL);
	pthread_mutex_lock(&args->output);
	printf("%lld %d %s\n", curr, args->phi[i].w_sit, str);
	pthread_mutex_unlock(&args->output);
	return (NULL);
}
