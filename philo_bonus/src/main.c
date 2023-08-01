/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:56:15 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 13:08:07 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy_bonus.h"

void	clean(t_data *args)
{
	int	i;

	i = 0;
	sem_unlink("finish");
	sem_close(args->finish);
	sem_unlink("output");
	sem_close(args->output);
	sem_unlink("forks");
	sem_close(args->forks);
	sem_unlink("dead");
	sem_close(args->dead);
	while (i < args->inp.nr_philos)
		kill(args->pid[i++], SIGKILL);
	free(args->pid);
	free(args->phi);
	free(args);
	exit (0);
}

int	check_parent(t_data *args)
{
	int	i;

	i = 0;
	while (i < args->inp.nr_philos)
	{
		if (args->pid[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*args;
	int		i;

	i = 0;
	args = malloc(sizeof(t_data));
	if (!(verification(ac, av, args)))
	{
		printf("Error, wrong arguments!\n");
		return (1);
	}
	if (!philos(args))
		philo_frees(args);
	start_sim(args);
	//if (check_parent(args))
	//{
	//while (i < args->inp.nr_philos)
	waitpid(-1, 0, 0);
	//}
	clean(args);
	return (0);
}

/*if (args->inp.nr_philos == 1)
{
	one_philo(args);
	philo_frees(args);
	return (0);
}*/
