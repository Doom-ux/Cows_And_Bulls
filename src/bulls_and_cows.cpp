/*
Модуль содержит определения методов класса BullsAndCows.
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "bulls_and_cows.h"


/**
 * Функция вычисляет количество быков и коров в попытке игрока.
 * @param attempt: попытка игрока;
 * @param number: загаданное число.
 * @return: массив из количества быков и коров в попытке.
 */
int* calculate_bulls_and_cows(std::string& attempt,
	std::string& number)
{
	int bulls = 0, cows = 0; // количество быков и коров
	for (unsigned int i = 0; i < number.length(); i++)
	{
		for (unsigned int j = 0; j < number.length(); j++)
		{
			if (i == j && attempt[i] == number[j])
				bulls++;
			if (i != j && attempt[i] == number[j])
				cows++;
		}
	}
	int* result = new int[2];
	result[0] = bulls;
	result[1] = cows;
	return result;
}

/**
 * Функция выводит на экран количество быков и коров в попытке игрока.
 * @param bulls, cows: количество быков и коров в попытке игрока.
 * @return: текст, который выводится на экран.
 */
const std::string show_bulls_and_cows(const int bulls, const int cows)
{
	std::string result = "В вашем варианте ";
	// Количество коров
	if (cows == 0)
		result += "нет коров ";
	else if (cows == 1)
		result += " 1 корова ";
	else if (cows < 5)
		result += std::to_string(cows) + " коровы ";
	else
		result += std::to_string(cows) + " коров ";
	// Количество быков
	if (bulls == 0)
		result += "и нет быков.\n";
	else if (bulls == 1)
		result += "и 1 бык.\n";
	else if (bulls < 5)
		result += "и " + std::to_string(bulls) + " быка.\n";
	else
		result += "и " + std::to_string(bulls) + " быков.\n";
	std::cout << result;
	return result;
}

/**
 * Функция придумывает случайное n-значное число.
 * @param n: количество цифр в числе.
 * @return: n-значное число из неповторяющихся цифр.
 */
std::string think_random_number(const int n)
{
	srand((unsigned int)time(NULL));
	std::string number; // переменная для числа
	for (int i = 0; i < n; i++)
	{
		bool is_unique = false;
		char digit; // цифра для числа
		while (!is_unique)
		{
			// Считаем по умолчанию, что цифры digit в числе number нет
			is_unique = true;
			// Получаем случайную цифру от 0 до 9
			digit = std::to_string(rand() % 10)[0];
			// Проверяем, что в числе нет цифры digit
			for (unsigned int j = 0; j < number.length(); j++)
			{
				if (number[j] == digit)
				{
					// В числе number уже есть цифра digit
					is_unique = false;
					break;
				}
			}
		}
		// Нашли цифру, которой в числе не было, добавляем эту цифру
		number += digit;
	}
	return number;
}

/**
 * Метод анализирует изменение количества быков и коров при угадывании числа
 * компьютером.
 * @param bulls, cows: количество быков и коров в текущей попытке;
 * @param previous_bulls, previous_cows: количество быков и коров в предыдущей
 * попытке.
 * @return: true, если игру можно продолжить, иначе false.
 */
