/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbakker <dbakker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:24:41 by dbakker           #+#    #+#             */
/*   Updated: 2025/10/08 23:05:06 by dbakker          ###   ########.fr       */
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

int32_t	ft_atoi(const char *str);

void	ft_bzero(void *buffer, size_t num);

void	*ft_calloc(size_t num, size_t size);

size_t	ft_intlen(int32_t number);

bool	ft_isalpha(int c);
bool	ft_isascii(int c);
bool	ft_isdigit(int c);
bool	ft_isprint(int c);
bool	ft_isalnum(int c);

bool	ft_isspace(int c);

char	*ft_itoa(int32_t num);

void	*ft_memchr(const void *ptr, int character, size_t size);
int32_t	ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t num);
void	*ft_memset(void *ptr, int character, size_t num);

int32_t	ft_putchar_fd(char character, int fd);
int32_t	ft_putstr_fd(const char *str, int fd);
int32_t	ft_putendl_fd(const char *str, int fd);
int32_t	ft_putnum_fd(int32_t num, int fd);

char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t num);

char	*ft_strchr(const char *str, int character);
char	*ft_strrchr(const char *str, int character);

void	ft_striteri(char *str, void (*func)(uint32_t, char*));
char	*ft_strmapi(const char *str, char (*func)(uint32_t, char));

char	*ft_strjoin(const char *dest, const char *src);

size_t	ft_strlcpy(char *dest, const char *src, size_t num);
size_t	ft_strlcat(char *dest, const char *src, size_t num);

size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);

void	ft_free2d(void **ptr, size_t size);
char	**copy_array(char **array);
void	free_and_null(char **str);
void	free_array(char ***array);

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int character);
int		ft_toupper(int character);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstbefore_last(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
#endif