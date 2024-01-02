/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:34:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 00:46:24 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 512
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>

int		get_next_line(int fd, char **out_line);
char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(const char *s);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);
char	*ft_strdup_gnl(const char *src);
char	*ft_strjoin_gnl(char *s1, char const *s2, size_t len);

#endif