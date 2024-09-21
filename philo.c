/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:19:03 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/17 15:07:11 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_msg);
	printf(msg, get_time() - philo->time_born, philo->id);
	pthread_mutex_unlock(&philo->data->print_msg);
}

int	keep_going(t_philo *philo)
{
	int	return_value;

	return_value = true;
	pthread_mutex_lock(&philo->data->read_stop_philo);
	if (philo->data->stop_philo)
		return_value = true;
	pthread_mutex_unlock(&philo->data->read_stop_philo);
	return (return_value);
}

int	is_dead(t_philo *philo)
{
	int	is_dead;

	is_dead = false;
	pthread_mutex_lock(&philo->read_last_meal);
	//fprintf(stderr, "%d->last_meal : %ld\n %ld\n", philo->id, philo->last_meal, get_time());
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		print_message(philo, IS_DEAD);
		is_dead = true;
	}
	pthread_mutex_unlock(&philo->read_last_meal);
	return (is_dead);
}

int	philo_try_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	if (/*!keep_going(philo) ||*/ is_dead(philo))
		return (false);
	print_message(philo, TAKE_FORK);
	if (/*!keep_going(philo) ||*/ is_dead(philo))
		return (false);
	pthread_mutex_lock(philo->left_fork);
	if (/*!keep_going(philo) ||*/ is_dead(philo))
		return (false);
	print_message(philo, TAKE_FORK);
	print_message(philo, IS_EATING);
	timer(philo->data->time_to_eat);
	//if (!keep_going(philo))
	// 	return (false);
	pthread_mutex_lock(&philo->read_last_meal);
	philo->last_meal = get_time();
pthread_mutex_unlock(&philo->read_last_meal);
	pthread_mutex_lock(&philo->read_nb_meal);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->read_nb_meal);
	if (/*!keep_going(philo) ||*/ is_dead(philo))
		return (false);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
			usleep(1000);
	while (1)
	{
		// if (!keep_going(philo))
		// 	return (NULL);
	 	print_message(philo, IS_THINKING);
		if (!philo_try_to_eat(philo))
			return (NULL);
		// if (!keep_going(philo))
		// 	return (NULL);
		print_message(philo, IS_SLEEPING);
		timer(philo->data->time_to_sleep);
		if (/*!keep_going(philo) ||*/ is_dead(philo))
		 	return (NULL);
	}
	return (NULL);
}

int		make_thread(t_philo **philo)
{
	t_philo *lst;

	lst = *philo;
	while (lst)
	{
		if (pthread_create(&lst->thread, NULL, &routine, (void *)lst) == -1)
			return (write(STDERR, ERR_THRD, LEN_THRD), false);
		lst = lst->next;
	}
	lst = *philo;
	// if (pthread_create(&lst->data->monitor, NULL, &routine_monitor, (void *)lst->data) == -1)
	// 	return (write(STDERR, ERR_THRD, LEN_THRD), false);
	while (lst)
	{
		if (pthread_join(lst->thread, NULL) == -1)
			return (write(STDERR, "Error 404\n", 10), false);
		lst = lst->next;
	}
	// lst = *philo;
	// if (pthread_join(lst->data->monitor, NULL) == -1)
	// 	return (write(STDERR, "Error 404\n", 10), false);
	return (true);
}
