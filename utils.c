/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongguki <dongguki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:04:59 by dongguki          #+#    #+#             */
/*   Updated: 2021/11/16 23:07:43 by dongguki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(t_game *game)
{
	int	i;

	if (game->philos)
		free(game->philos);
	if (game->forks)
		free(game->forks);
	i = -1;
	while (++i < game->numphilo)
		if (game->philos[i].thid)
			pthread_detach(game->philos[i].thid);
	i = -1;
	while (++i < game->numphilo)
			pthread_mutex_destroy(&(game->forks[i]));
	return (1);
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
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
