#include "../../includes/minishell.h"

int	ft_atoi(const char*str)
{
	int	i;
	int	signal;
	int	number;

	i = 0;
	signal = 1;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		number = number * 10;
		number += str[i] - 48;
		i++;
	}
	return (signal * number);
}

int	ft_isnumeric(char*str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_lstsize(t_list*lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst -> next;
		size++;
	}
	return (size);
}

int	ft_lstsize_mod(t_command*lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst -> next;
		size++;
	}
	return (size);
}

void	ft_putendl_fd(char*s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char*s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

static size_t	ft_countword(char const*s, char c)
{
	size_t	i;
	size_t	word_count;
	int		new_word;

	if (s == 0)
		return (0);
	i = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		new_word = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			if (new_word == 0)
			{
				word_count++;
				new_word = 1;
			}
			i++;
		}
	}
	return (word_count);
}

static size_t	try_malloc(char**dest, size_t pos, size_t size)
{
	size_t	i;

	i = 0;
	dest[pos] = malloc(size);
	if (dest[pos] == 0)
	{
		while (i < pos)
		{
			free(dest[i++]);
		}
		free(dest);
		return (1);
	}
	return (0);
}

static size_t	ft_fill_words(char**dest, char const*s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (try_malloc(dest, i, len + 1))
				return (1);
			ft_strlcpy(dest[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

char	**ft_split(char const*s, char c)
{
	size_t	words;
	char	**dest;

	words = ft_countword(s, c);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (s == 0 || dest == 0)
		return (0);
	if (ft_fill_words(dest, s, c))
		return (0);
	dest[words] = 0;
	return (dest);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	temp_c;
	char	*temp_s;

	temp_c = (char)c;
	temp_s = (char *)s;
	i = ft_strlen(temp_s);
	if (temp_s[i] == '\0' && temp_c == '\0')
		return (temp_s + i);
	while (i >= 0)
	{
		if (temp_s[i] == temp_c)
			return (temp_s + i);
		i--;
	}
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

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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

char	*ft_strcpy(char*dest, char*src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}