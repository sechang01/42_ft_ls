/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:30:56 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 21:57:44 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_strjoin(char const *s1, char const *s2)
{
	char		*newstr;
	int			midlen;
	int			fulllen;

	midlen = ft_strlen(s1);
	fulllen = ft_strlen(s2) + midlen + 2;
	newstr = 0;
	if (!(newstr = (char *)malloc(sizeof(char) * fulllen)))
		return (0);
	if (s1)
	{
		ft_strcpy(newstr, s1);
	}
	ft_strcat(newstr, s2);
	newstr[fulllen - 2] = '/';
	newstr[fulllen - 1] = '\0';
	return (newstr);
}

char	*full_path(t_queue *lst)
{
	t_sqnode	*tmp;
	char		*fullpath;
	char		*tmppath;

	tmppath = 0;
	fullpath = (char *)malloc(sizeof(char) * 0);
	tmp = lst->front;
	while (tmp)
	{
		tmppath = ls_strjoin(fullpath, (char *)tmp->data);
		free(fullpath);
		fullpath = tmppath;
		tmp = tmp->next;
	}
	if (tmppath[0] == '/' && tmppath[1] == '/')
	{
		fullpath = ft_strdup(tmppath + 1);
		free(tmppath);
		return (fullpath);
	}
	return (fullpath);
}

void	print_dir_n_files(t_node *filetop, t_node *dirtop, t_usage *usage)
{
	if (filetop)
		sort_and_print(filetop, usage);
	if (dirtop)
	{
		sort_list(dirtop, usage);
		if (usage->t)
			sort_list_time(dirtop, usage, 0, 0);
		print_out2(dirtop, usage);
	}
}

void	separate_dir_n_files(int i, t_usage *usage, int argc, char **argv)
{
	t_node		*filetop;
	t_node		*dirtop;
	t_node		*node;

	dirtop = 0;
	filetop = 0;
	while (i < argc)
	{
		node = node_init(argv[i++], usage->statbuf);
		if (!node->int_last_mod)
			ft_printf("ft_ls: %s: No such file or directory\n", argv[i++]);
		else if (node->isdir)
		{
			if (dirtop)
				node->next = dirtop;
			dirtop = node;
		}
		else
		{
			if (filetop)
				node->next = filetop;
			filetop = node;
		}
	}
	print_dir_n_files(filetop, dirtop, usage);
}

int	main(int argc, char **argv)
{
	int			i;
	t_usage		*usage;
	t_node		*node;

	i = 1;
	usage = init_usage();
	while (i < argc)
	{
		if (argv[i][0] == '-')
			usage_check(usage, argv[i]);
		else
			break ;
		i++;
	}
	if (!argv[i])
	{
		node = node_init(".", usage->statbuf);
		open_dir_files(node, usage, NULL, NULL);
	}
	else
	{
		separate_dir_n_files(i, usage, argc, argv);
	}
	return (0);
}
