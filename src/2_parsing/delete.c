#include "../../includes/minishell.h"

void	ft_bzero(void*s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		*p = 0;
		i++;
		p++;
	}
}

t_list	*ft_lst_last(t_list*lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

char	*ft_strdup(const char*src)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*dest;

	dest = (void *)malloc(number * size);
	if (dest == 0)
		return (0);
	ft_bzero(dest, number * size);
	return (dest);
}

t_command	*ft_lst_last_command(t_command*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_strcmp(char*s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_lstadd_back(t_list**lst, t_list*new)
{
	t_list	*last;

	last = ft_lst_last(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last -> next = new;
}
