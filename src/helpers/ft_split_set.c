#include <stdlib.h>
#include "libft.h"

static void	*ft_free(char **ret, long nstr)
{
	while (nstr >= 0)
	{
		free(ret[nstr]);
		nstr--;
	}
	free(ret);
	return (NULL);
}

static size_t	is_in_set(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	n_splits(const char *s, const char *set)
{
	size_t	i;
	size_t	nstr;
	size_t	in_str;

	i = 0;
	nstr = 0;
	in_str = 0;
	while(s[i] != '\0')
	{
		if ((is_in_set(s[i], set) == 0) && in_str == 0)
		{
			nstr++;
			in_str = 1;
		}
		else if (is_in_set(s[i], set) == 1)
			in_str = 0;
		i++;
	}
	return (nstr);
}

static char **fill_str_array(const char *s, const char *set, char **ret)
{
	size_t	i;
	size_t	len;
	long	nstr;
	long	start_i;

	i = 0;
	nstr = 0;
	start_i = -1;
	len = ft_strlen(s);
	while(i <= len)
	{
		if ((is_in_set(s[i], set) == 0) && start_i < 0)
			start_i = i;
		else if ((is_in_set(s[i], set) == 1 || s[i] == '\0') && start_i >= 0)
		{
			ret[nstr] = ft_substr(s, start_i, i - start_i);
			if (ret[nstr] == NULL)
				return (ft_free(ret, nstr));
			nstr++;
			start_i = -1;
		}
		i++;
	}
	return (ret);
}

char	**ft_split_set(char const *s, char const *set)
{
	char	**ret;

	ret = ft_calloc(n_splits(s, set) + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	return (fill_str_array(s, set, ret));
}
