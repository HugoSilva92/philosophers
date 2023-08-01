/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:15:21 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 13:00:06 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy_bonus.h"

void	ender(t_data *args)
{
	int	i;

	i = 0;
	pthread_detach(args->checks_death);
	pthread_detach(args->end);
	while (i < args->inp.nr_philos)
	{
		sem_post(args->finish);
		usleep (1000);
		i++;
	}
	exit (0);
}

void	*wait_dead(void *stuc)
{
	t_data *args;

	args = (t_data *)stuc;
	sem_wait(args->finish);
	//pthread_detach(args->checks_death);
	//pthread_detach(args->end);
	exit (0);
}

/*void	*phi_dead(void *stuc)
{
	t_data	*args;
	int		i;

	i = 0;
	args = (t_data *)stuc;
	while (i < args->inp.nr_philos)
	{
		//printf("%lld\n", args->phi[i].time_die);
		if (get_time() > args->phi[i].time_die && !args->phi[i].is_eating)
		{
			print (args, i, "died");
			//printf("Morri %d\n", i);
			args->deaths++;
			ender(args);
			//sem_wait(args->finish);
			//exit (0);
			//return (NULL);
		}
		i++;
		usleep(1000);
		if (i == args->inp.nr_philos)
			i = 0;
	}
	return (NULL);
}*/

void	*phi_dead(void *stuc)
{
	t_data	*args;

	args = (t_data *)stuc;
	while (1)
	{
		/*if (args->nr_time_all_eat == args->time_eat)
			ender(args);*/
		sem_wait(args->dead);
		if (get_time() > args->phi[args->threads].time_die)
		{
			print (args, args->threads, "died");
			//printf("%lld\n", args->time_to_die);
			ender(args);
			args->deaths++;
		}
		sem_post(args->dead);
		usleep(1000);
	}
	return (NULL);
}

void	phi_sleep(t_data *args, int i)
{
	print(args, i, SLEEP);
	usleep(args->inp.time_sleep * 1000);
}

void	*fork_release(t_data *args, int i)
{
	sem_post(args->forks);
	sem_post(args->forks);
	args->phi[i].nr_eaten++;
	args->time_eat++;
	return (NULL);
}

void	*print(t_data *args, int i, char *str)
{
	long long	curr;

	curr = get_time() - args->start_time;
	if (args->deaths != 0 || args->inp.nr_times_to_eat == args->phi[i].nr_eaten)
		return (NULL);
	sem_wait(args->output);
	printf("%lld %d %s\n", curr, args->phi[i].w_sit, str);
	sem_post(args->output);
	return (NULL);
}

int	eat(t_data *args, int i)
{
	sem_wait(args->forks);
	print(args, i, FORK);
	sem_wait(args->forks);
	print(args, i, FORK);
	print(args, i, EAT);
	args->is_eating = 1;
	//args->time_to_die = get_time() + args->inp.time_die;
	//printf("Antes : Tempo para morrer do %d e de : %lld\n", args->phi[i].w_sit, args->phi[i].time_die);
	args->phi[i].time_die += args->inp.time_die;
	//printf("Tempo para morrer do %d e de : %lld\n", args->phi[i].w_sit, args->phi[i].time_die);
	usleep(args->inp.time_eat * 1000);
	args->is_eating = 0;
	fork_release(args, i);
	return (1);
}

int	eat_sleep_think(t_data *args, int i)
{
	pthread_create(&args->checks_death, NULL, &phi_dead, (void *)args);
	pthread_create(&args->end, NULL, &wait_dead, (void *)args);
	while (args->inp.nr_times_to_eat >= args->phi[i].nr_eaten || args->inp.nr_times_to_eat == -1 || args->deaths == 0)
	{
		/*if (args->deaths != 0)
			return (0);*/
		//printf("%d\n", args->phi[i].w_sit);
		eat(args, i);
		if (args->inp.nr_times_to_eat != args->phi[i].nr_eaten)
		{
			phi_sleep(args, i);
			print(args, i, THINK);
		}
	}
	return (1);
}

void	*start_sim(t_data *args)
{
	int	i;

	i = 0;
	args->start_time = get_time();
	while (i < args->inp.nr_philos)
	{
		args->pid[i] = fork();
		args->threads = i;
		if (args->pid[i] == 0)
		{
			eat_sleep_think(args, i);
			break ;
		}
		i++;
		usleep (60);
	}
	return (NULL);
}