bool BullsAndCows::analyze(int bulls, int cows, int& previous_bulls,
	int& previous_cows)
{
	if (cows < 0 || bulls < 0 || cows + bulls > N)
	{
		// Игрок явно отвечает нечестно
		std::cout << "Вы меня обманываете в количестве быков и "
			"коров и играете нечестно! Я не буду с вами играть!\n";
		return false;
	}
	// Если сделана первая попытка угадать число
	if (previous_bulls == -1)
	{
		previous_bulls = bulls;
		previous_cows = cows;
		return true;
	}
	// Параметры для позиции и предыдущей цифры в этой позиции
	int position;
	int prev_digit;
	if (variant == 1)
	{
		// Если изменена цифра в позиции test_position
		position = test_position;
		prev_digit = previous_digit;
	}
	else
	{
		// Если изменена цифра в дополнительной позиции test_position_2
		position = test_position_2;
		prev_digit = previous_digit_2;
	}
	if (bulls + cows > previous_bulls + previous_cows)
	{
		// Предыдущая цифра в позиции position точно не входит
		// в загаданное число, исключаем его
		unsigned int found_pos = digits.find(prev_digit);
		if (found_pos != std::string::npos)
			digits.erase(digits.begin() + found_pos);
		if (denied_digit == "")
			denied_digit = prev_digit;
		if (variant == 1)
			pos = digits.find(attempt[position]) + 1;
		else
			pos = found_pos;
	}
	else if (bulls + cows < previous_bulls + previous_cows)
	{
		// Текущая цифра в позиции position точно не входит в
		// загаданное число, исключаем его
		unsigned int found_pos = digits.find(attempt[position]);
		if (found_pos != std::string::npos)
			digits.erase(digits.begin() + found_pos);
		if (denied_digit == "")
			denied_digit = attempt[position];
		if (variant == 1)
			pos = found_pos;
		else
			pos = digits.find(prev_digit);
	}
	else if (variant == 1)
		pos++;
	if (previous_bulls < bulls)
	{
		// Текущая цифра в позиции position точно входит в
		// загаданное число
		number[position] = attempt[position];
		previous_bulls = bulls;
		previous_cows = cows;
	}
	else if (bulls < previous_bulls)
	{
		// Предыдущая цифра в позиции position точно входит в
		// загаданное число
		number[position] = prev_digit;
		attempt[position] = prev_digit;
	}
	else
	{
		previous_bulls = bulls;
		previous_cows = cows;
	}
	variant = 1;
	return true;
}

/**
 * Метод реализует игровой процесс, когда компьютер загадывает число.
 * @return: true, если игра закончена по правилам, иначе false.
 */
bool BullsAndCows::comp_concieve_number()
{
	// Компьютер загадывает случайное число
	number = think_random_number(N);
	std::cout << "\nНовая игра!\nЯ загадал " << N << "-значное число с "
		"неповторяющимися цифрами. Отгадайте его.\n";
	// Если включен режим отладки, выводим на экран загаданное число
	if (DEBUG)
		std::cout << "(Загадано число " << number << ")\n";
	// Игрок пытается угадать число
	int attempt_number = 1; // номер попытки
	while (true)
	{
		// Читаем попытку игрока
		std::string response;
		std::cout << "Попытка №" << attempt_number <<
			". Ваш вариант (0 - завершить игру): ";
		std::cin >> response;
		if (response == "0")
			// Игрок хочет завершить игру
			return false;
		try
		{
			response = "1" + response;
			response = std::to_string(std::stoi(response, nullptr));
			response = response.substr(1);
			if (response.length() != N)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Не понял ваше число, попробуйте еще раз.\n";
			continue;
		}
		// Определяем количество быков и коров в попытке игрока
		int* bulls_and_cows = calculate_bulls_and_cows(response, number);
		// Проверяем, угадал ли игрок все цифры
		if (bulls_and_cows[0] == N)
		{
			// Игрок угадал все цифры в нужных позициях, игра закончена
			std::cout << "Я загадал число " << number << ". Вы угадали его!\n";
			break;
		}
		// Игрок не угадал число, потому готовим подсказку из количества быков
		// и коров в попытке игрока
		show_bulls_and_cows(bulls_and_cows[0], bulls_and_cows[1]);
		attempt_number++;
	}
	return true;
}

/**
 * Метод реализует игровой процесс, когда компьютер угадывает число.
 * @return: true, если игра завершена по правилам, иначе false.
 */
bool BullsAndCows::comp_guess_number()
{
	std::cout << "\nНовая игра!\nЗагадайте " << N << "-значное число с "
		"неповторяющимися цифрами.\n";
	// Включен режим отладки, поэтому нужно ввести загаданное число
	std::string real_number;
	if (DEBUG == true)
	{
		std::cout << "Введите загаданное число: ";
		std::cin >> real_number;
	}
	attempt = "****"; // попытка компьютера
	number = "****"; // угаданные цифры в нужных положениях
	// Количество быков и коров в попытке
	int bulls, cows;
	// Количество быков и коров в предыдущей попытке
	int previous_bulls = -1, previous_cows = 0;
	int attempt_number = 1; // номер попытки
	while (true)
	{
		// Компьютер придумывает число
		if (!iterate_number())
		{
			std::cout << "Кажется, вы меня обманываете в количестве быков и "
				"коров и играете нечестно! Я не буду с вами играть!\n";
			return false;
		}
		// Узнаем у игрок количество быков и коров
		std::cout << "Попытка №" << attempt_number << ". Вы загадали число " <<
			attempt << "?\n";
		if (DEBUG)
		{
			// Режим отладки. Сами вычисляем количество быков и коров и выводим
			// на экран
			int* bulls_and_cows = calculate_bulls_and_cows(attempt,
				real_number);
			bulls = bulls_and_cows[0];
			cows = bulls_and_cows[1];
			show_bulls_and_cows(bulls, cows);
		}
		else
		{
			bulls = determine_response("Количество быков (-1 - завершить игру): ");
			if (bulls == -1)
				// Игрок хочет завершить игру
				return false;
			cows = determine_response("Количество коров (-1 - завершить игру): ");
			if (cows == -1)
				// Игрок хочет завершить игру
				return false;
		}
		// Анализируем ответ игрока
		if (bulls == N)
		{
			// Компьютер угадал все цифры в нужных позициях
			std::cout << "Вы загадали число " << attempt << ". Я выиграл!\n";
			return true;
		}
		if (!analyze(bulls, cows, previous_bulls, previous_cows))
			return false;
		attempt_number++;
	}
	return true;
}

