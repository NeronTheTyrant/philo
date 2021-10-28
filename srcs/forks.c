/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:00:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/28 18:31:30 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mtx);
	if (philo->left_fork->status == LOCKED)
	{
		philo->left_fork->status = UNLOCKED;
	}
	pthread_mutex_unlock(&philo->left_fork->mtx);
	pthread_mutex_lock(&philo->right_fork->mtx);
	if (philo->right_fork->status == LOCKED)
	{
		philo->right_fork->status = UNLOCKED;
	}
	pthread_mutex_unlock(&philo->right_fork->mtx);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	if (fork->status == LOCKED)
		fork->status = UNLOCKED;
	pthread_mutex_unlock(&fork->mtx);
}

int	grab_fork(t_fork *fork)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&fork->mtx);
	if (fork->status == UNLOCKED)
	{
		fork->status = LOCKED;
		ret = 1;
	}
	pthread_mutex_unlock(&fork->mtx);
	return (ret);
}

int	get_forks(t_philo *philo, t_table *table)
{
	while (1)
	{
		if (check_term(philo, table) == 1)
			return (-1);
		if (grab_fork(philo->right_fork) == 0)
		{
			usleep(1000);
			continue ;
		}
/*		if (table->time_to_die - (gettime() - philo->last_meal) <= table->time_to_eat * 1.2)
		{
			philo_msg("has priority", philo, table);
			while (1)
			{
				if (check_term(philo, table) == 1)
					return (-1);
				if (grab_fork(philo->left_fork) == 1)
					break ;
			}
		}
		else */if (grab_fork(philo->left_fork) == 0)
		{
			drop_fork(philo->right_fork);
			usleep(1000);
			continue ;
		}
		break ;
	}
	return (0);
}
