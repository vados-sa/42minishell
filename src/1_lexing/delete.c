#include "../../includes/minishell.h"

int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

t_token	*ft_lst_last_token(t_token*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	*ft_memset(void*s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		*p = (unsigned char)c;
		i++;
		p++;
	}
	return (s);
}

char	*ft_strchr(const char*s, int c)
{
	int		i;
	char	temp_c;
	char	*temp_s;

	i = 0;
	temp_c = (char)c;
	temp_s = (char *)s;
	while (temp_s[i] != '\0')
	{
		if (temp_s[i] == temp_c)
			return (temp_s + i);
		i++;
	}
	if (temp_s[i] == '\0' && temp_c == '\0')
		return (temp_s + i);
	return (0);
}


size_t	ft_strlcpy(char*dest, const char*src, size_t n)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (n != 0)
	{
		while (src[i] != '\0' && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}

size_t	ft_strlen(const char*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_iseven(int n)
{
	return (n % 2 == 0);
}