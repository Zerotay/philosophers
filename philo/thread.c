/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongguki <dongguki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:04:52 by dongguki          #+#    #+#             */
/*   Updated: 2021/11/22 11:09:09 by dongguki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*if_only_one(void *all)
{
	t_philo	*philo;

	philo = all;
	philo->game->start_time =  present_time();
	pthread_mutex_lock(&(philo->game->forks[0]));
	print(0, "has taken a fork", *philo->game);
	pass(philo->game->livetime);
	print(0, "died", *philo->game);
	pthread_mutex_unlock(&(philo->game->forks[0]));
	return (0);
}

void	*rotate(void *all)
{
	t_philo	*philo;

	philo = all;
	philo->tictoc = present_time();
	if (philo->num % 2)
		usleep(15000);
	while (philo->game->death)
	{
		pthread_mutex_lock(&(philo->game->forks[philo->lfork]));
		print(philo->num, "has taken a fork", *philo->game);
		pthread_mutex_lock(&(philo->game->forks[philo->rfork]));
		print(philo->num, "has taken a fork", *philo->game);
		pthread_mutex_lock(&(philo->game->while_eating));
		print(philo->num, "is eating", *philo->game);
		philo->eatcount++;
		philo->tictoc = present_time();
		pthread_mutex_unlock(&(philo->game->while_eating));
		pass(philo->game->eattime);
		pthread_mutex_unlock(&(philo->game->forks[philo->lfork]));
		pthread_mutex_unlock(&(philo->game->forks[philo->rfork]));
		print(philo->num, "is sleeping", *philo->game);
		pass(philo->game->sleeptime);
		print(philo->num, "is thinking", *philo->game);
	}
	return (0);
}

void	is_full(t_philo *philo, t_game *game)
{
	int	i;

	i = -1;
	if (game->mineat != -1)
		while (++i < game->numphilo && \
				game->philos[i].eatcount >= game->mineat)
			continue ;
	if (i == game->numphilo)
	{
		game->mineat = 0;
		game->death = 0;
	}
}

void	is_starve(t_philo *philo, t_game *game)
{
	int	i;

	while (game->mineat)
	{
		i = -1;
		while (++i < philo->game->numphilo)
		{
			usleep(100);
			pthread_mutex_lock(&(philo->game->while_eating));
			if (present_time() - game->philos[i].tictoc > game->livetime)
			{
				print(philo->num, "died", *game);
				game->death = 0;
			}
			pthread_mutex_unlock(&(philo->game->while_eating));
		}
		if (!game->death)
			break ;
		is_full(philo, game);
	}
}
