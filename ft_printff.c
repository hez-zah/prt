#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int print_char(int c)
{
	return (write (1, &c, 1));
}

int print_str(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		count += print_char(*str);
		str++;
	}
	return (count);
}

int	print_digit(int nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count += write (1, "-", 1);
		-nbr;
	}
	if (nbr < 10)
		count += print_char(nbr + '0');
	else 
	{
		count += print_digit(nbr / 10);
		count += print_digit(nbr % 10);
	}
	return (count);
}

int	print_hexa(unsigned int nbr, char specifier)
{
	int count;
	char *symboles;
	char *symbolesU;

	count = 0;
	symboles = "0123456789abcdef";
	symbolesU = "0123456789ABCDEF";
	if (nbr > 16)
	{
		count += print_hexa(nbr / 16, specifier);
		count += print_hexa(nbr % 16, specifier);
	}	
	else
	{
		if (specifier == 'X')
			count += print_char(symbolesU[nbr % 16]);
		else 
			count += print_char(symboles[nbr % 16]);
	}
	return (count);
}

void print_hex_ptr(unsigned long nbr)
{
	int	count;
	char *symboles;

	count = 0;
	symboles = "0123456789abcdef";
	if (nbr > 16)
	{
		print_hex_ptr(nbr / 16);
		print_hex_ptr(nbr % 16);
	}
	else 
		print_char(symboles[nbr % 16]);
	return (count);
}

int set_hexa(unsigned long nbr)
{
	int len;

	len = 0;
	while (nbr)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

int print_ptr(unsigned long nbr)
{
	int count;

	count += write(1,"0x",2);
	if (nbr == 0)
		count += write(1,"0",1);
	else
	{
		print_hex_ptr(nbr);
		count += set_hexa(nbr);
	}
	return (count);
}

static int ft_handl(va_list ap, char specifier)
{
	int count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(ap, int));
	else if (specifier == 's')
		count += print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count += print_ptr(va_arg(ap, unsigned long));
	else if(specifier == 'd' || specifier == 'i')
		count += print_digit(va_arg(ap, int));
	else if(specifier == 'x' || specifier == 'X')
		count += print_hexa(va_arg(ap, unsigned int), specifier);
	return (count);
}
int ft_printf(const char *str , ...)
{
	int count ;
	va_list ap;

	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{   
			++str; 
			count += ft_handl(ap, *str);
		}
		else 
			count += write(1, str, 1);
		str++;
	}
	va_end(ap);
	return (count);
}

int main()
{
	int p = 17;
	int count = ft_printf("my name is %s I'm %i , group sg is %c hhhhhh%x , llllll%p\n", "said" ,25, 'A', 110, p);
	int fount = printf("my name is %s I'm %i , group sg is %c hhhhhh%x , llllll%p\n", "said" ,25, 'A', 110, p);
	printf("%d  ]]]]  %d\n", count, fount);
}