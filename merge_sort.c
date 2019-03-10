/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 14:44:36 by sechang           #+#    #+#             */
/*   Updated: 2019/03/09 16:54:00 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_node		*ls_mergesort(t_node **headref, t_usage *usage)
{
	t_node	*head;
	t_node	*a;
	t_node	*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return (NULL);
	frontbacksplit(head, &a, &b);
	ls_mergesort(&a, usage);
	ls_mergesort(&b, usage);
	*headref = sortedmerge(a, b, usage);
	return (*headref);
}

t_node		*sortedmerge(t_node *a, t_node *b, t_usage *usage)
{
	t_node *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((usage->r) ? ft_strcmp(a->name, b->name) > 0 :
			ft_strcmp(a->name, b->name) < 0)
	{
		result = a;
		result->next = sortedmerge(a->next, b, usage);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next, usage);
	}
	return (result);
}

void		frontbacksplit(t_node *source, t_node **frontref, t_node **backref)
{
	t_node	*fast;
	t_node	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}
