/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongguki <dongguki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:04:59 by dongguki          #+#    #+#             */
/*   Updated: 2021/11/18 16:06:41 by dongguki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error1(t_game *game)
{
	if (game->philos)
		free(game->philos);
	if (game->forks)
		free(game->forks);
	return (0);
}

int	error2(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->numphilo)
		if (game->philos[i].thid)
			pthread_detach(game->philos[i].thid);
	i = -1;
	while (++i < game->numphilo)
		pthread_mutex_destroy(&(game->forks[i]));
	return (error1(game));
}

void	print(int num, char *str, t_game game)
{
	if (!game.death)
		return ;
	printf("%4lldms %d %s\n", present_time() - game.start_time, num + 1, str);
	return ;
}

void	pass(int time)
{
	long long	i;

	i = present_time();
	while (1)
	{
		if (present_time() - i >= (long long)time)
			break ;
		usleep(100);
	}
}

long long	present_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
