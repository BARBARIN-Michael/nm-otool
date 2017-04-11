/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarbari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:12:25 by mbarbari          #+#    #+#             */
/*   Updated: 2017/04/10 16:34:28 by mbarbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/stat.h>
# include <stdint.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <mach/machine.h>

# include "libft.h"

# define BASE16 "0123456789abcdef"

typedef struct s_item_sym	t_item_sym;
typedef struct s_type_seg	t_type_seg;

struct						s_item_sym
{
	uint64_t	ptr;
	uint8_t		n_type;
	uint8_t		n_sect;
	char		*str;
};

/*
** handle_open.c
*/
void						*handle_open(const char *exe, const char *file,
											struct stat *buf);
void						handle_close(void *data, struct stat *buf);
void						handle_parse(const void *mem);

/*
** handle_sym.c
*/
t_list						*handle_sym(void *mem, struct symtab_command *sym);
void						add_list_sym(t_list **lst, t_item_sym *item);
t_item_sym					insert_item(void *symlst, char *str, size_t i);

/*
** print.c
*/
void						print_hex(uint64_t ptr);
int							print_type(t_item_sym *sym, int *seg);
void						print_content(t_list *elem, int *seg);

/*
** singleton.c
*/
struct mach_header			get_header(const void *mem);

/*
** error.c / error_file.c / error_header.c
*/
void						error(const char *error);
void						error_usage(const char *arg);
void						error_file(const char *exe, const char *arg,
										const char *error);
void						error_header(const char *error);

#endif