/**
 * Метод определяет числовой ответ игрока.
 * @param question: вопрос, на который игрок должен дать числовой ответ.
 * @return: ответ игрока.
 */
int BullsAndCows::determine_response(const char* question)
{
	while (true)
	{
		std::cout << question;
		std::string response;
		std::cin >> response;
		try
		{
			int int_response = std::stoi(response, nullptr);
			return int_response;
		}
		catch (...)
		{
			continue;
		}
	}
}

/**
 * Метод определяет роли компьютера и игрока в игре.
 * @return: STOP_GAME, если игру нужно завершить, COMP_CONCIVE, если компьютер
 * загадывает число, COMP_GUESS, если компьютер отгадывает число.
 */
char BullsAndCows::determine_roles()
{
	const char QUESTION[] = "Вы будете отгадывать или загадывать число (0 - "
		"завершить игру, 1 - отгадывать, 2 - загадывать)?\nВаш выбор: ";
	const std::vector<char> ANSWERS = { '0', '1', '2' };
	const char RESPONSE = select_response(QUESTION, ANSWERS);
	if (RESPONSE == '0')
		return STOP_GAME;
	else if (RESPONSE == '1')
		return COMP_CONCIEVE;
	return COMP_GUESS;
}

/**
 * Метод подбирает число-попытку для компьютера (в игре, когда компьютер
 * должен отгадать число, загаданное игроком).
 * @return: true, если удалось подобрать новую попытку для компьютера,
 * иначе false.
 */
bool BullsAndCows::iterate_number()
{
	if (attempt == "****")
	{
		// Делается первая попытка угадать число
		attempt = think_random_number(N);
		test_position = 0;
		variant = 1;
		return true;
	}
	// Ищем в числе позицию, для которой пока не определена цифра
	while (test_position < N && number[test_position] != '*')
	{
		test_position++;
		pos = 0;
		variant = 1;
	}
	if (test_position >= N)
		// Если мы пробежались по всем позициям числа и до сих пор не отгадали
		// число, то игрок нас обманывал в своих ответах
		return false;
	// Сначала пробуем изменить цифру в позиции test_position
	if (variant == 1)
	{
		// Перебираем цифры из доступных в digits
		while (pos < digits.length() &&
			attempt.find(digits[pos]) != std::string::npos &&
			number.find(digits[pos]) != std::string::npos)
			pos++;
		if (pos < digits.length() &&
			attempt.find(digits[pos]) != std::string::npos)
			variant = 2;
		else if (pos < digits.length())
		{
			previous_digit = attempt[test_position];
			attempt[test_position] = digits[pos];
			return true;
		}
		else
			// Не удалось подобрать новую попытку, игрок нас явно обманывает
			return false;
	}
	// Не удалось изменить цифру в позиции test_position, будем изменять цифру
	// в позиции test_position_2
	if (variant == 2)
	{
		test_position_2 = attempt.find(this->digits[pos]);
		std::string digits;
		if (denied_digit != "" && this->digits.length() == N)
			digits = denied_digit + this->digits;
		else
			digits = this->digits;
		for (auto d : digits)
		{
			if (attempt.find(d) == std::string::npos)
			{
				previous_digit_2 = attempt[test_position_2];
				attempt[test_position_2] = d;
				return true;
			}
		}
		// Не удалось подобрать новую попытку
		return false;
	}
	return true;
}

