#include <stdio.h>
#include <stdlib.h>

struct date
{
	int d, m, y;
};
typedef struct date Date;

Date* newDate(char f[])
{
	Date* nvo = (Date*)malloc(sizeof(Date));
	nvo -> d = (((f[3] - 48) * 10) + (f[4] - 48));
	nvo -> m = (((f[0] - 48) * 10) + (f[1] - 48));;
	nvo -> y = (((f[6] - 48) * 1000) + ((f[7] - 48) * 100) + ((f[8] - 48) * 10) + (f[9] - 48));
	return nvo;
}

int cmpDates(Date* d1, Date* d2)
{
	if(((d1 -> y) <= (d2 -> y)) && ((d1 -> m) <= (d2 -> m)) && ((d1 -> d) < (d2 -> d)))
		return 1;
	return 0;
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

int daysBetween(Date *d1, Date *d2)
{
	int y, m = 0, d = 0, i;
	int dfm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if((d1 -> m) == (d2 -> m))
	{
		m = 0;
		if(d1 -> d <= d2 -> d)
		{
			y = (d2 -> y) - (d1 -> y);
			d = (d2 -> d) - (d1 -> d);
		}
		else
		{
			y = (d2 -> y) - (d1 -> y) - 1;
			
			for(i = (d1 -> m) + 1; i == d2 -> m; i++)
			{
				if(i > 12)
					i = 1;
				m += dfm[i];
			}
		}
	}
	else
	{
		if((d1 -> m) < (d2 -> m))
		{
			y = (d2 -> y) - (d1 -> y);	
		}
		else
		{
			y = (d2 -> y) - (d1 -> y) - 1;		
		}
	}
	
	if(d2 -> m <= 2 && d2 -> d <= 28)
		return ((y * 365) + numberOfLeapYears(d1 -> y, d2 -> y) + d + m) - 1;
	return ((y * 365) + numberOfLeapYears(d1 -> y, d2 -> y) + d + m);
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
