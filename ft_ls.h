/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 15:40:29 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 22:05:42 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <fcntl.h>
# include <dirent.h>
# include <time.h>
# include "Libft/inc/libft.h"
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <string.h>
# include <errno.h>

typedef struct		s_usage
{
	int				l;
	int				bigr;
	int				a;
	int				r;
	int				t;
	int				total_blocks;
	t_queue			*dir;
	struct stat		statbuf;
}					t_usage;

typedef struct		s_node
{
	struct s_node	*next;
	char			*name;
	char			*owner;
	char			*group;
	char			*last_mod;
	char			permission[12];
	char			extend[1024];
	char			*s_link;
	int				size;
	int				links;
	int				int_last_mod;
	long			nano_last_mod;
	int				isdir;
}					t_node;

void				separate_dir_n_files(int i, t_usage *usage, int argc,
					char **argv);
void				print_dir_n_files(t_node *filetop, t_node *dirtop,
					t_usage *usage);
void				open_dir_files(t_node *node, t_usage *usage,
					char *path, t_node *new);

void				print_out(t_node *node, t_usage *usage,
					t_node *front, t_node *rear);
void				print_out2(t_node *node, t_usage *usage);
void				print_out_lst(t_node *node, t_usage *usage);
t_node				*make_lst_of_dir(t_node *node, t_usage *usage,
					t_node *front);

void				sort_and_print(t_node *node, t_usage *usage);
t_node				*sort_list(t_node *lst, t_usage *usage);
t_node				*sort_list_time(t_node *lst, t_usage *usage,
					t_node *tmp, t_node *prev);
t_node				*sort_list_time2(t_node *lst, t_usage *usage);

char				*ls_strjoin(char const *s1, char const *s2);
char				*full_path(t_queue *lst);
void				ls_free(t_node *node);
void				swap_node(t_node **start, t_node **prev, t_node **curr);

t_node				*node_init(char *name, struct stat statbuf);
void				is_usage(t_usage *usage, char c);
void				usage_check(t_usage *usage, char *argv);
t_usage				*init_usage(void);
void				usage_flags(char c);

#endif
