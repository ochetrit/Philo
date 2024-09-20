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

#include "philosophers.h"

void    free_philo(t_philo **philo)
{
    t_philo *current;
    t_philo *tmp;

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
        if (tmp->left_fork)
            pthread_mutex_destroy(tmp->left_fork);
        free(tmp);
    }
    free(philo);
}