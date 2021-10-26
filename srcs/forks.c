/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:00:48 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/19 23:48:39 by mlebard          ###   ########.fr       */
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
			continue ;
		if (grab_fork(philo->left_fork) == 0)
		{
			drop_forks(philo);
			continue ;
		}
		else
			break ;
	}
	return (0);
}
