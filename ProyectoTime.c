#include <stdio.h>
#include <stdlib.h>

/*
	Autor: Oscar I. Castillo Magaña
	Grupo: 1CM5  	Materia: Algoritmia y programación estructurada
	Fecha: 13/01/16
	Proyecto: Calculador de Fechas
*/

struct date //Estructura para guardar el día, mes y año de una fecha.
{
	int d, m, y;
};
typedef struct date Date;

Date* newDate(char f[]) //Función que se encarga de sacar los valores del mes, día y año de la cadena que ingresa el usuario.
{
	Date* nvo = (Date*)malloc(sizeof(Date));
	nvo -> d = (((f[3] - 48) * 10) + (f[4] - 48));
	nvo -> m = (((f[0] - 48) * 10) + (f[1] - 48));;
	nvo -> y = (((f[6] - 48) * 1000) + ((f[7] - 48) * 100) + ((f[8] - 48) * 10) + (f[9] - 48));
	return nvo;
}

int repeat(char a[]) //Función que valida si ingresan si o alguna variante de esa cadena.
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

int isAfter(Date *d1, Date *d2) //Regresa 1 si el mes y el día de la fecha 2 son mayores que el mes o día de la fecha 1.
{
	if(d1 -> m < d2 -> m)
		return 1;
	if(d1 -> m == d2 -> m && d1 -> d <= d2 -> d)
		return 1;
	return 0;
}

int isAfterFeb(Date *da) //Retorna 1 si la fecha dada es después de febrero y es año bisiesto.
{
	if(da -> m > 2 && isLeapYear(da -> y))
		return 1;
	return 0;
}

int isBeforeLeapDay(Date *da) //Retorna 0 si no es año bisiesto. Si es antes de febrero o antes del 29 de febrero.
{
	if(!isLeapYear(da -> y))
		return 0;
	if(da -> m < 2)
		return 1;
	if(da -> m == 2)
	{
		if(da -> d < 29)
			return 1;
		return 0;
	}
	return 0;
}

int getDaysFromMonths(Date *d1, Date *d2) //Esta función retorna el número de días que 
{										  //existen entre el mes de la fecha 1 y el mes de la fecha 2.
	int dfm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int m = 0, i, n;
	for(i = (d2 -> m); i < (d1 -> m); i++)
	{
		m += dfm[i];
	}
	return m;
}

int daysBetween(Date *d1, Date *d2) //Función que retorna el número de días que existen entre dos fechas dadas.
{
	int y, m = 0, d = 0, i;
	
	y = ((d2 -> y) - (d1 -> y)) * 365; //Obtiene la diferencia de años y los convierte a días.
	
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
	return y + m + d + numberOfLeapYears((d1 -> y), (d2 -> y)) - isBeforeLeapDay(d2) - isAfterFeb(d1);
}

int dateOK(Date* date) //Valida que la fecha es después del añp 1600 y que los días y meses son correctos.
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

int optionOK(char o) //Verifica que se selecciono una opción correcta
{
	return !(o == 'a' || o == 'b' || o == 'c' || o == 'A' || o == 'B' || o == 'C');
}

