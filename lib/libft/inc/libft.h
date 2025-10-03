/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elie <elie@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:08:45 by ebelle            #+#    #+#             */
/*   Updated: 2025/10/03 15:19:48 by elie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>
# include "ft_printf.h"
# include "get_next_line.h"

// /* Testing */
// # include <stdio.h>
// # include <string.h>

/* IO */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* Nums */
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

/* Chars */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isdigit(int c);

int			ft_tolower(int c);
int			ft_toupper(int c);

/* Strs */
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strnstr(const char *big, const char *small, size_t len);

void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strtrim(const char *s1, const char *set);

char		*ft_strjoin(const char *s1, const char *s2);
char		**ft_split(const char *s, char c);
char		*ft_substr(const char *s, unsigned int start, size_t len);

/* Memory */
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);

/* Custom */
long		ft_atol(const char *str);
void		free_array(char ***array);
void		free_and_null(char **str);
char		**copy_array(char **array);
int			is_whitespace(char c);
char		*ft_strndup(const char *s, size_t len);
#endif
