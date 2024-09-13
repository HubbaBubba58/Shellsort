//This programm sorting array to increasing with method Shell
#include <iostream>
#include <fstream>
#include <windows.h>
int max_size = 0;						
int set_max_size()									
{
	std::cout << "Введите количество элементов в массиве:\n  > ";
	max_size = 0;;
	std::cin >> max_size;
	return max_size;
}
void print_array(int* array)		
{
	for (int counter = 0; counter < max_size; ++counter)		
	{
		std::cout << counter << '\t';
	}
	std::cout << std::endl;
	for (int counter = 0; counter < max_size; ++counter)	
	{
		std::cout << array[counter] << '\t';
	}
	std::cout << '\n';
}
bool init_array(int* array)
{
	for (int counter = 0; counter < max_size; ++counter)
	{
		array[counter] = rand() % 201 - 101;	
	}
	return 0;
}
int* init_array_from_file(int& max_size)
{
	std::cout << "Введите название файла:\n  > ";
	std::string answer = "";		
	std::cin >> answer;
	std::ifstream file(answer);	
	file >> max_size;						
	if (max_size < 1)			
	{
		return 0;
	}
	int* array = new int[max_size];	
	for (int counter = 0; counter < max_size; ++counter)
	{
		file >> array[counter];			
	}
	file.close();		
	return array;									
}
bool print_to_file(int* array)
{
	std::cout << "Введите название файла для записи:\n  > ";
	std::string name = "";			
	std::cin >> name;
	std::ofstream file(name);			
	if (!file)
	{
		std::cout << "Ошибка открытия файла.\n";
		return 1;
	}
	file << max_size << std::endl;	
	for (int counter = 0; counter < max_size; ++counter)
	{
		file << array[counter] << ' ';	
	}
	file.close();		
	return 0;
}

int* create_and_save()		
{
	std::cout << "Выбирете способ инициализации массива:\n1)Ввести вручную размерность и инициализировать случайно\n2)Из файла\n  > ";
	int answer = 0;
	std::cin >> answer;
	int* array = nullptr;				
	if (answer == 1)
	{
		max_size = set_max_size();		
		if (max_size < 1)
		{
			return 0;
		}
		array = new int[max_size];		
		init_array(array);					
	}
	else if (answer == 2)
	{
		array = init_array_from_file(max_size);				 
	}
	else
	{
		std::cout << "Неверный ввод.\n";
		system("pause");
		return 0;
	}
	std::cout << "Исходный массив:\n";
	print_array(array);

	std::cout << "Сохранить исходный массив в файл?(1 - да/0 - нет)\n  > ";
	std::cin >> answer;
	if (answer)
	{
		print_to_file(array);		
	}
	return array;				
}

time_t sort_array(int* array)							
{
	int buffer = 0;					
	bool boo = 0;				
	time_t start = clock();	
	for (int distance = max_size / 2; distance >= 1;)
	{
		boo = 0;			
		//std::cout << "\n distance = " << distance << std::endl;	
		for (int counter = 0; ((counter + distance) < max_size); counter += (distance))
		{
			if (array[counter] > array[counter + distance])	
			{
				buffer = array[counter];
				array[counter] = array[counter + distance];
				array[counter + distance] = buffer;
				boo = 1;			
			}
		}
		//print_array(array, max_size);	
		if (!boo)
		{
			distance /= 2;		
		}
	}
	return (clock() - start);		
}

bool output_array_and_save(int* array, time_t time)	
{
	std::cout << "Конечный массив:\n";
	print_array(array);	
	std::cout << "Время выполнения алгоритма = " << time << "мс" << std::endl;
	bool answer = 0;
	std::cout << "Сохранить конечный массив?(1 - да/0 - нет)\n  > ";
	std::cin >> answer;
	if (answer)
	{
		return print_to_file(array);	
	}
	return 0;
}

int main()
{
	srand(time(0));				
	SetConsoleCP(1251);									
	SetConsoleOutputCP(1251);
	int* array = create_and_save();	
	if (!array)										
	{
		std::cout << "Ошибка инициализации массива. Программа завершена." << std::endl;
		system("pause");
		return 0;
	}
	output_array_and_save(array, sort_array(array));				
	delete[] array;										
	return 0;
}
