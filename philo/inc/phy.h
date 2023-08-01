/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:38:02 by huolivei          #+#    #+#             */
/*   Updated: 2023/03/28 10:44:23 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHY_H
# define PHY_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_input
{
	int	nr_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nr_times_to_eat;
}		t_input;

typedef struct s_forks
{
	int	left;
	int	right;
}		t_forks;

typedef struct s_philos
{
	int			w_sit;
	int			nr_eaten;
	long long	time_die;
	t_forks		fork;
	pthread_t	th;
}		t_philos;

typedef struct s_data
{
	int				threads;
	int				deaths;
	long long		start_time;
	t_input			inp;
	t_philos		*phi;
	pthread_t		checks_death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
}		t_data;

int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
int			ft_isnum(int c);
void		philo_frees(t_data *args);
long long	get_time(void);
int			forks(t_data *args);
void		fill_philos(t_data *args, int i, int j);
int			philos(t_data *args);
int			init(char **av, t_data *args);
int			verification(int ac, char **av, t_data *args);
void		*print(t_data *args, int i, char *str);
int			eat(t_data *args, int i);
int			eat_sleep_think(t_data *args, int i);
void		*routine(void *stru);
void		*start_eat(t_data *args);
void		phi_sleep(t_data *args, int i);
void		*checker(void *strut);
int			phi_dead(t_data *args, int i);
int			thread_joiner(t_data *args);
void		mutex_destroyer(t_data *args);
void		*one_philo(t_data *args);
void		*fork_release(t_data *args, int i);

#endif
