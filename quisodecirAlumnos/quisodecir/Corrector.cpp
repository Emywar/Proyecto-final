/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define ipalabras 3300
#define fer 0
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[NUMPALABRAS][TAMTOKEN], int iEstadisticas[NUMPALABRAS], int &iNumElementos)
{
	//Declaracion de variables
	FILE* fpdic;
	char szpalabras[NUMPALABRAS][TAMTOKEN], cauxpala[TAMTOKEN];
	int i, i2, iauxletras, iband, iconta, icontapala, icontaesta, icmp, idoc, isalta, isig, ilon, iletras, iestadisticas[NUMPALABRAS];

	idoc = fopen_s(&fpdic, szNombre, "r");//Apertura
	if (fpdic != NULL)
	{
		//Lectura
		for (i2 = 0; !feof(fpdic); i2++)
		{
			fgets(cauxpala, 4000, fpdic);
			for (i = 0; i < strlen(cauxpala); i++)
			{
				if (cauxpala[i]==',')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i]=='.')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i] == '-')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i] == '?')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i] == '=')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i] == '+')
				{
					cauxpala[i] = '\0';
				}
				if (cauxpala[i] == '!')
				{
					cauxpala[i] = '\0';
				}
			}
		}
		//Cierre
		fclose(fpdic);//Cierre de archivo
		i2 = i2 - 2;
		
		//Eliminacion de caracteres especiales
		for (icontapala = 0; icontapala<i2-1; icontapala++)
		{
			_strlwr_s(szpalabras[icontapala], TAMTOKEN);
			ilon = strlen(szpalabras[icontapala]);
			for (iletras = 0; iletras <= ilon; iletras++)
			{
				if (szpalabras[icontapala][iletras] == '(')
				{
					iauxletras = iletras;
					while (szpalabras[icontapala][iletras] != '\0')
					{
						szpalabras[iletras][TAMTOKEN] = szpalabras[iletras + 1][TAMTOKEN];
						iletras++;
					}
					iletras = iauxletras;
					ilon--;
				}
				if (szpalabras[icontapala][iletras] == ')')
				{
					iauxletras = iletras;
					while (szpalabras[icontapala][iletras] != '\0')
					{
						szpalabras[icontapala][iletras] = szpalabras[icontapala][iletras+ 1];
						iletras++;
					}
					iletras = iauxletras;
					ilon--;
				}
				if (szpalabras[icontapala][iletras] == ',')
				{
					iauxletras = iletras;
					while (szpalabras[icontapala][iletras] != '\0')
					{
						szpalabras[icontapala][iletras] = szpalabras[icontapala][iletras + 1];
						iletras++;
					}
					iletras = iauxletras;
					ilon--;
				}
				if (szpalabras[icontapala][iletras] == '.')
				{
					iauxletras = iletras;
					while (szpalabras[icontapala][iletras] != '\0')
					{
						szpalabras[icontapala][iletras] = szpalabras[icontapala][iletras + 1];
						iletras++;
					}
					iletras = iauxletras;
					ilon--;
				}
			}
		}

		//Burbujazo
		for (icontapala = 0; icontapala < i2 - 1; icontapala++)
		{
			for (iauxletras = 0; iauxletras < i2 - 1; iauxletras++)
			{
				if (iauxletras<i2-2)
				{
					if ((strcmp(szpalabras[iauxletras], szpalabras[iauxletras + 1])) >= 1)
					{
						strcpy_s(cauxpala, TAMTOKEN, szpalabras[iauxletras]);
						strcpy_s(szpalabras[iauxletras], TAMTOKEN, szpalabras[iauxletras + 1]);
						strcpy_s(szpalabras[iauxletras + 1], TAMTOKEN, cauxpala);
					}
				}
				if (iauxletras>=i2-2)
				{
					strcpy_s(szpalabras[iauxletras], TAMTOKEN, szpalabras[iauxletras + 1]);
				}
			}
		}
		
		//Repeticion
		for (icontapala = 0; icontapala <= i2; icontapala++)
		{
			if (strcmp(szpalabras[icontapala], szpalabras[icontapala + 1]) == 0 )
			{
				strcpy_s(szpalabras[icontapala+2], TAMTOKEN, szpalabras[icontapala+1]);
				szpalabras[icontapala][TAMTOKEN] = '\0';
				iestadisticas[icontapala+1]++;
			}
		}

		for (iNumElementos = 0; iNumElementos < icontapala-2; iNumElementos++)
		{
			strcpy_s(szPalabras[iNumElementos], TAMTOKEN, szpalabras[iNumElementos]);
			iEstadisticas[iNumElementos] = iestadisticas[iNumElementos];
		}
	}
}
/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Declaracion de variables
	int iaux, iaux2, iaux3, iconta, iconta2, iconta3, iconta4; 
	char szpalaleida[TAMTOKEN], szaux[TAMTOKEN], szpalasuge[ipalabras][TAMTOKEN], szletras[39] = "abcdefghijklmnñopqrstuvwxyzáéíóú";

	//Copiado de palabra a una auxiliar
	strcpy_s(szpalaleida, TAMTOKEN, szPalabraLeida);

	//Iniciar con eliminacion
	iaux=strlen(szpalaleida);
	for (iconta = 0; iconta < iaux; iconta++)
	{
		if (iconta == 0)
		{
			iconta2 = iconta;
			while (szpalaleida[iconta2 + 1] != '\0')
			{
				szpalasuge[iconta][iconta2] = szpalaleida[iconta2 + 1];
				iconta2++;
			}
			szpalasuge[iconta][iconta2] = '\0';
			iconta2 = 0;
		}
		if (iconta > 0)
		{
			for (iconta2 = 0; iconta2 < iaux; iconta2++)
			{
				if (iconta2 < iconta)
				{
					szpalasuge[iconta][iconta2] = szpalaleida[iconta2];
				}
				if (iconta2 == iconta)
				{
					szpalasuge[iconta][iconta2] = szpalaleida[iconta2+1];
					iconta2++;
				}
				if (iconta2 > iconta)
				{
					szpalasuge[iconta][iconta2-1] = szpalaleida[iconta2];
				}
			}
			szpalasuge[iconta][iconta2 - 1] = '\0';
		}
	}

	//Trasposicion de caracteres
	for (iconta2 = 0; iconta2 < iaux-1; iconta2++)
	{
		if (iconta2 == 0)
		{
			szpalasuge[iconta][iconta2] = szpalaleida[iconta2 + 1];
			szpalasuge[iconta][iconta2 + 1] = szpalaleida[iconta2];
			for (iconta3 = iconta2; iconta3 < iaux-2; iconta3++)
			{
				szpalasuge[iconta][iconta3 + 2] = szpalaleida[iconta3 + 2];
			}
			szpalasuge[iconta][iconta3 + 2] = '\0';
			iconta3 = 0;
		}
		if (iconta2 > 0)
		{
			for (iconta3 = 0; iconta3 < iaux; iconta3++)
			{
				if (iconta3 < iconta2)
				{
					szpalasuge[iconta][iconta3] = szpalaleida[iconta3];
				}
				if (iconta3 == iconta2)
				{
					szpalasuge[iconta][iconta3] = szpalaleida[iconta3 + 1];
					szpalasuge[iconta][iconta3 + 1] = szpalaleida[iconta3];
					for (iconta4 = iconta3; iconta4 < iaux-2; iconta4++)
					{
						szpalasuge[iconta][iconta4 + 2] = szpalaleida[iconta4 + 2];
					}
					szpalasuge[iconta][iconta4 + 2] = '\0';
					iconta4 = 0;
				}
				if (iconta2 > iconta)
				{
					szpalasuge[iconta][iconta3] = szpalaleida[iconta3];
				}
			}
		}
		iconta++;
	}

	//Sustitucion de caracteres por alfabeto
	for (iconta2=0; iconta2<iaux; iconta2++)
	{
		if (iconta2 == 0)
		{
			for (iconta3 = 0; iconta3 < 32; iconta3++)
			{
				szpalasuge[iconta][0] = szletras[iconta3];
				for (iconta4= 1; iconta4 <= iaux-1; iconta4++)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4];
				}
				szpalasuge[iconta][iconta4] = '\0';
				iconta++;
			}
		}
		if (iconta2 > 0)
		{
			iconta3 = 0;
			iconta4 = 0;
			while (iconta3 < 32)
			{
				while (iconta4 < iconta2)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4];
					iconta4++;
				}
				while (iconta4 == iconta2)
				{
					szpalasuge[iconta][iconta4] = szletras[iconta3];
					iconta4++;
				}
				while (iconta4 < iaux)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4];
					iconta4++;
				}
				szpalasuge[iconta][iconta4] = '\0';
				iconta++; iconta4 = 0; iconta3++;
			}
		}
	}

	//Sustitucion de espacios por alfabeto
	iaux2 = (iaux);
	for (iconta2 = 0;iconta2<=iaux2;iconta2++)
	{
		iaux3 = iconta2 % 2;
		if (iaux3 != 0)
		{
			iconta3 = 0;
			iconta4 = 0;
			while (iconta3 < 32)
			{
				while (iconta4 < iconta2)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4];
					iconta4++;
				}
				while (iconta4 == iconta2)
				{
					szpalasuge[iconta][iconta4] = szletras[iconta3];
					iconta4++;
				}
				while (iconta4 <= iaux)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4-1];
					iconta4++;
				}
				szpalasuge[iconta][iconta4] = '\0';
				iconta++; iconta4 = 0; iconta3++;
			}
		}
		if (iaux3==0)
		{
			iconta3 = 0;
			iconta4 = 0;
			while (iconta3 < 32)
			{
				while (iconta4 < iconta2)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4];
					iconta4++;
				}
				while (iconta4 == iconta2)
				{
					szpalasuge[iconta][iconta4] = szletras[iconta3];
					iconta4++;
				}
				while (iconta4 <= iaux)
				{
					szpalasuge[iconta][iconta4] = szPalabraLeida[iconta4-1];
					iconta4++;
				}
				szpalasuge[iconta][iconta4] = '\0';
				iconta++; iconta4 = 0; iconta3++;
			}
		}
	}

	//Pasar a la lista candidatas y numeros
	for (iNumSugeridas = 0; iNumSugeridas<iconta; iNumSugeridas++)
	{
		strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, szpalasuge[iNumSugeridas]);
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{
	//Declaracion de variables
	int iaux4, iaux2, icompara, ipalabra, ipeso[NUMPALABRAS];
	char szlisfin[NUMPALABRAS][TAMTOKEN], szaux[TAMTOKEN];

	//Comparacion de palabras
	ipalabra = 0; iaux4 = 0;
	for (iaux4 = 0; iaux4 <= iNumElementos; iaux4++)
	{
		for (iaux2 = 0; iaux2 <= iNumSugeridas; iaux2++)
		{
			icompara=strcmp(szPalabras[iaux4], szPalabrasSugeridas[iaux2]);
			if (icompara == 0)
			{
				strcpy_s(szlisfin[ipalabra], TAMTOKEN, szPalabras[iaux4]);
				iEstadisticas[iaux4]=ipeso[ipalabra];
				ipalabra++;
			}
		}
	}

	//Depurar lista
	iaux4 = 0;
	for (iaux4 = 0; iaux4 <= ipalabra; iaux4++)
	{
		icompara = strcmp(szlisfin[iaux4], szlisfin[iaux4 + 1]);
		if (icompara == 0)
		{
			for (iaux2 = iaux4; iaux2 <= ipalabra - 1; iaux2++)
			{
				if (iaux2 <=  ipalabra- 3) 
				{
					strcpy_s(szlisfin[iaux2 + 1], TAMTOKEN, szlisfin[iaux2 + 2]);
				}
				if (iaux2 == ipalabra - 2)
				{
					szlisfin[iaux2][TAMTOKEN] = '\0';
					szlisfin[iaux2 + 1][TAMTOKEN] = '\0';
					//ipeso[iaux2 + 1] = 0;
					ipalabra--;
				}
				//iaux4--;
			}
		}
	}

	//Copiado de probabilidades y palabras
	iaux4 = 0;
	for (iaux4 = 0; iaux4 < 3300; iaux4++)
	{
		iPeso[iaux4] = ipeso[iaux4];
		strcpy_s(szListaFinal[iaux4], TAMTOKEN, szlisfin[iaux4]);
	}
	iNumLista = iaux4;
}
