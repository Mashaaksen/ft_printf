#ifndef PRINTF_FT_PRINTF_H
#define PRINTF_FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"
#include <stdint.h>

typedef struct  s_print
{
    int         mynus;
    int         plus;
    int         null;
    int         space;
    int         hash;
    int         weidth;
    int         accuracy;
    char        *size;
    int        proc;
    char        type;
    int         cost;
    char        *p;
}               t_print;

int     ft_printf( const char *format, ... );
int    fill(const char *str, t_print *print, va_list ap);
t_print *check_accurancy(const char **str, va_list ap, t_print *print);
t_print *check_width(const char **str, va_list ap, t_print *print);
t_print *check_flag(const char **str, t_print *print);
t_print *check_size(const char **str, t_print *print);
int     find_spec(char *str);
t_print *check_type(const char **str, t_print *print);
void       full(t_print **print);
int       ft_print(t_print *print, va_list ap);
int		size_v(unsigned long long value, int base);
char	*ft_itoa_base(unsigned long long value, char c);
char			*ft_itoa_long(long long n);
t_print     *change(t_print *print);
int     check_all(t_print *print, char **str);
char     *proc(const char *str, t_print *print, va_list ap, int *ret);
char    *accuarcy(t_print *print, char *str);
char    *flag_weidth(t_print *print, char *str);
char    *find_str(t_print *print, va_list ap);
long long		ft_int_min(long long n);
int		ft_len_int(long long n);
char    *ft_wchar(wchar_t *str, t_print *print);


#endif //PRINTF_FT_PRINTF_H
