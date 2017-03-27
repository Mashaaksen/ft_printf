#include "ft_printf.h"

t_print     *change(t_print *print)
{
    if (print->type == 'S' || print->type == 'D' || print->type == 'O' || print->type == 'U')
    {
        print->size = ft_strdup("l");
        if (print->type == 'S')
            print->type = 's';
        else if (print->type == 'D')
            print->type = 'd';
        else if (print->type == 'O')
            print->type = 'o';
        else if (print->type == 'U')
            print->type = 'u';
    }
    return (print);
}
