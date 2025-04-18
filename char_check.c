/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:33:02 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/18 13:33:02 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_char_isblank(char c)
{
	return (c == '\t' || c == ' ');
}

int	ft_char_isnewline(char c)
{
	return (c == '\n');
}

int	ft_char_isoperator(char c)
{
	return (c == '"' || c == '\'' || c == ')' || c == '(' || c == '|'
		|| c == '&');
}

int	ft_char_isdollar(char c)
{
	return (c == '$');
}

int	ft_char_isquote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_char_iseoi(char c)
{
	return (c == '\0');
}
