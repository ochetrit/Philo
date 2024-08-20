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

int is_int(char *str, int len)
{
    int i;

    if (str[0] == '+')
    {
        str++;
        len--;
    }
    if (len < LEN_INT_MAX)
        return (true);
    if (len == LEN_INT_MAX)
    {
        i = 0;
        while (str[i] - "2147483647"[i] <= 0 && str[i])
			i++;
    }
    if (str[i] || len > LEN_INT_MAX)
        return (write(STDERR, ERR_INT, LEN_INT), false);
    return (true);
}

int	ft_atoi(const char *nptr)
{
	int		nbr;
	char	neg;

	nbr = 0;
	neg = 1;
	while (*nptr == ' ' || (*nptr < 14 && *nptr > 7))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr <= '9' && *nptr >= '0')
	{
		nbr = 10 * nbr + *nptr - '0';
		nptr++;
	}
	return (neg * nbr);
}

int is_number(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (write(STDERR, ERR_NB, LEN_NB), -1);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (write(STDERR, ERR_NB, LEN_NB), -1);
        i++;
    }
    if (str[0] == '-')
        return (write(STDERR, ERR_SIGN, LEN_SIGN), -1);
    if (!is_int(str, i))
        return (-1);
    return (ft_atoi(str));
}

int init_data(t_data *data, int ac, char **av)
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
    data->is_dead = false;
    if (ac == 6)
    {
        data->nb_must_eat = is_number(av[5]);
        if (data->nb_must_eat == -1)
            return (false);
    }
    else
        data->nb_must_eat = -1;
    return (true);
}

t_philo **parse_args(int ac, char **av)
{
    t_data *data;
    t_philo **philo;

    (void)av;
    if (ac < 5 || ac > 6)
        return (write(STDERR, ERR_ARGS, LEN_ARGS), NULL);
    data = malloc(sizeof(t_data));
    if (!data)
        return (write(STDERR, ERR_MALLOC, LEN_M), free(data), NULL);
    if (!init_data(data, ac, av))
        return (free(data), NULL);
    if (data->nb_philo < 2)
        return (write(STDERR, ERR_NB_PHILO, LEN_NB_PHILO), free(data), NULL);
    philo = init_philo(data);
    return (philo);
}
