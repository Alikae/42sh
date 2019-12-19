#include "sh_word_expansion.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _GNU_SOURCE
#include <stdio.h>

char *operator(t_arith *arith)
{
	if (arith->next_op == PLUS)
		return("plus");
	else if (arith->next_op == MINUS)
		return("minus");
	else if (arith->next_op == MULTI)
		return("multi");
	else if (arith->next_op == DIV)
		return("division");
	else if (arith->next_op == MODULO)
		return("modulo");
	else if (arith->next_op == MORE)
		return("more");
	else if (arith->next_op == LESS)
		return("less");
	else if (arith->next_op == MORE_EQUAL)
		return("more equal");
	else if (arith->next_op == LESS_EQUAL)
		return("less equal");
	else if (arith->next_op == AND)
		return("and");
	else if (arith->next_op == OR)
		return("or");
	else if (arith->next_op == AND_AND)
		return("and and");
	else if (arith->next_op == OR_OR)
		return("or or");
	else if (arith->next_op == DIFFERENT)
		return("different");
	else if (arith->next_op == EQUAL)
		return("equal");
	else
		return(sh_long_itoa(arith->nb));
}

void bst_print_dot_aux(t_arith *a, int  stream)
{
	static int i;

	i++;
    if (a->next)
    {
        dprintf(stream, "    __%s__%p -> __%s__%p;\n", operator(a), a, operator(a->next), a->next);
        bst_print_dot_aux(a->next, stream);
    }
    if (a->sub)
    {
        dprintf(stream, "   __%s__%p -> __%s__%p;\n", operator(a),a, operator(a->sub),a->sub);
        bst_print_dot_aux(a->sub, stream);
    }   
}

void bst_print_dot(t_arith *a, char  *str, char *arth)
{
	int stream;

	stream = open(str, O_CREAT | O_TRUNC | O_RDWR, S_IRWXO);
	printf("stream = %i\n", stream);
    dprintf(stream, "digraph BST {\n");
    dprintf(stream, "    node [fontname=\"Arial\"];\n");
	dprintf(stream, "	label = <<font color='red'><b>%s</b></font><br/>>;\n", arth);

    if (!a)
        dprintf(stream, "\n");
    else if (!a->next && !a->sub)
        dprintf(stream, "    %ld;\n", a->nb);
    else
        bst_print_dot_aux(a, stream);
    dprintf(stream, "}\n");
	close(stream);
}
