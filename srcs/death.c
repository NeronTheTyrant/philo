/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:07:24 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/27 13:59:24 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_die(t_philo *philo, t_table *table)
{
	unsigned long int	time;

	pthread_mutex_lock(&table->msg);
	pthread_mutex_lock(&table->sig_mtx);
	if (table->sig != SIG_TERM_DIE && table->sig != SIG_TERM_MEALS)
	{
		time = gettime() - table->start_time;
		printf("%lums: %d died\n", time, philo->id);
	}
	table->sig = SIG_TERM_DIE;
	pthread_mutex_unlock(&table->sig_mtx);
	pthread_mutex_unlock(&table->msg);
}

int	check_term(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->sig_mtx);
	if (table->sig == SIG_TERM_DIE || table->sig == SIG_TERM_MEALS)
	{
		pthread_mutex_unlock(&table->sig_mtx);
		return (1);
	}
	pthread_mutex_unlock(&table->sig_mtx);
	if (gettime() - philo->last_meal >= table->time_to_die)
	{
		philo_die(philo, table);
		return (1);
	}
	else
		return (0);
}
