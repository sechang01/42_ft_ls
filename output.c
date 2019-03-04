/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:32:39 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 23:39:45 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_and_print(t_node *node, t_usage *usage)
{
	node = sort_list(node, usage);
	if (usage->t)
		node = sort_list_time(node, usage, 0, 0);
	if (usage->l && !usage->args)
		ft_printf("total %d\n", usage->total_blocks);
	print_out(node, usage, NULL, NULL);
}

static void		next_n_free(t_node **node)
{
	t_node		*tmp;

	tmp = *node;
	*node = (*node)->next;
	ls_free(tmp);
}

void			print_out_list(t_node *node, t_usage *usage)
{
	if (!usage->l)
		ft_printf("%s\n", node->name);
	if (usage->l)
	{
		ft_printf("%s", node->permission);
		ft_printf("%2d", node->links);
		ft_printf(" ");
		ft_printf("%-7s", node->owner);
		ft_printf("  ");
		ft_printf("%-7s", node->group);
		ft_printf(" ");
		ft_printf("%6d", node->size);
		ft_printf(" ");
		ft_printf("%+s", node->last_mod);
		ft_printf(" ");
		ft_printf("%s", node->name);
		if (node->s_link)
			ft_printf(" -> %s", node->s_link);
		ft_printf("\n");
	}
}

void			print_out(t_node *node, t_usage *usage,
		t_node *front, t_node *rear)
{
	t_node *tmp;

	while (node)
	{
		if (!usage->a && node->name[0] == '.')
		{
			next_n_free(&node);
			continue ;
		}
		if (usage->bigr && node->isdir && node->name[0] != '.')
		{
			if (!front && (front = node_init(node->name, usage->statbuf)))
				rear = front;
			else if ((tmp = node_init(node->name, usage->statbuf)))
			{
				rear->next = tmp;
				rear = tmp;
			}
		}
		print_out_list(node, usage);
		next_n_free(&node);
	}
	print_out2(front, usage);
}

void			print_out2(t_node *front, t_usage *usage)
{
	t_node		*tmp;
	char		*fullpath;
	char		*fullname;

	if (!usage->dir)
		usage->dir = queue_init_lst();
	while (front)
	{
		queue_in(usage->dir, (void *)front->name);
		fullpath = full_path(usage->dir);
		fullname = ft_strdup(fullpath);
		if (usage->args != 1 || usage->bigr)
			ft_printf("\n");
		if (!(*ft_strrchr(fullname, '/') = '\0') && usage->bigr)
			ft_printf("./");
		if (usage->args != 1 || usage->bigr)
			ft_printf("%s:\n", fullname);
		free(fullname);
		open_dir_files(front, usage, fullpath, NULL);
		free(fullpath);
		queue_out_rear(usage->dir);
		tmp = front;
		front = front->next;
		ls_free(tmp);
	}
}
