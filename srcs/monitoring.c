/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:31:06 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philo *philo, t_data *data)
{
	int	return_value;

	return_value = false;
	pthread_mutex_lock(&philo->read_is_eating);
	if (philo->is_eating)
	{
		pthread_mutex_unlock(&philo->read_is_eating);
		return (return_value);
	}
	pthread_mutex_unlock(&philo->read_is_eating);
	pthread_mutex_lock(&philo->read_last_meal);
	if (get_time() - philo->last_meal > data->time_to_die)
	{
		print_message(philo, IS_DEAD);
		pthread_mutex_lock(&data->print_msg);
		data->can_print = false;
		pthread_mutex_unlock(&data->print_msg);
		return_value = true;
	}
	pthread_mutex_unlock(&philo->read_last_meal);
	return (return_value);
}

int	finish_eating(t_philo *philo, t_data *data)
{
	int	return_value;

	return_value = false;
	pthread_mutex_lock(&philo->read_nb_meal);
	if (philo->nb_eat >= data->nb_must_eat)
		return_value = true;
	pthread_mutex_unlock(&philo->read_nb_meal);
	return (return_value);
}

void	set_stop_philo(t_data *data)
{
	pthread_mutex_lock(&data->read_stop_philo);
	data->stop_philo = true;
	pthread_mutex_unlock(&data->read_stop_philo);
}

void	check_philo(t_philo *philo, t_data *data)
{
	int	i;
	int	everyone_full;

	if (check_death(philo, data))
		set_stop_philo(data);
	else if (data->nb_must_eat != -1 && finish_eating(philo, data))
		data->philo_full[philo->id - 1] = true;
	i = 0;
	everyone_full = true;
	while (i < data->nb_philo && data->nb_must_eat != -1)
	{
		if (!data->philo_full[i])
			everyone_full = false;
		i++;
	}
	if (everyone_full && data->nb_must_eat != -1)
		set_stop_philo(data);
}

void	*routine_monitor(void *arg)
{
	t_data	*data;
	t_philo	*lst;
	t_philo	**philo;

	data = (t_data *)arg;
	while (1)
	{
		philo = (t_philo **)data->philo;
		lst = *philo;
		while (lst)
		{
			check_philo(lst, data);
			pthread_mutex_lock(&data->read_stop_philo);
			if (data->stop_philo)
			{
				pthread_mutex_unlock(&data->read_stop_philo);
				return (NULL);
			}
			pthread_mutex_unlock(&data->read_stop_philo);
			lst = lst->next;
		}
	}
	return (NULL);
}
