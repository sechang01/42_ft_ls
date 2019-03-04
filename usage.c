/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:52:45 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 22:44:31 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage_check(t_usage *usage, char *argv)
{
	int		i;

	i = 1;
	if (!argv[1])
		ft_printf("ls: -: No such file or directory\n");
	while (argv[i])
		is_usage(usage, argv[i++]);
}

void	is_usage(t_usage *usage, char c)
{
	if (c == 'l')
		usage->l = 1;
	else if (c == 'R')
		usage->bigr = 1;
	else if (c == 'a')
		usage->a = 1;
	else if (c == 'r')
		usage->r = 1;
	else if (c == 't')
		usage->t = 1;
	else
	{
		ft_printf("ls: illegal option -- %c\n\
				usage: ./ft_ls [-lRart] [file ...]\n", c);
		exit(1);
	}
}
