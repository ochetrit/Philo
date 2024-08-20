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

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (philo)
        else if (philo->state == EATING)
            eating(philo);
        else if (philo->state == THINKING)
            thinking(philo);
        else if (philo->state == SLEEPING)
            sleeping(philo);
    }
    return (NULL);
}

int    pair_philo(t_philo **philo)
{
    t_philo *lst;

    lst = *philo;
    while (lst)
    {
        if (pthread_create(&lst->thread, NULL, &routine, lst) == -1)
            return (write(STDERR, ERR_THRD, LEN_THRD), false);
        lst = lst->next;
    }
    lst  = *philo;
    while (lst)
    {
        if (pthread_join(lst->thread, NULL) == -1)
            return (write(STDERR, ERR_THRD2, LEN_THRD2), false);
        lst = lst->next;
    }
}