int isLeapYear(int y) //Valida si el año es un año bisiesto
{
	return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

int numberOfLeapYears(int y1, int y2) //Cuenta los años bisiestos entre dos fechas dadas.
{
	int i, cont = 0;
	for(i = y1; i <= y2; i++)
	{
		if(isLeapYear(i))
			cont++;
	}
	return cont;
}

int setMonths(Date *d, int lapse) //Esta función recibe una fecha y un lapso de días. Lo que realiza es ir sumando el número de días de cada
{								//mes hasta que el lapso sea más pequeño que la longitud del mes.
	int dfm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//Número de días por mes.
	int i;
	for(i = (d -> m) - 1; lapse > dfm[i]; i++)
	{
		if(isLeapYear(d -> y)) //Convierte la longitud de febrero de 28 a 29 si es año bisiesto.
			dfm[1] = 29;
		else
			dfm[1] = 28;
			
		lapse -= dfm[i];
		
		if(d -> m != 12) //Se verifica que no es diciembre.
			(d -> m) = (d -> m) + 1;	
		else //Si es diciembre el año aumenta y el mes se posiciona en 1.
		{
			i = -1;
			(d -> y) = (d -> y) + 1;
			(d -> m) = 1;
		}
	}
	
	return lapse;
}

void setDays(Date *da, int lapse) //Esta función agrega a la fecha los días restantes del lapso. Verificando que no sobrepasen la longitud
{								  //del mes. Además si se llega al 31 de diciembre para al siguiente año.
	int dfm[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;
	
	if(isLeapYear(da -> y))
		dfm[1] = 29;
	else
		dfm[1] = 28;
			
	if(da -> d > dfm[(da -> m) - 1]) //Ajusta si el número de días es mayor que la longitud del mes.
	{
		if(da -> m == 12) //Si es diciembre aumenta un año, el mes y día se vuelven 1.
		{
			da -> d = 1;
			da -> m = 1;
			(da -> y)++;
		}
		else
		{
			da -> d = 1;
			(da -> m)++;
		}
	}
	
	for(i = (da -> m) - 1; lapse > 0; lapse--) //Se iran agregando días y disminuyendo el lapso 1 a 1 hasta que el paso sea 0.
	{
		if(isLeapYear(da -> y))
			dfm[1] = 29;
		else
			dfm[1] = 28;
			
		if(da -> d < dfm[i]) //Se verifica que los días sean menores que la longitud del mes. Sino, se ajusta el mes.
			(da -> d)++;
		else
		{
			if(i == 11)
			{
				i = 0;
				da -> m = 1;
				da -> d = 1;
				(da -> y)++;
			}
			else
			{
				i++;
				(da -> m)++;
				da -> d = 1;	
			}
		}
	}
	
	if(da -> d > dfm[(da -> m) - 1])
	{
		if(da -> m == 12)
		{
			da -> d = 1;
			da -> m = 1;
			(da -> y)++;
		}
		else
		{
			da -> d = 1;
			(da -> m)++;
		}
	}
}

int setYear(Date *da, int lapse) //Función que avanza los años y los resta del lapso dependiendo de si es bisiesto o no.
{
	int ylong;
	if((isLeapYear(da -> y) && (da -> m <= 2)) || ((isLeapYear((da -> y) + 1)) && (da -> m) > 2))
		ylong = 366;
	else
		ylong = 365;
		
	while(lapse / ylong > 0) //Mientras que el lapso sea mayor de 366 o 365 según el caso seguirá aumentando los años y disminuyendo el lapso.
	{
		if((isLeapYear(da -> y) && (da -> m <= 2)) || ((isLeapYear((da -> y) + 1)) && (da -> m) > 2))
			ylong = 366;
		else
			ylong = 365;
			
		(da -> y)++;
		lapse = lapse - ylong;
	}
	return lapse;
}

Date* getLastDate(Date *d1, int lapse) //Retorna la fecha en la que acaba un lapso de tiempo.
{
	Date* last = (Date*) malloc(sizeof(Date));
	//Se parte creando una fecha con los mismo datos de la fecha 1.
	last -> y = d1 -> y;
	last -> m = d1 -> m;
	last -> d = d1 -> d;
	
	lapse = setYear(last, lapse); //Se definen los años y se modifica el lapso.
	lapse = setMonths(last, lapse); //Se defefinen los meses y se modifica el lapso.
	setDays(last, lapse); //Se definen los días.
	
	return last;
}

int main()
{
	char option, r[2]; //Option es para guardar la opción que escoge el usuario. r almacena la respuesta de repetir o no del usuario.
	char firstDate[10], lastDate[10]; //Cadenas que almacenan las fechas.
	Date *first, *last; //Apuntadores a Date para manejar las fechas.
	int ok, lapse; //Lapse es el número de días que se utilizan en la opción b. ok es un boolean.
	
	do
	{
		puts("\n\n\nEste programa hace las siguientes funciones respecto a fechas, siempre y cuando las fechas pertenezcan\nal calendario gregoriano que es a partir del anio 1600.\n\n");
		puts("a) Calcula cuantos dias hay entre dos fechas ingresadas por el usuario.\n\n");
		puts("b) Dada una fecha inicial y un rango de dias calcula en que dia acaba el rango de dias.\n\n");
		puts("c) Acerca de...\n\n");
		
		do	
		{
			puts("Seleccione una opcion valida:\n");
			scanf("%c", &option);
		}while(optionOK(option)); //Verifica si ingresan a, b o c. En caso contrario vuelve a pedir una opción.
		
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
					
					first = newDate(firstDate); //Se llena first y last con el valor de Date que retorna newDate.
					last = newDate(lastDate);	//Usando como parametro la cadena que ingrese el usuario.
				
					if(dateOK(first) && dateOK(last)) //Verifica que las fechas cumplen con el formato
					{
						ok = 1; 
						if(first -> y <= last -> y) //Se verifica si la fecha 1 es menor que la fecha 2.
							printf("Han pasado %d dias.\n", daysBetween(first, last)); //Si es así se llama a la función normalmente.
						else
							printf("Han pasado -%d dias.\n", daysBetween(last, first)); //Si no, se intencambian las fechas y se agrega el
						getchar(); 														//el signo menos.
						puts("Volver a pantalla principal?");
						scanf("%s", &r);
					}
					else
					{
						ok = 0;
						puts("Fechas invalidas.");
					}
				}while(!ok); //ok funciona para controlar la repetición de la solicitud de fechas.
			break;
			
			case 'b':
				do
				{
					getchar();
					puts("Ingresa la fecha inicial: (mm dd aaaa)\n");
					gets(firstDate);
					first = newDate(firstDate); //Se obtiene la fecha 1 con newDate y la cadena que ingresa el usuario.
					puts("Ingresa el lapso de dias:\n");
					scanf("%d", &lapse);
					if(dateOK(first) && lapse > 0) //Se veirifica que la fecha inicial es correcta y el lapso es positivo.
					{
						ok = 1;
						last  = getLastDate(first, lapse); //La fecha final se obtiene con el retorno de getLastDate, la fecha inicial y el lapso.
						printf("La fecha final (en formato mm/dd/aaaa) es: %02d/%02d/%02d.\n", last -> m, last -> d, last -> y);
						getchar();
						puts("Volver a pantalla principal?");
						scanf("%s", &r);
					}
					else
					{
						ok = 0;
						puts("Datos invalidos.");
					}
				}while(!ok); //Si algún dato no es correcto, se volverán a pedir.
			break;
			
			case 'c':
				puts("\n\nAutor: Oscar I. Castillo Magaña\nGrupo: 1CM5  	Materia: Algoritmia y programación estructurada\nFecha: 13/01/16\nProyecto: Calculador de Fechas\n\nPulse una tecla para continuar...\n\n");
				getchar();
				getchar();
				r[0] = 's';
			break;
			
			default: //Si no se selecciona una opción valida se vuelve a pedir seleccionar una opción correcta.
				puts("Ingresa una opción valida.");
				r[0] = 's';
			break;
		}
		
	}while(repeat(r));
}
