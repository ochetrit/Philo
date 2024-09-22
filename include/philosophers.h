/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:57 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

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
# define TAKE_FORK "%ld %d has taken a fork\n"
# define IS_EATING "%ld %d is eating\n"
# define IS_SLEEPING "%ld %d is sleeping\n"
# define IS_THINKING "%ld %d is thinking\n"
# define IS_DEAD "%ld %d died\n"

typedef struct s_data
{
	int				nb_philo;
	int				nb_must_eat;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	pthread_t		monitor;
	pthread_mutex_t	print_msg;
	pthread_mutex_t	read_stop_philo;
	int				stop_philo;
	int				can_print;
	int				*philo_full;
	void			*philo;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				is_eating;
	suseconds_t		time_born;
	suseconds_t		last_meal;
	struct s_philo	*next;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	read_is_eating;
	pthread_mutex_t	read_last_meal;
	pthread_mutex_t	read_nb_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

t_philo				**parse_args(int ac, char **av);
t_philo				**init_philo(t_data *data);
void				free_philo(t_philo **philo);
int					make_thread(t_philo **philo);
void				*routine_monitor(void *arg);
int					init_data(t_data *data, int ac, char **av);
int					is_number(char *str);
void				*routine_monitor(void *arg);
void				print_message(t_philo *philo, char *msg);

/// UTILS ///
long int			get_time(void);
void				timer(int time_to_act);
void				print_message(t_philo *philo, char *msg);
void				release_fork(t_philo *philo);

#endif