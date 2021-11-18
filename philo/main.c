/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongguki <dongguki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:04:49 by dongguki          #+#    #+#             */
/*   Updated: 2021/11/18 16:17:28 by dongguki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_base(t_game *game, int gc, char **gv)
{
	game->numphilo = ft_atoi(gv[1]);
	game->livetime = ft_atoi(gv[2]);
	game->eattime = ft_atoi(gv[3]);
	game->sleeptime = ft_atoi(gv[4]);
	game->death = 1;
	game->philos = 0;
	game->forks = 0;
	game->mineat = -1;
	if (gc == 6)
	{
		game->mineat = ft_atoi(gv[5]);
		if (game->mineat <= 0)
			return (1);
	}
	if (game->numphilo < 2 || game->numphilo > 200 || game->livetime < 0 || \
	game->eattime < 0 || game->sleeptime < 0)
		return (1);
	return (0);
}

int	init_game(t_game *game, int gc, char **gv)
{
	int	i;

	if (init_base(game, gc, gv))
		return (1);
	game->philos = (t_philo *)malloc(sizeof(t_philo) * game->numphilo);
	if (!game->philos)
		return (error1(game));
	game->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
				* game->numphilo);
	if (!game->forks)
		return (error1(game));
	i = -1;
	while (++i < game->numphilo)
		pthread_mutex_init(&(game->forks[i]), NULL);
	pthread_mutex_init(&(game->while_eating), NULL);
	return (0);
}

void	end_thread(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->numphilo)
		pthread_join(game->philos[i].thid, 0);
	i = -1;
	while (++i < game->numphilo)
		pthread_mutex_destroy(&(game->forks[i]));
	pthread_mutex_destroy(&(game->while_eating));
	free(game->philos);
	free(game->forks);
	return ;
}

int	main(int gc, char **gv)
{
	int		i;
	t_game	game;

	if (init_game(&game, gc, gv))
		return (error1(&game));
	i = -1;
	while (++i < game.numphilo)
	{
		game.philos[i].thid = 0;
		game.philos[i].num = i;
		game.philos[i].lfork = i;
		game.philos[i].rfork = (i + 1) % game.numphilo;
		game.philos[i].game = &game;
		game.philos[i].eatcount = 0;
	}
	i = -1;
	game.start_time = present_time();
	while (++i < game.numphilo)
		if (pthread_create(&(game.philos[i].thid), NULL, rotate, \
			&(game.philos[i])))
			return (error2(&game));
	is_starve(game.philos, &game);
	end_thread(&game);
	return (0);
}
