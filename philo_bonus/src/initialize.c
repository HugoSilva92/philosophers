/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:58:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 11:10:11 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy_bonus.h"

void	init_sema(t_data *args)
{
	sem_unlink("output");
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("dead");
	args->finish = sem_open("finish", O_CREAT, 0644, 0);
	args->forks = sem_open("forks", O_CREAT, 0644, args->inp.nr_philos);
	args->output = sem_open("output", O_CREAT, 0644, 1);
	args->dead = sem_open("dead", O_CREAT, 0644, 1);
}

void	fill_philos(t_data *args, int i)
{
	args->phi[i].w_sit = i + 1;
	args->phi[i].nr_eaten = 0;
	args->phi[i].time_die = get_time() + args->inp.time_die;
	args->phi[i].is_eating = 0;
}

int	philos(t_data *args)
{
	int	i;

	i = 0;
	args->phi = malloc(sizeof(t_philos) * args->inp.nr_philos);
	if (!(args->phi))
		return (0);
	while (i < args->inp.nr_philos)
	{
		fill_philos(args, i);
		i++;
	}
	return (1);
}

int	init(char **av, t_data *args)
{
	args->start_time = 0;
	args->deaths = 0;
	args->is_eating = 0;
	args->threads = 0;
	args->time_eat = 0;
	args->inp.nr_philos = ft_atoi(av[1]);
	args->inp.time_die = ft_atoi(av[2]);
	args->inp.time_eat = ft_atoi(av[3]);
	args->inp.time_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		args->inp.nr_times_to_eat = ft_atoi (av[5]);
		args->nr_time_all_eat = args->inp.nr_philos * args->inp.nr_times_to_eat;
	}
	else
	{
		args->inp.nr_times_to_eat = -1;
		args->nr_time_all_eat = INT_MAX;
	}
	args->pid = malloc(sizeof(int *) * args->inp.nr_philos);
	init_sema(args);
	args->time_to_die = get_time() + args->inp.time_die;
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
