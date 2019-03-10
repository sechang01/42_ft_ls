/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 21:47:14 by sechang           #+#    #+#             */
/*   Updated: 2019/03/09 16:51:10 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sum_blocks(t_node *node, t_usage *usage)
{
	if (usage->a)
		usage->total_blocks += usage->statbuf.st_blocks;
	else if (!usage->a)
		if (node->name[0] != '.')
			usage->total_blocks += usage->statbuf.st_blocks;
}

int			dir_file_util(t_node **node, char *path, t_usage *usage)
{
	if (path)
	{
		lstat(path, &usage->statbuf);
		if (!(usage->statbuf.st_mode & S_IRUSR))
		{
			ft_printf("ft_ls: %s: Permission denied\n", (*node)->name);
			return (1);
		}
	}
	else if ((*node)->permission[1] == '-')
	{
		ft_printf("ft_ls: %s: Permission denied\n", (*node)->name);
		return (1);
	}
	if (*node && !path)
		ls_free(*node);
	return (0);
}

void		open_dir_files(t_node *node, t_usage *usage,
		char *path, t_node *new)
{
	DIR				*dir;
	struct dirent	*test;
	char			*tmp_path;

	dir = (path) ? opendir(path) : opendir(node->name);
	if (dir_file_util(&node, path, usage))
		return ;
	while ((test = readdir(dir)))
	{
		lstat(test->d_name, &usage->statbuf);
		if (path && (tmp_path = ft_strjoin(path, test->d_name)))
		{
			lstat(tmp_path, &usage->statbuf);
			free(tmp_path);
		}
		node = new;
		new = node_init(test->d_name, usage->statbuf);
		sum_blocks(new, usage);
		if (node)
			new->next = node;
	}
	node = new;
	closedir(dir);
	sort_and_print(node, usage);
}
