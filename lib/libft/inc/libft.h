/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:24:41 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/29 11:23:52 by dbakker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_list	t_list;

typedef struct s_list
{
	void	*content;
	t_list	*next;
}	t_list;

//copy_array.c

char	**copy_array(char **array);
char	**copy_narray(char **array, size_t n);
// free_and_null.c

void	free_and_null(char **str);
// free_array.c

void	free_array(char ***array);
void	ft_free2d(void **ptr, size_t size);

// ft_atoi.c

int32_t	ft_atoi(const char *str);
// ft_bzero.c

void	ft_bzero(void *buffer, size_t num);
// ft_calloc.c

void	*ft_calloc(size_t num, size_t size);
// ft_intlen.c

size_t	ft_intlen(int32_t number);
// ft_isthing1/2.c

int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
// ft_itoa.c

char	*ft_itoa(int32_t num);
// ft_listadd.c

void	ft_listadd_front(t_list **list, t_list *new);
void	ft_listadd_back(t_list **list, t_list *new);
// ft_listdel.c

void	ft_listdelone(t_list *list, void (*del)(void *));
void	ft_listclear(t_list **list, void (*del)(void *));
// ft_listfunc.c

void	ft_listiter(t_list *list, void (*func)(void *));
t_list	*ft_listmap(t_list *list, void *(*func)(void *), void (*del)(void *));
// ft_listlast.c

t_list	*ft_listlast(t_list *list);
t_list	*ft_listbefore_last(t_list *list);
// ft_listnew.c

t_list	*ft_listnew(void *content);
// ft_listsize.c

size_t	ft_listsize(t_list *list);
// ft_mem.c

void	*ft_memchr(const void *ptr, int character, size_t size);
int32_t	ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t num);
void	*ft_memset(void *ptr, int character, size_t num);
// ft_puttype_fd.c

int32_t	ft_putchar_fd(char character, int fd);
int32_t	ft_putstr_fd(const char *str, int fd);
int32_t	ft_putendl_fd(const char *str, int fd);
int32_t	ft_putnum_fd(int32_t num, int fd);
// ft_split.c

char	**ft_split(char const *str, char delimiter);
// ft_strdup.c

char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t num);
// ft_strfind.c

char	*ft_strchr(const char *str, int character);
char	*ft_strrchr(const char *str, int character);
// ft_strfunc.c

void	ft_striteri(char *str, void (*func)(uint32_t, char*));
char	*ft_strmapi(const char *str, char (*func)(uint32_t, char));
// ft_strjoin.c

char	*ft_strjoin(const char *dest, const char *src);
// ft_strlc.c

size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
// ft_strlen.c

size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);
// ft_strncmp.c

int32_t	ft_strncmp(const char *str1, const char *str2, size_t num);
// ft_strnstr.c

char	*ft_strnstr(const char *haystack, const char *needle, size_t num);
// ft_strtrim.c

char	*ft_strtrim(char const *str, char const *set);
// ft_substr.c

char	*ft_substr(const char *str, uint32_t start, size_t num);
// ft_tocase.c

int		ft_tolower(int character);
int		ft_toupper(int character);

// CUSTOM

char	*ft_strreplace(const char *base_str, const char *pattern, const char *replacement);
void	ft_repoint(char **old_str, char *new_str);
size_t	ft_count_occurrences(const char *base_str, const char *pattern);
// ed_convert_list.c

t_list	*array_to_llist(const char **array);
char	**llist_to_array(const t_list *list);
#endif