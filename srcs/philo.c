/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:19:03 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	keep_going(t_philo *philo)
{
	int	return_value;

	return_value = true;
	pthread_mutex_lock(&philo->data->read_stop_philo);
	if (philo->data->stop_philo)
	{
		return_value = false;
	}
	pthread_mutex_unlock(&philo->data->read_stop_philo);
	return (return_value);
}

int	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	print_message(philo, TAKE_FORK);
	if (!keep_going(philo))
		return (pthread_mutex_unlock(&philo->right_fork), false);
	pthread_mutex_lock(philo->left_fork);
	if (!keep_going(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return (false);
	}
	print_message(philo, TAKE_FORK);
	print_message(philo, IS_EATING);
	pthread_mutex_lock(&philo->read_is_eating);
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->read_is_eating);
	return (true);
}

int	philo_try_to_eat(t_philo *philo)
{
	if (!philo_take_fork(philo))
		return (false);
	timer(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->read_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->read_last_meal);
	pthread_mutex_lock(&philo->read_is_eating);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->read_is_eating);
	if (!keep_going(philo))
		return (release_fork(philo), false);
	pthread_mutex_lock(&philo->read_nb_meal);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->read_nb_meal);
	if (!keep_going(philo))
		return (release_fork(philo), false);
	release_fork(philo);
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
		if (!keep_going(philo))
			return (NULL);
		print_message(philo, IS_THINKING);
		if (!keep_going(philo))
			return (NULL);
		if (!philo_try_to_eat(philo))
			return (NULL);
		if (!keep_going(philo))
			return (NULL);
		print_message(philo, IS_SLEEPING);
		timer(philo->data->time_to_sleep);
		if (!keep_going(philo))
			return (NULL);
	}
	return (NULL);
}

int	make_thread(t_philo **philo)
{
	t_philo	*lst;

	lst = *philo;
	while (lst)
	{
		if (pthread_create(&lst->thread, NULL, &routine, (void *)lst) == -1)
			return (write(STDERR, ERR_THRD, LEN_THRD), false);
		lst = lst->next;
	}
	lst = *philo;
	if (pthread_create(&lst->data->monitor, NULL, &routine_monitor,
			(void *)lst->data) == -1)
		return (write(STDERR, ERR_THRD, LEN_THRD), false);
	while (lst)
	{
		if (pthread_join(lst->thread, NULL) == -1)
			return (write(STDERR, "Error 404\n", 10), false);
		lst = lst->next;
	}
	lst = *philo;
	if (pthread_join(lst->data->monitor, NULL) == -1)
		return (write(STDERR, "Error 404\n", 10), false);
	return (true);
}
