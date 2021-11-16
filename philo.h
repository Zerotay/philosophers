/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongguki <dongguki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:05:02 by dongguki          #+#    #+#             */
/*   Updated: 2021/11/16 23:05:44 by dongguki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

struct s_game;

typedef struct	s_philo
{
	pthread_t		thid;
	int				num;
	int				lfork;
	int				rfork;
	struct s_game	*game;
	long long		tictoc;
	int				eatcount;
}				t_philo;

typedef struct	s_game
{
	int				numphilo;
	int				livetime;
	int				eattime;
	int				sleeptime;
	int				mineat;
	int				death;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	while_eating;
}				t_game;

int			error(t_game *game);
int			ft_atoi(const char *str);
void		print(int num, char *str, t_game game);
void		pass(int time);
long long	present_time(void);
void		*rotate(void *all);
void		is_starve(t_philo *philo, t_game *game);

#endif