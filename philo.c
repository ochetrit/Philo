/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:19:03 by ochetrit          #+#    #+#             */
/*   Updated: 2024/08/20 18:28:23 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->is_dead == false)
	{
		printf(IS_THINKING, get_time(), philo->id);
		pthread_mutex_lock(&philo->right_fork);
		printf(TAKE_FORK, get_time(), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf(TAKE_FORK, get_time(), philo->id);
	}
}

int		make_thread(t_philo **philo)
{
	t_philo *lst;

	lst = *philo;
	if (pthread_create(&lst->thread, NULL, &routine, (void *)lst) == -1)
		return (write(STDERR, ERR_THRD, LEN_THRD), false);
	else if (pthread_join(lst->thread, NULL) == -1)
		return (write(STDERR, "Error 404\n", 10), false);
	return (true);
}