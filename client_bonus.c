/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:52:39 by rpandipe          #+#    #+#             */
/*   Updated: 2024/04/21 22:56:58 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *nptr)
{
	int	ans;
	int	sign;
	int	i;

	ans = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ans = ans * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * ans);
}

void	ft_ctob(int pid, char c)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

void	sig_handler(int sign, siginfo_t *info, void *context)
{
	static int	i;
	char		b;

	(void)info;
	(void)context;
	if (sign == SIGUSR2)
		i++;
	else if (sign == SIGUSR1)
	{
		b = i / 8 + '0';
		write(1, "Number of bytes recieved is ", 28);
		write(1, &b, 1);
	}
}

int	main(int argc, char **argv)
{
	int			pid;
	int			i;
	struct sigaction	sa;

	i = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (argc == 3 && (sigaction(SIGUSR1, &sa, NULL) == -1 && \
		sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != 0)
		{
			ft_ctob(pid, argv[2][i]);
			i++;
		}
		ft_ctob(pid, '\0');
	}
	else
	{
		write (1, "Error\n", 6);
		return (1);
	}
	return (0);
}
