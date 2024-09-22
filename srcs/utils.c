/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(STDERR, ERR_TIME, LEN_TIME), -1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	timer(int time_to_act)
{
	long int	start;

	start = get_time();
	while (get_time() - start < time_to_act)
		usleep(100);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_msg);
	if (philo->data->can_print == true)
		printf(msg, get_time() - philo->time_born, philo->id);
	pthread_mutex_unlock(&philo->data->print_msg);
}
