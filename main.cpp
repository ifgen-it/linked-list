/*
Вар. 23.
Посредством структур реализуйте односвязный список для хранения окружностей. Обеспечьте следующую функциональность:
А) добавить окружность в список;
Б) циклически сдвинуть список на N элементов вправо;
В) циклически сдвинуть список на N элементов влево;
Г) сохранить данные в файле
Д) считать данные из файла
*/

#define _CRT_SECURE_NO_WARNINGS
//#include <tchar.h>
#include <iostream>
#include <cstdio>
#include "list.h"


using namespace std;

// инициализировали Односвязный список  { NODE* Head; size_t Size; }
SLIST List = { nullptr, 0 };

int main()
{

	// печать лого
	PrintStripe();
	printf("*         SINGLY LINKED LIST of Circles        *\n");
	PrintStripe();

	PrintMenu();	// печать основного меню
	bool NeedMiniMenu; 
	bool Continue = true;

	while (Continue)
	{
		NeedMiniMenu = true;

		int Choice;
		scanf("%1d", &Choice);	// выбор пункт меню
		cout << endl;

		int DelNumber = 0;	// номер удаляемого узла
		int Side = 0;	// направление сдвига списка
		int ShiftSize = 0;		// количество элементов сдвига списка

		switch (Choice)
		{
		case 0:
			PrintMenu();			// печать основного меню
			NeedMiniMenu = false;
			break;
		case 1:
			PrintList(List);		// печать всего списка
			break;
		case 2:
			InsertNode(List);		// добавить элемент списка - окружность
			break;
		case 4:
			TruncateList(List);		// очистить список
			break;
		case 3:
			printf("Choose Circle number to delete: ");	// удалить выбранный элемент списка
			scanf("%d", &DelNumber);
			DeleteNode(List, DelNumber);
			break;
		case 7:
			SaveToFile(List);		// сохранить в файл
			break;
		case 6:
			LoadFromFile(List);		// загрузить из файла
			break;
		case 5:												// циклически сдвинуть список
			printf("(1)FORWARD (0)BACKWARD: ");		// выбор направления сдвига
			scanf("%d", &Side);
			printf("SHIFT size: ");							// величина сдвига
			scanf("%d", &ShiftSize);
			ShiftList(List, Side, ShiftSize);				// сдвиг
			break;
		case 8:
			system("cls");			// очистка экрана
			break;
		case 9:
			Continue = false;
			NeedMiniMenu = false;
			break;
		default:
			printf("Incorrect number of menu item. Try again!\n\n");
			break;
		}
		if (NeedMiniMenu) {
			PrintMiniMenu();		// печать МиниМеню
		}
	}

	
	TruncateList(List);

	return 0;
}