/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:46 by ochetrit          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_philo_full(t_data *data)
{
	int	i;

	data->philo_full = (int *)malloc(sizeof(int) * data->nb_philo);
	if (!data->philo_full)
		return (write(STDERR, ERR_MALLOC, LEN_M), false);
	i = 0;
	data->monitor = 0;
	while (i < data->nb_philo)
	{
		data->philo_full[i] = false;
		i++;
	}
	return (true);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = is_number(av[1]);
	if (data->nb_philo == -1)
		return (false);
	data->time_to_die = is_number(av[2]);
	if (data->time_to_die == -1)
		return (false);
	data->time_to_eat = is_number(av[3]);
	if (data->time_to_eat == -1)
		return (false);
	data->time_to_sleep = is_number(av[4]);
	if (data->time_to_sleep == -1)
		return (false);
	data->stop_philo = false;
	data->philo_full = NULL;
	if (ac == 6)
	{
		data->nb_must_eat = is_number(av[5]);
		if (data->nb_must_eat == -1)
			return (false);
		if (!init_philo_full(data))
			return (false);
	}
	else
		data->nb_must_eat = -1;
	return (true);
}
