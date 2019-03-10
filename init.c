/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 13:31:16 by sechang           #+#    #+#             */
/*   Updated: 2019/03/09 15:40:28 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		permissions(t_node *new, struct stat statbuf)
{
	new->permission[0] = (S_ISDIR(statbuf.st_mode)) ? 'd' : '-';
	if (new->s_link)
		new->permission[0] = 'l';
	new->permission[1] = (statbuf.st_mode & S_IRUSR) ? 'r' : '-';
	new->permission[2] = (statbuf.st_mode & S_IWUSR) ? 'w' : '-';
	new->permission[3] = (statbuf.st_mode & S_IXUSR) ? 'x' : '-';
	new->permission[4] = (statbuf.st_mode & S_IRGRP) ? 'r' : '-';
	new->permission[5] = (statbuf.st_mode & S_IWGRP) ? 'w' : '-';
	new->permission[6] = (statbuf.st_mode & S_IXGRP) ? 'x' : '-';
	new->permission[7] = (statbuf.st_mode & S_IROTH) ? 'r' : '-';
	new->permission[8] = (statbuf.st_mode & S_IWOTH) ? 'w' : '-';
	new->permission[9] = (statbuf.st_mode & S_IXOTH) ? 'x' : '-';
	if (statbuf.st_mode & S_ISVTX && new->permission[6] != '-')
		new->permission[9] = 't';
	else if (statbuf.st_mode & S_ISVTX)
		new->permission[9] = 'T';
	new->permission[10] = (new->extend[0]) ? '@' : ' ';
	new->permission[11] = '\0';
	new->size = statbuf.st_size;
	new->links = statbuf.st_nlink;
	new->int_last_mod = statbuf.st_mtime;
	new->nano_last_mod = statbuf.st_mtimespec.tv_nsec;
	new->isdir = S_ISDIR(statbuf.st_mode);
}

t_node		*node_init(char *name, struct stat statbuf)
{
	t_node			*new;
	struct passwd	*pwd;
	struct group	*grp;

	lstat(name, &statbuf);
	new = (t_node*)ft_memalloc(sizeof(t_node));
	new->next = NULL;
	new->name = ft_strdup(name);
	if ((pwd = getpwuid(statbuf.st_uid)))
		new->owner = ft_strdup(pwd->pw_name);
	if ((grp = getgrgid(statbuf.st_gid)))
		new->group = ft_strdup(grp->gr_name);
	new->s_link = NULL;
	if ((S_ISLNK(statbuf.st_mode)))
	{
		new->s_link = malloc(statbuf.st_size + 1);
		readlink(name, new->s_link, statbuf.st_size + 1);
	}
	listxattr(name, new->extend, 1024, XATTR_SHOWCOMPRESSION);
	new->last_mod = ft_strdup(ctime(&statbuf.st_mtime) + 4);
	*ft_strrchr(new->last_mod, ':') = '\0';
	permissions(new, statbuf);
	return (new);
}

t_usage		*init_usage(void)
{
	t_usage *new;

	if (!(new = (t_usage*)ft_memalloc(sizeof(t_usage))))
	{
		ft_printf("Memory could not be allocated.\n");
		exit(1);
	}
	new->total_blocks = 0;
	return (new);
}

void		ls_free(t_node *node)
{
	if (node->name)
		free(node->name);
	if (node->s_link)
		free(node->s_link);
	if (node->owner)
		free(node->owner);
	if (node->group)
		free(node->group);
	if (node->last_mod)
		free(node->last_mod);
	free(node);
}
