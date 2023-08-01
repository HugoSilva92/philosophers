/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:44:22 by huolivei          #+#    #+#             */
/*   Updated: 2023/03/28 10:37:34 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

int	forks(t_data *args)
{
	int	i;

	i = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->inp.nr_philos);
	if (!args->forks)
		return (0);
	while (i < args->inp.nr_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	fill_philos(t_data *args, int i, int j)
{
	args->phi[i].w_sit = i + 1;
	args->phi[i].nr_eaten = 0;
	args->phi[i].time_die = get_time() + args->inp.time_die;
	args->phi[i].fork.left = i;
	args->phi[i].fork.right = j;
}

int	philos(t_data *args)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	args->phi = malloc(sizeof(t_philos) * args->inp.nr_philos);
	if (!(args->phi))
		return (0);
	while (j < args->inp.nr_philos)
	{
		fill_philos(args, i, j);
		i++;
		j++;
	}
	j = 0;
	fill_philos(args, i, j);
	return (1);
}

int	init(char **av, t_data *args)
{
	args->start_time = 0;
	args->deaths = 0;
	args->threads = 0;
	args->inp.nr_philos = ft_atoi(av[1]);
	args->inp.time_die = ft_atoi(av[2]);
	args->inp.time_eat = ft_atoi(av[3]);
	args->inp.time_sleep = ft_atoi(av[4]);
	if (av[5])
		args->inp.nr_times_to_eat = ft_atoi (av[5]);
	else
		args->inp.nr_times_to_eat = -1;
	return (1);
}

int	verification(int ac, char **av, t_data *args)
{
	int	i;

	i = 1;
	if (ac <= 4 || ac >= 7 || !args)
		return (0);
	if (av[1][0] <= 48 && av[1][1] == '\0')
		return (0);
	while (i < ac)
	{
		if (!(ft_isdigit(av[i])))
			return (0);
		if (av[1][0] == 48 || av[2][0] == 48)
			return (0);
		if (av[i][0] == '-')
			return (0);
		i++;
	}
	if (!init(av, args))
		return (0);
	return (1);
}
