/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philo(t_philo **philo)
{
	t_philo	*current;
	t_philo	*tmp;

	if (!philo)
		return ;
	current = *philo;
	pthread_mutex_destroy(&current->data->read_stop_philo);
	pthread_mutex_destroy(&current->data->print_msg);
	free(current->data->philo_full);
	free(current->data);
	while (current)
	{
		tmp = current;
		current = current->next;
		pthread_mutex_destroy(&tmp->right_fork);
		pthread_mutex_destroy(&tmp->read_last_meal);
		pthread_mutex_destroy(&tmp->read_nb_meal);
		pthread_mutex_destroy(&tmp->read_is_eating);
		free(tmp);
	}
	free(philo);
}
