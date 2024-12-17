/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:05:46 by surpetro          #+#    #+#             */
/*   Updated: 2024/04/12 21:27:04 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	putnbr(int n)
{
	char	c;

	if (n >= 10)
		putnbr(n / 10);
	c = (n % 10 + '0');
	write (1, &c, 1);
}

void	ft_receive(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static int	corrector;

	(void)s;
	if (signal == SIGUSR1)
		corrector |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		write (1, &corrector, 1);
		bit = 0;
		corrector = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	write (1, "PID -> ", 7);
	putnbr(pid);
	write (1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receive;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
