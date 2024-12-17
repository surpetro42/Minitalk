/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:05:46 by surpetro          #+#    #+#             */
/*   Updated: 2024/04/18 11:48:03 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	num;
	int	i;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] == ' ' || (str[i] == '\n') || (str[i] == '\t')
			|| (str[i] == '\v') || (str[i] == '\f') || str[i] == '\r'))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	handler(int sig)
{
	int		i;
	char	*s;

	i = 0;
	s = "DONE";
	if (sig == SIGUSR1)
		while (*s)
			write(1, &*s++, 1);
	write(1, "\n", 1);
}

void	ft_bits_message(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c & (0x01 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t		pid;
	int			i;

	if (argc != 3)
	{
		write(2, "the arguments are either more or less, try again\n", 50);
		exit(1);
	}
	else
	{
		pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			signal(SIGUSR1, handler);
			signal(SIGUSR2, handler);
			ft_bits_message(pid, argv[2][i]);
			i++;
		}
		ft_bits_message(pid, '\n');
	}
	return (0);
}
