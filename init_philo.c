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

t_philo *ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_philo *ft_lstnew(t_data *data, int id)
{
    t_philo	*newlist;

    newlist = (t_philo *)malloc(sizeof(t_philo));
    if (!newlist)
        return (NULL);
    newlist->id = id;
    newlist->data = data;
	newlist->time_born = get_time();
    newlist->last_meal = newlist->time_born;
    newlist->is_eating = false;
    newlist->next = NULL;
    newlist->thread = 0;
    newlist->nb_eat = 0;
    newlist->left_fork = NULL;
    return (newlist);
}

int init_mutex(t_philo **philo)
{
	t_philo	*current;

	current = *philo;
    while (current)
    {
        if (pthread_mutex_init(&current->right_fork, NULL) == -1)
            return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
		if (pthread_mutex_init(&current->read_last_meal, NULL) == -1)
            return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
		if (pthread_mutex_init(&current->read_nb_meal, NULL) == -1)
            return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
		if (pthread_mutex_init(&current->read_is_eating, NULL) == -1)
            return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
		if (current->next)
			current->next->left_fork = &current->right_fork;
		else
    		philo[0]->left_fork = &current->right_fork;
		current = current->next;
    }
    if (pthread_mutex_init(&philo[0]->data->read_stop_philo, NULL) == -1)
		return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
	if (pthread_mutex_init(&philo[0]->data->print_msg, NULL) == -1)
            return (write(STDERR, ERR_MUTEX, LEN_MUTEX), false);
	return (true);
}

t_philo **init_philo(t_data *data)
{
    t_philo **philo;
    t_philo *tmp;
    int i;

    philo = malloc(sizeof(t_philo *));
    if (!philo)
        return (NULL);
    *philo = NULL;
    i = 0;
    while (++i <= data->nb_philo)
    {
        tmp = ft_lstnew(data, i);
        if (!tmp)
            return (free_philo(philo), NULL);
        ft_lstadd_back(philo, tmp);
    }
	if (!init_mutex(philo))
		return(free_philo(philo), NULL);
	data->philo = (void *)philo;
    return (philo);
}
