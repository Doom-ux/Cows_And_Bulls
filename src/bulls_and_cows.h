/*
Модуль содержит определение класса BullsAndCows, который реализует игру
"Быки и коровы".
*/

#pragma once
#ifndef BULLS_AND_COWS_H
#define BULLS_AND_COWS_H

#include <vector>

// Функция вычисляет количество коров и быков в попытке игрока
int* calculate_bulls_and_cows(std::string&, std::string&);
// Функция выводит на экран количество быков и коров в попытке игрока
const std::string show_bulls_and_cows(const int, const int);
// Функция придумывает случайное N-значное число
std::string think_random_number(const int);

/**
 * Класс для игры "Быки и коровы".
 */
class BullsAndCows
{
public:
	// Методы:
	// Метод определяет роли компьютера и игрока в игре
	char determine_roles();
	// Метод запускает игру
	bool start_game();

private:
	// Постоянные значения
	const bool DEBUG = true; // true, то режим отладки
	static const char STOP_GAME = '0';
	static const char START_GAME = '1';
	static const char COMP_CONCIEVE = '2';
	static const char COMP_GUESS = '3';
	static const int N = 4; // количество цифр в загадываемом числе
	// Атрибуты:
	std::string attempt; // попытка компьютера отгадать число
	std::string denied_digit; // одна из цифр, которой точно нет в числе
	std::string digits; // цифры, которые могут быть в числе
	std::string number; // загаданное число
	unsigned int pos;
	char previous_digit; // цифра, испытывавшаяся ранее в test_position
	char previous_digit_2; // цифра, испытывавшаяся ранее в test_position_2
	int test_position; // позиция для изменения цифры в числе
	int test_position_2; // позиция для изменения дополнительной цифры в числе
	int variant;
	// Методы:
	// Метод анализирует изменение количества быков и коров при угадывании
	bool analyze(int, int, int&, int&);
	// Метод реализует игровой процесс, когда компьютер загадывает число
	bool comp_concieve_number();
	// Метод реализует игровой процесс, когда компьютер отгадывает число
	bool comp_guess_number();
	// Метод определяет числовой ответ игрока
	int determine_response(const char*);
	// Метод подбирает число-попытку для компьютера
	bool iterate_number();
	// Метод определяет выбор игрока из заданного набора ответов
	const char select_response(const char*, const std::vector<char>&);
	// Метод возвращает значения атрибутов в исходные состояния
	void set_to_default();
	// Метод выводит на экран правила игры
	void show_rules();
	// Метод определяет, нужно ли завершить игру
	const char stop_game();
};

#endif // !BULLS_AND_COWS_H
