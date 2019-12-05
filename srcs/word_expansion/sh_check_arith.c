#include "sh.h"

int		sh_valid_arith(char *str)
{
	int		i;
	int		par;

	i = 0;
	par = 0;
	return (1);
	while (str[i])
	{
		if (str[i] == '(')
			par++;
		else if (str[i] == ')')
			par--;
		//else if (sh_all_operator_char(str[i]) &&
		i++;
	}
	return (0);
}