/**
 * Метод определяет выбор игрока из заданного набора ответов.
 * @param question: вопрос, на который пользователь должен ответить;
 * @param answers: вектор из вариантов ответов.
 * @return: ответ пользователя - один из элементов массива answers.
 */
const char BullsAndCows::select_response(const char* question,
	const std::vector<char>& answers)
{
	while (true)
	{
		std::cout << question;
		std::string response;
		std::cin >> response;
		for (auto answer : answers)
		{
			if (response[0] == answer)
				return answer;
		}
	}
}

/**
 * Метод возвращает значения атрибутов класса в исходные состояния.
 */
void BullsAndCows::set_to_default()
{
	attempt = "****"; // попытка отгадать число
	denied_digit = ""; // одна из цифр, которой точно нет в числе
	digits = "0123456789"; // цифры, которые могут быть в числе
	number = "****"; // загаданное число
	pos = 0; // индекс цифры в массиве digits
	previous_digit = ' ';
	previous_digit_2 = ' ';
	test_position = 0; // позиция для изменения цифры в числе
	test_position_2 = 0; // позиция для изменения дополнительной цифры в числе
	variant = 1;
}

/**
 * Метод выводит на экран правила игры.
 */
void BullsAndCows::show_rules()
{
	std::cout << "Правила игры 'Быки и коровы':\n" <<
		"Игрок играет с Компьютером. Игрок выбирает свою роль в игре:\n"
		"отгадывать или загадывать число.\n" <<
		"Если Игрок выбрал отгадывать число, то Компьютер загадывает 4-значное\n"
		"число с неповторяющимися цифрами. Игрок пытается отгадать число, вводя\n"
		"4-значные числа. Компьютер сообщает в ответ, сколько цифр угадано без\n"
		"совпадения с их позициями в тайном числе (количество 'коров') и сколько\n"
		"угадано вплоть до позиции в тайном числе (количество 'быков').\n" <<
		"Например, задумано тайное число 3219.\n"
		"Попытка: 2310.\n"
		"Результат: две 'коровы' (две цифры: 2 и 3 — угаданы на неверных позициях)\n"
		"и один 'бык' (одна цифра 1 угадана вплоть до позиции).\n" <<
		"Если Игрок загадывает число, то Копмьютер пытается угадать число, а Игрок\n"
		"должен сообщать количество 'коров' и 'быков'.\n\n";
}

/**
 * Метод запускает игру.
 */
bool BullsAndCows::start_game()
{
	// Выводится приветствие и правила игры
	std::cout << "\nДобро пожаловать в игру 'Быки и коровы'!\n\n";
	show_rules();
	while (true)
	{
		// Возвращаем атрибуты в исходные состояния
		set_to_default();
		// Определяем роли компьютера и игрока
		switch (determine_roles())
		{
		case COMP_CONCIEVE:
		{
			// Компьютер загадывает число
			if (!comp_concieve_number())
			{
				// Игрок хочет завершить игру
				std::cout << "Конец игры.\n";
				return false;
			}
			break;
		}
		case COMP_GUESS:
		{
			// Компьютер отгадывает число
			if (!comp_guess_number())
			{
				// Игрок хочет завершить игру
				std::cout << "Конец игры.\n";
				return false;
			}
			break;
		}
		case STOP_GAME:
		{
			// Игрок хочет завершить игру
			std::cout << "Конец игры.\n";
			return false;
		}
		}
		// Начать игру сначала или завершить игру?
		if (stop_game() == STOP_GAME)
		{
			// Игрок хочет завершить игру
			std::cout << "Конец игры.\n";
			return false;
		}
	}
	return true;
}

/**
 * Метод определяет, нужно ли завершить игру.
 * @return: STOP_GAME, если игру нужно завершить, иначе START_GAME.
 */
const char BullsAndCows::stop_game()
{
	const char QUESTION[] = "\nЗавершить или продолжить игру (0 - завершить, "
		"1 - продолжить)?\nВаш выбор: ";
	const std::vector<char> ANSWERS = { '0', '1' };
	const char RESPONSE = select_response(QUESTION, ANSWERS);
	if (RESPONSE == '0')
		// Игрок хочет завершить игру
		return STOP_GAME;
	// Игрок хочет продолжит игру
	return START_GAME;
}