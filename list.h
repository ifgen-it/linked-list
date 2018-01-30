
struct CIRCLE {		// Данные окружности
	float Radius;
	float X;
	float Y;
};

struct NODE {			// данные узла
	CIRCLE Data;
	NODE* pNext;		// указатель на следующий элемент
	};

struct SLIST {		// singly list
	NODE* Head;		// указатель на 1й элемент списка
	size_t Size;	// количество узлов в списке
};

void PrintMenu();							// печать Меню

void PrintMiniMenu();						// печать МиниМеню

void PrintStripe();							// печать полоски

void PrintList(SLIST &List);				// Печать списка

void AddCircle(CIRCLE &ItemCircle);			// Добавление информации об окружности

void InsertNode(SLIST &List);				// Вставка нового узла

void TruncateList(SLIST &List);				// Очистка всего списка

void DeleteNode(SLIST &List, int Number);	// Удаление выбранного узла

void SaveToFile(SLIST &List);				// Сохранение в файл

void LoadFromFile(SLIST &List);				// Загрузка из файла

void ShiftList(SLIST &List, int Side, int ShiftSize);	// Циклический сдвиг списка
