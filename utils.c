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

long int    get_time(void)
{
    struct timeval  time;

    if (gettimeofday(&time, NULL) == -1)
        return (write(STDERR, ERR_TIME, LEN_TIME), -1);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	timer(int time_to_act)
{
	int	timer;

	timer = 0;
	while (timer < time_to_act * 1000)
	{
		usleep(150);
		timer += 150;
	}
}