/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:50:47 by mlebard           #+#    #+#             */
/*   Updated: 2021/10/19 22:58:15 by mlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** usage: compares strings s1 and s2
** return: difference of first differing character.
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	int	i;
	int	intlen;

	i = 1;
	while (i < argc)
	{
		if (ft_strcheck_each(argv[i], &ft_isdigit) == 0)
			return (0);
		intlen = ft_strlen(argv[i]);
		if (intlen < 1 || intlen > 10)
			return (0);
		if (intlen == 1 && *argv[i] == '0')
			return (0);
		if (intlen == 10 && ft_strcmp(argv[i], "2147483647") > 0)
			return (0);
		i++;
	}
	table->philonum = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->mealcount = ft_atoi(argv[5]);
	return (1);
}
