/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochetrit <ochetrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:41:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/09/22 23:52:40 by ochetrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_philo	**philo;

	philo = parse_args(ac, av);
	if (!philo)
		return (free_philo(philo), 1);
	else if (philo[0]->data->nb_must_eat == 0)
		return (free_philo(philo), 2);
	else if (philo[0]->data->nb_philo > 200)
		return (free_philo(philo), 3);
	else if (!make_thread(philo))
		return (free_philo(philo), 4);
	free_philo(philo);
	return (0);
}
