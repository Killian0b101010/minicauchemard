/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_palindrome.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:37:03 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:27:26 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_palindrome(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	j--;
	while (i < j)
	{
		if (str[i] != str[j])
			return (0);
		i++;
		j--;
	}
	return (1);
}
/*
int	main(void)
{
	char	str1[] = "kayak";
	char	str2[] = "hello";

	if (ft_is_palindrome(str1))
		printf("%s is a palindrome\n", str1);
	else
		printf("%s is not a palindrome\n", str1);
	if (ft_is_palindrome(str2))
		printf("%s is a palindrome\n", str2);
	else
		printf("%s is not a palindrome\n", str2);
	return (0);
}
 */