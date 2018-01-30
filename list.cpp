#define _CRT_SECURE_NO_WARNINGS

#include "list.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

// печать в файл
void SaveToFile(SLIST &List){

	FILE* f = fopen("List.txt", "w");		// открываем файл для записи
	if (f)									// если удалось открыть файл
	{
	
		fprintf(f,"SINGLY LINKED LIST of Circles\n");
		fprintf(f,"Size: %d\n\n", List.Size);

		NODE* pTemp = List.Head;	// начинаем обход с Головы
		if (pTemp){
			int Counter = 1;
			fprintf(f,"| NUM | RADIUS        | COORD.X       | COORD.Y       |\n");
			fprintf(f,"-------------------------------------------------------\n");

			while (pTemp){				// пока указатель не 0, то этот элемент списка печатаем
				fprintf(f,"| %-2d  | %-14g| %-14g| %-14g|\n", Counter, pTemp->Data.Radius, pTemp->Data.X, pTemp->Data.Y);
				
				pTemp = pTemp->pNext;	// переуказали на следующий элемент списка
				Counter++;
			}
			fprintf(f,"-------------------------------------------------------\n\n");
		}


		fclose(f);											// закрыли файл
		cout << "List was saved in file: 'List.txt'\n\n";
	}
	else
	{										// если не удалось открыть файл
		cout << "Cannot open file\n\n";
	}
	
}


// загрузка из файла
void LoadFromFile(SLIST &List){

	FILE* f = fopen("List.txt", "r");		// открываем файл для чтения
	if (f)									// если удалось открыть файл
	{
		TruncateList(List);		// очистка Списка перед загрузкой из файла
								// после очистки List.Size = 0, List.Head = nullptr;

		fscanf(f, "SINGLY LINKED LIST of Circles\n");
	
		fscanf(f, "Size: %d\n\n", &List.Size);
		fscanf(f, "| NUM | RADIUS        | COORD.X       | COORD.Y       |\n");
		fscanf(f, "-------------------------------------------------------\n");
		int Counter = 0;	// вынужденная переменная
		NODE* pTail = nullptr;  // Хвост
		for (int i = 0; i < List.Size; i++){	// заполнение Окружностей информацией из файла
			NODE* pNode = new NODE;		// создали новый узел
			fscanf(f, "| %d  | %f | %f | %f |\n", &Counter, &pNode->Data.Radius, &pNode->Data.X, &pNode->Data.Y);

			if (List.Head){		// если есть хотя бы один элемент списка
			// вставляем в Хвост
				pTail->pNext = pNode;	// в бывший Хвост добавили указатель на новый Хвост
				pNode->pNext = nullptr; // признак конца
				pTail = pNode;			// переопределили Хвост
			}
			else
			{			// если список пустой то новый элемент становится первым и последним
				pNode->pNext = nullptr;		// признак конечного элемента
				List.Head = pNode;			// определили новый элемент Головным
				pTail = pNode; // Хвостом является Голова
			}
		}
		
		fclose(f);											// закрыли файл
		printf("List was loaded from file: 'List.txt'\n\n");
	}
	else
	{										// если не удалось открыть файл
		cout << "Cannot open file\n\n";
	}
}



// печать Списка
void PrintList(SLIST &List){

	printf("SINGLY LINKED LIST of Circles\n");
	printf("Size: %d\n\n", List.Size);

	NODE* pTemp = List.Head;	// начинаем обход с Головы
	if (pTemp){
		int Counter = 1;
		printf("| NUM | RADIUS        | COORD.X       | COORD.Y       |\n");
		printf("-------------------------------------------------------\n");
		
		while (pTemp){				// пока указатель не 0, то этот элемент списка печатаем
			printf("| %-2d  | %-14g| %-14g| %-14g|\n", Counter, pTemp->Data.Radius, pTemp->Data.X, pTemp->Data.Y);
			
			pTemp = pTemp->pNext;	// переуказали на следующий элемент списка
			Counter++;
		}
		printf("-------------------------------------------------------\n\n");
	}
	else
	{
		printf("List is empty!\n\n");
	}
}


// Добавить информации об Окружности
void AddCircle(CIRCLE &ItemCircle){

	printf("Input information about new Circle:\n");
	do
	{
		printf("Radius: ");
		scanf("%g", &ItemCircle.Radius);
		fseek(stdin, 0, 0);

	} while (ItemCircle.Radius <= 0);

		printf("Coordinate X: ");
		scanf("%g", &ItemCircle.X);
		fseek(stdin, 0, 0);

		printf("Coordinate Y: ");
		scanf("%g", &ItemCircle.Y);
		fseek(stdin, 0, 0);
}


