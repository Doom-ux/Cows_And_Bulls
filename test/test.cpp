/*
В модуле определены тесты для игры "Быки и коровы".
*/

#include "ctest.h"
#include <string>
#include "../src/bulls_and_cows.h"


CTEST(suite1, test1)
{
	// Тест на количество цифр в генерируемом случайном числе
	const int N = 4;
	const std::string number = think_random_number(N);
	ASSERT_EQUAL(N, number.length());
}

CTEST(suite1, test2)
{
	// Тест на уникальность всех цифр в генерируемом случайном числе
	const int N = 4;
	const std::string number = think_random_number(N);
	// Определяем количество уникальных цифр в number
	int coincidence = 0;
	for (unsigned int i = 0; i < number.length(); i++)
	{
		for (unsigned int j = 0; j < number.length(); j++)
		{
			if (i != j && number[i] == number[j])
				coincidence++;
		}
	}
	ASSERT_EQAUL(0, coincidence);
}

CTEST(suite2, test1)
{
	// Тест на правильность вычисления быков
	std::string attempt = "8742";
	std::string number = "6732";
	int* bulls_and_cows = calculate_bulls_and_cows(attempt, number);
	int bulls = bulls_and_cows[0];
	ASSERT_EQUAL(2, bulls);
}

CTEST(suite2, test2)
{
	// Тест на правильность вычисления коров
	std::string attempt = "8742";
	std::string number = "6732";
	int* bulls_and_cows = calculate_bulls_and_cows(attempt, number);
	int cows = bulls_and_cows[1];
	ASSERT_EQUAL(0, cows);
}

CTEST(suite3, test1)
{
	// Тест на правильность сообщения о количестве коров и быков
	const std::string result = show_bulls_and_cows(0, 2);
	const std::string expected = "В вашем варианте 2 коровы и нет быков.\n";
	ASSERT_STR(expected.c_str(), result.c_str());
}
