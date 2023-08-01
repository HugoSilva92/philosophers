/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phy_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:13:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/05 10:54:52 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHY_BONUS_H
# define PHY_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

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

typedef struct s_philos
{
	int			w_sit;
	int			nr_eaten;
	long long	time_die;
	int			is_eating;
	pthread_t	th;
}		t_philos;

typedef struct s_data
{
	int				*pid;
	int				threads;
	int				deaths;
	long long		start_time;
	long long		time_to_die;
	int				is_eating;
	int				nr_time_all_eat;
	int				time_eat;
	t_input			inp;
	t_philos		*phi;
	pthread_t		checks_death;
	pthread_t		end;
	pthread_t		cleaner;
	sem_t	*dead;
	sem_t	*forks;
	sem_t	*output;
	sem_t	*finish;
}		t_data;

int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
int			ft_isnum(int c);
void		philo_frees(t_data *args);
long long	get_time(void);
void		fill_philos(t_data *args, int i);
int			philos(t_data *args);
int			init(char **av, t_data *args);
int			verification(int ac, char **av, t_data *args);
void		*print(t_data *args, int i, char *str);
int			eat(t_data *args, int i);
int			eat_sleep_think(t_data *args, int i);
void		phi_sleep(t_data *args, int i);
void		*checker(void *strut);
void		*phi_dead(void *stuc);
int			thread_joiner(t_data *args);
void		*one_philo(t_data *args);
void		*start_sim(t_data *args);

#endif