// Вставка нового узла
void InsertNode(SLIST &List){

	NODE* pNode = new NODE;		// создали новый узел
	AddCircle(pNode->Data);		// ввели данные

	if (List.Head){		// если есть хотя бы один элемент списка
		pNode->pNext = List.Head;	// в новый элемент добавили указатель на предыдущий -  бывший Головной
		List.Head = pNode;			// новый элемент теперь стал Головным
	}
	else
	{			// если список пустой то новый элемент становится первым и последним
		pNode->pNext = nullptr;		// признак конечного элемента
		List.Head = pNode;			// определили новый элемент Головным
	}
	List.Size++;	// увеличили размер Списка
	printf("Circle added!\n\n");
}


// Очистка списка
void TruncateList(SLIST &List){

	NODE* pTemp = nullptr;	
	int DelNodes = 0;
	if (List.Head){
		while (List.Head){					// пока существует хотя бы 1 первый элемент
			pTemp = List.Head;				//  временный указатель направили на 1й элемент
			List.Head = List.Head->pNext;	// Головой назначили следующий элемент
			delete pTemp;					// освободили память из под бывшей головы
			pTemp = nullptr;
			DelNodes++;
			List.Size--;
		}
		printf("List truncated. Deleted %d Circles!\n\n", DelNodes);
	}
	else
	{
		printf("List was empty!\n\n");
	}
}


// удаление выбранного узла
void DeleteNode(SLIST &List, int Number){

	if (Number > 0 && Number <= List.Size)		// если дали правильный номер, то работаем
	{
			NODE* pTemp = List.Head;
			NODE* pDel = nullptr;
				// начинаем обход с Головы
     	if (pTemp){
     		switch (Number){
     		case 1: //удалить голову
     		pDel = List.Head;
     		List.Head = pDel->pNext;
     		break;
     		
     		default:  // 2 и далее элемент
		     for (int i = 0; i < Number - 2; i++){
				   pTemp = pTemp->pNext;
	     	} // удалить надо pNext
	     	
	     	pDel = pTemp->pNext; // пометили удаляемый
	     	if (pDel->pNext){
	     	pTemp->pNext = pDel->pNext;  // переуказали на новый элемент
	     	}
	     	else {
	     		pTemp->pNext = nullptr;  // удаляемый был последним
	     	}
	     	break;
	     	
     		} // конец Свитч
     		
	     	delete pDel;
	     	pDel = nullptr;
	     	List.Size--;
	     		
 		printf("Circle number %d deleted!\n\n", Number);
    	}
	}
     else
	{					// если дали неправильный номер
		printf("Wrong number. Circle did not deleted!\n\n");
	}
}


// Циклический сдвиг списка
void ShiftList(SLIST &List, int Side, int ShiftSize){

int ShiftTotal = 0;

	NODE* pTemp = List.Head;	// начинаем обход с Головы
	if (pTemp){
		
		while (true){	
			if (pTemp->pNext){
				   pTemp = pTemp->pNext;
				}	
			else {
			   	pTemp->pNext =  List.Head; // замкнули список
			   	break; // закончили
			}
		}
        char SideName[9];
		if (Side == 0){ // если двигать обратно
		ShiftTotal = List.Size - ShiftSize;
		strcpy(SideName, "BACKWARD");	
		}
		else {
			strcpy(SideName, "FORWARD");
			ShiftTotal = ShiftSize;
		}
//двигаем голову
        pTemp = List.Head;	// начинаем обход с Головы
        for (int i = 0; i < ShiftTotal - 1; i++){
        	pTemp = pTemp->pNext;
        }  // следующий элемент - Голова
        List.Head = pTemp->pNext; //опеределили новую Голову
        pTemp->pNext = nullptr; // текущий назначили хвостом
        
        printf("List shifted '%d elements %s'\n\n", ShiftSize, SideName );
	}
		else
	{
		printf("List is empty. It is nothing to shift!\n\n");
	}
	
}

// печать Меню
void PrintMenu(){
	
	printf("(0) MENU:\n");
	PrintStripe();
	printf("(1) Print all Circles\n");
	printf("(2) Add new Circle\n");
	printf("(3) Delete selected Circle\n");
	printf("(4) Delete all Circles\n");
	printf("(5) Shift Circles cyclically\n");
	printf("(6) Load Circles from file\n");
	printf("(7) Save Circles to file\n");
	printf("(8) Clear screen\n");
	printf("(9) Exit\n");
	printf("\n");
	printf(">");
}

void PrintMiniMenu(){
	
	printf("(0)Menu	 (1)Print (2)Add  (3)Delete (4)Truncate\n");
	printf("(5)Shift (6)Load  (7)Save (8)ClrScr (9)Exit\n");
	printf("\n");
	printf(">");
}

void PrintStripe(){
	printf("------------------------------------------------\n");
}