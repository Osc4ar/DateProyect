#include <stdio.h>
#include <stdlib.h>

struct date
{
	int d, m, y;
};
typedef struct date Date;

int f()
{
	return 1;
}

Date* newDate(char f[])
{
	Date* nvo = (Date*)malloc(sizeof(Date));
	nvo -> d = (((f[3] - 48) * 10) + (f[4] - 48));
	nvo -> m = (((f[0] - 48) * 10) + (f[1] - 48));;
	nvo -> y = (((f[6] - 48) * 1000) + ((f[7] - 48) * 100) + ((f[8] - 48) * 10) + (f[9] - 48));
	return nvo;
}

int repeat(char a[])
{
	if(strcmp(a, "Si") == 0)
		return 1;
	if(strcmp(a, "SI") == 0)
		return 1;
	if(strcmp(a, "si") == 0)
		return 1;
	if(strcmp(a, "S") == 0)
		return 1;
	if(strcmp(a, "s") == 0)
		return 1;
	return 0;
}

int isAfter(Date *d1, Date *d2)
{
	if(d1 -> m < d2 -> m)
		return 1;
	if(d1 -> m == d2 -> m && d1 -> d <= d2 -> d)
		return 1;
	return 0;
}

int isAfterFeb(Date *da)
{
	if(da -> m > 2 && isLeapYear(da -> y))
		return 1;
	return 0;
}

int isBeforeLeapDay(Date *da)
{
	if(da -> m < 2 || da -> m == 2 && da -> d < 29)
		return 1;
	return 0;
}

int getDaysFromMonths(Date *d1, Date *d2)
{
	int dfm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int m = 0, i;
	for(i = (d2 -> m); i < (d1 -> m); i++)
	{
		m += dfm[i];
	}
	return m;
}

int daysBetween(Date *d1, Date *d2)
{
	int y, m = 0, d = 0, i;
	
	y = ((d2 -> y) - (d1 -> y)) * 365;
	
	if(d1 -> m >= d2 -> m)
	{
		m = getDaysFromMonths(d1, d2) * (-1);
	}
	else
	{
		m = getDaysFromMonths(d2, d1);
	}
	
	d = ((d1 -> d) - (d2 -> d));
	if(isAfter(d1, d2) && d < 0)
		d *= (-1);
	else
	{
		if(d > 0)
			d *= (-1);                                          
	}
	printf("d = %d\nm = %d\ny = %d\nLeap = %d\n", d, m, y, numberOfLeapYears((d1 -> y), (d2 -> y)));
	return y + m + d + numberOfLeapYears((d1 -> y), (d2 -> y)) - isBeforeLeapDay(d2) - isAfterFeb(d1);
}

int dateOK(Date* date)
{
	if(date -> y > 1600)
	{
		if(date -> m <= 12 && date ->  m > 0)
		{
			if(date -> d > 0)
			{
				if(date -> m == 1 && date -> d <= 31)
					return 1;
				else
				{
					if((date -> m == 2 && date -> d <= 29 && isLeapYear(date -> y)) || (date -> m == 2 && date -> d <= 28 && !isLeapYear(date -> y)))
						return 1;
					else
					{
						if(date -> m == 3 && date -> d <= 31)
							return 1;		
						else
						{
							if(date -> m == 4 && date -> d <= 30)
								return 1;	
							else
							{
								if(date -> m == 5 && date -> d <= 31)
									return 1;
								else
								{
									if(date -> m == 6 && date -> d <= 30)
										return 1;	
									else
									{
										if(date -> m == 7 && date -> d <= 31)
											return 1;	
										else
										{
											if(date -> m == 8 && date -> d <= 31)
												return 1;
											else
											{
												if(date -> m == 9 && date -> d <= 30)
													return 1;
												else
												{
													if(date -> m == 10 && date -> d <= 31)
														return 1;
													else
													{
														if(date -> m == 11 && date -> d <= 30)
															return 1;
														else
														{
															if(date -> m == 12 && date -> d <= 31)
																return 1;
															else
																return 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}		
			}
		}
		else
			return 0;
	}
	return 0;
}

int optionOK(char o)
{
	return !(o == 'a' || o == 'b');
}

int isLeapYear(int y)
{
	return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

int numberOfLeapYears(int y1, int y2)
{
	int i, cont = 0;
	for(i = y1; i <= y2; i++)
	{
		if(isLeapYear(i))
			cont++;
	}
	return cont;
}

int main()
{
	int daysForMonth[] = {31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30, 31};
	int months[] = {1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11, 12};
	char option, r[2];
	char firstDate[10], lastDate[10];
	Date *first, *last;
	int ok;
	
	do
	{
		puts("Este programa hace las siguientes funciones respecto a fechas, siempre y cuando las fechas pertenezcan al calendario gregoriano\n");
		puts("que es a partir del año 1600.\n\n");
		puts("a) Calcula cuantos dias hay entre dos fechas ingresadas por el usuario.\n\n");
		puts("b) Dada una fecha inicial y un rango de dias calcula en que dia acaba el rango de dias.\n\n");
		
		do	
		{
			puts("Seleccione una opcion valida:\n");
			scanf("%c", &option);
		}while(optionOK(option));
		
		switch(option)
		{
			case 'a':
				do
				{
					getchar();
					puts("Ingresa la fecha inicial: (mm dd aaaa)\n");
					gets(firstDate);
				
					puts("Ingresa la fecha final: (mm dd aaaa)\n");
					gets(lastDate);
					
					first = newDate(firstDate);
					last = newDate(lastDate);
				
					if(dateOK(first) && dateOK(last))
					{
						ok = 1;
						printf("Han pasado %d dias.\n", daysBetween(first, last));
					}
					else
					{
						ok = 0;
						puts("Fechas invalidas.");
					}
				}while(!ok);
			break;
			
			case 'b':
				getchar();
				puts("Repetir?");
				scanf("%s", &r);	
			break;
			
			default:
				puts("Ingresa una opción valida.");
				r[0] = 's';
			break;
		}
		
	}while(repeat(r));
}
