/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:39:23 by huolivei          #+#    #+#             */
/*   Updated: 2023/03/22 15:23:44 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/phy.h"

int	main(int ac, char **av)
{
	t_data	*args;

	args = malloc(sizeof(t_data));
	if (!(verification(ac, av, args)))
	{
		printf("Error, wrong arguments!\n");
		return (1);
	}
	if (!philos(args) || !forks(args))
	{
		philo_frees(args);
		return (1);
	}
	if (args->inp.nr_philos == 1)
	{
		one_philo(args);
		philo_frees(args);
		return (0);
	}
	start_eat(args);
	philo_frees(args);
	return (0);
}
