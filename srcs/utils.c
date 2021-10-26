/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:59:06 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/26 20:12:11 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_msg(char *str, t_philo *philo, t_table *table)
{
	unsigned long int	time;
	int					sig;

	pthread_mutex_lock(&table->msg);
	pthread_mutex_lock(&table->sig_mtx);
	sig = table->sig;
	if (sig != SIG_TERM_DIE && sig != SIG_TERM_MEALS)
	{
		time = gettime() - table->start_time;
		printf("%lums: %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&table->sig_mtx);
	pthread_mutex_unlock(&table->msg);
}

unsigned long int	gettime(void)
{
	struct timeval	tv;
	long			ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_sec * 1000;
	ret += tv.tv_usec / 1000;
	return (ret);
}

unsigned long int	gettimetosleep(unsigned long int last_meal,
		unsigned long int time_to_do, unsigned long int time_to_die)
{
	unsigned long int	time;

	time = gettime() - last_meal;
	if (time + time_to_do >= time_to_die)
		return (time_to_die - time);
	else
		return (time_to_do);
}
