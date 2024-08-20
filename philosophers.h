/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/07/18 11:59:22 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

# define ERR_MALLOC "Error: malloc failed\n"
# define LEN_M 21
# define ERR_ARGS "Error: I need 4 or 5 args\n"
# define LEN_ARGS 26
# define STDERR STDERR_FILENO
# define ERR_NB "Error: I need a number\n"
# define LEN_NB 23
# define ERR_INT "Error: I need an int\n"
# define LEN_INT 21
# define LEN_INT_MAX 10
# define ERR_SIGN "Error: I need a positive integer\n"
# define LEN_SIGN 33
# define ERR_NB_PHILO "Error: I need at least 2 philosophers\n"
# define LEN_NB_PHILO 38
# define ERR_TIME "Error: could not access to the time of the day\n"
# define LEN_TIME 47
# define ERR_MUTEX "Error: failed to initialise a mutex\n"
# define LEN_MUTEX 36
# define ERR_THRD "Error: failed to create a thread\n"
# define LEN_THRD 33
# define ERR_THRD2 "Error: failed to join a thread\n"
# define LEN_THRD2 31
# define TAKE_FORK "%d %d has taken a fork\n"
# define IS_EATING "%d %d is eating\n"
# define IS_SLEEPING "%d %d is sleeping\n"
# define IS_THINKING "%d %d is thinking\n"
# define IS_DEAD "%d %d died\n"
# define EATING 0
# define THINKING 1
# define SLEEPING 2

typedef struct s_data
{
	int				nb_philo;
	int				nb_must_eat;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	pthread_mutex_t	death_mutex;
	int				is_dead;
}	t_data;

typedef struct s_philo
{
	int id;
	int nb_eat;
	int is_doing;
	suseconds_t last_meal;
	int is_dead;
	struct s_philo *next;
	t_data *data;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t right_fork;
}	t_philo;

t_philo	**parse_args(int ac, char **av);
t_philo	**init_philo(t_data *data);
void	free_philo(t_philo **philo);
int		make_thread(t_philo **philo);

/// UTILS ///
long int    get_time(void);

#endif