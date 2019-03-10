/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sorting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:56:47 by sechang           #+#    #+#             */
/*   Updated: 2019/03/09 16:36:20 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_node(t_node **start, t_node **prev, t_node **curr)
{
	t_node		*buf;

	if (*curr == *start)
		*start = (*curr)->next;
	if (*prev)
		(*prev)->next = (*curr)->next;
	buf = *curr;
	*curr = (*curr)->next;
	buf->next = (*curr)->next;
	(*curr)->next = buf;
	*curr = *start;
}

t_node	*sort_list(t_node *lst, t_usage *usage)
{
	t_node		*tmp;
	t_node		*prev;

	tmp = lst;
	prev = NULL;
	while (lst->next)
	{
		if ((usage->r) ? ft_strcmp(lst->name, lst->next->name) < 0 :
				ft_strcmp(lst->name, lst->next->name) > 0)
		{
			swap_node(&tmp, &prev, &lst);
		}
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
	lst = tmp;
	return (lst);
}

t_node	*sort_list_time(t_node *lst, t_usage *usage, t_node *tmp, t_node *prev)
{
	prev = NULL;
	tmp = lst;
	while (lst->next)
	{
		if (lst->int_last_mod == lst->next->int_last_mod)
		{
			if ((usage->r) ? (lst->nano_last_mod > lst->next->nano_last_mod) :
					(lst->nano_last_mod < lst->next->nano_last_mod))
			{
				swap_node(&tmp, &prev, &lst);
				continue ;
			}
		}
		if ((usage->r) ? (lst->int_last_mod > lst->next->int_last_mod) :
				(lst->int_last_mod < lst->next->int_last_mod))
			swap_node(&tmp, &prev, &lst);
		else
		{
			prev = lst;
			lst = lst->next;
		}
	}
	lst = tmp;
	return (lst);
}
