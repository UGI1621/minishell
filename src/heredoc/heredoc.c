/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:22 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 17:27:54 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include <fcntl.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <unistd.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;
// 	char	*temp;

// 	len = 0;
// 	if (!s || !*s)
// 		return (len);
// 	temp = (char *)s;
// 	while (temp[len])
// 		len++;
// 	return (len);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t len)
// {
// 	unsigned char	*temp1;
// 	unsigned char	*temp2;
// 	size_t			i;

// 	temp1 = (unsigned char *)s1;
// 	temp2 = (unsigned char *)s2;
// 	i = 0;
// 	while (i < len && *temp1 && *temp2)
// 	{
// 		if (*temp1 != *temp2)
// 			return (*temp1 - *temp2);
// 		i++;
// 		temp1++;
// 		temp2++;
// 	}
// 	if (i < len)
// 		return (*temp1 - *temp2);
// 	return (0);
// }

/*===============================*/

static void	write_no_extend(char *line, int heredoc_fd)
{
	int	i;

	i = -1;
	while (line[++i])
		write(heredoc_fd, &line[i], 1);
	write(heredoc_fd, "\n",1);
}

static void	write_extend(char *line, int heredoc_fd)
{
	char	*res;
	char	*temp;
	int		i;
	int		s;

	i = -1;
	s = 0;
	while(line[++i])
	{
		if (line[i] != '$')
			write(heredoc_fd, &line[i], 1);
		else
		{
			s = i;
			while(line[i] && !is_quote(line[i]) && !is_wspace(line[i]))
				i++;
			temp = ft_substr(line, s + 1, i -s);
			write(heredoc_fd, getenv(temp), ft_strlen(getenv(temp)));
			free(temp);
		}
	}
	write(heredoc_fd, "\n", 1);
}

void	heredoc_proc(char *delimiter, int heredoc_fd, int quote_flag)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		if (quote_flag)
			write_no_extend(line, heredoc_fd);
		else
			write_extend(line, heredoc_fd);
		free(line);
	}
	free(delimiter);
}

// int	main(void)
// {
// 	heredoc_proc("2");
// 	return (0);
// }
