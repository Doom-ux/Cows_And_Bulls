/*
������ �������� ����������� ������� ������ BullsAndCows.
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "bulls_and_cows.h"


/**
 * ����� ����������� ��������� ���������� ����� � ����� ��� ���������� �����
 * �����������.
 * @param bulls, cows: ���������� ����� � ����� � ������� �������;
 * @param previous_bulls, previous_cows: ���������� ����� � ����� � ����������
 * �������.
 * @return: true, ���� ���� ����� ����������, ����� false.
 */
bool BullsAndCows::analyze(int bulls, int cows, int& previous_bulls,
	int& previous_cows)
{
	if (cows < 0 || bulls < 0 || cows + bulls > N)
	{
		// ����� ���� �������� ��������
		std::cout << "�� ���� ����������� � ���������� ����� � "
			"����� � ������� ��������! � �� ���� � ���� ������!\n";
		return false;
	}
	// ���� ������� ������ ������� ������� �����
	if (previous_bulls == -1)
	{
		previous_bulls = bulls;
		previous_cows = cows;
		return true;
	}
	// ��������� ��� ������� � ���������� ����� � ���� �������
	int position;
	int prev_digit;
	if (variant == 1)
	{
		// ���� �������� ����� � ������� test_position
		position = test_position;
		prev_digit = previous_digit;
	}
	else
	{
		// ���� �������� ����� � �������������� ������� test_position_2
		position = test_position_2;
		prev_digit = previous_digit_2;
	}
	if (bulls + cows > previous_bulls + previous_cows)
	{
		// ���������� ����� � ������� position ����� �� ������
		// � ���������� �����, ��������� ���
		int found_pos = digits.find(prev_digit);
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
		// ������� ����� � ������� position ����� �� ������ �
		// ���������� �����, ��������� ���
		int found_pos = digits.find(attempt[position]);
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
		// ������� ����� � ������� position ����� ������ �
		// ���������� �����
		number[position] = attempt[position];
		previous_bulls = bulls;
		previous_cows = cows;
	}
	else if (bulls < previous_bulls)
	{
		// ���������� ����� � ������� position ����� ������ �
		// ���������� �����
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
 * ����� ��������� ���������� ����� � ����� � ������� ������.
 * @param attempt: ������� ������;
 * @param number: ���������� �����.
 * @return: ������ �� ���������� ����� � ����� � �������.
 */
int* BullsAndCows::calculate_bulls_and_cows(std::string& attempt,
	std::string& number)
{
	int bulls = 0, cows = 0; // ���������� ����� � �����
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j && attempt[i] == number[j])
				bulls++;
			if (i != j && attempt[i] == number[j])
				cows++;
		}
	}
	int result[2] = { bulls, cows };
	return result;
}

/**
 * ����� ��������� ������� �������, ����� ��������� ���������� �����.
 * @return: true, ���� ���� ��������� �� ��������, ����� false.
 */
bool BullsAndCows::comp_concieve_number()
{
	// ��������� ���������� ��������� �����
	number = think_random_number();
	std::cout << "\n����� ����!\n� ������� " << N << "-������� ����� � "
		"���������������� �������. ��������� ���.\n";
	// ���� ������� ����� �������, ������� �� ����� ���������� �����
	if (DEBUG)
		std::cout << "(�������� ����� " << number << ")\n";
	// ����� �������� ������� �����
	int attempt_number = 1; // ����� �������
	while (true)
	{
		// ������ ������� ������
		std::string response;
		std::cout << "������� �" << attempt_number <<
			". ��� ������� (0 - ��������� ����): ";
		std::cin >> response;
		if (response == "0")
			// ����� ����� ��������� ����
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
			std::cout << "�� ����� ���� �����, ���������� ��� ���.\n";
			continue;
		}
		// ���������� ���������� ����� � ����� � ������� ������
		int* bulls_and_cows = calculate_bulls_and_cows(response, number);
		// ���������, ������ �� ����� ��� �����
		if (bulls_and_cows[0] == N)
		{
			// ����� ������ ��� ����� � ������ ��������, ���� ���������
			std::cout << "� ������� ����� " << number << ". �� ������� ���!\n";
			break;
		}
		// ����� �� ������ �����, ������ ������� ��������� �� ���������� �����
		// � ����� � ������� ������
		show_bulls_and_cows(bulls_and_cows[0], bulls_and_cows[1]);
		attempt_number++;
	}
	return true;
}

/**
 * ����� ��������� ������� �������, ����� ��������� ��������� �����.
 * @return: true, ���� ���� ��������� �� ��������, ����� false.
 */
bool BullsAndCows::comp_guess_number()
{
	std::cout << "\n����� ����!\n��������� " << N << "-������� ����� � "
		"���������������� �������.\n";
	// ������� ����� �������, ������� ����� ������ ���������� �����
	std::string real_number;
	if (DEBUG == true)
	{
		std::cout << "������� ���������� �����: ";
		std::cin >> real_number;
	}
	attempt = "****"; // ������� ����������
	number = "****"; // ��������� ����� � ������ ����������
	// ���������� ����� � ����� � �������
	int bulls, cows;
	// ���������� ����� � ����� � ���������� �������
	int previous_bulls = -1, previous_cows = 0;
	int attempt_number = 1; // ����� �������
	while (true)
	{
		// ��������� ����������� �����
		if (!iterate_number())
		{
			std::cout << "�������, �� ���� ����������� � ���������� ����� � "
				"����� � ������� ��������! � �� ���� � ���� ������!\n";
			return false;
		}
		// ������ � ����� ���������� ����� � �����
		std::cout << "������� �" << attempt_number << ". �� �������� ����� " <<
			attempt << "?\n";
		if (DEBUG)
		{
			// ����� �������. ���� ��������� ���������� ����� � ����� � �������
			// �� �����
			int* bulls_and_cows = calculate_bulls_and_cows(attempt,
				real_number);
			bulls = bulls_and_cows[0];
			cows = bulls_and_cows[1];
			show_bulls_and_cows(bulls, cows);
		}
		else
		{
			bulls = determine_response("���������� ����� (-1 - ��������� ����): ");
			if (bulls == -1)
				// ����� ����� ��������� ����
				return false;
			cows = determine_response("���������� ����� (-1 - ��������� ����): ");
			if (cows == -1)
				// ����� ����� ��������� ����
				return false;
		}
		// ����������� ����� ������
		if (bulls == N)
		{
			// ��������� ������ ��� ����� � ������ ��������
			std::cout << "�� �������� ����� " << attempt << ". � �������!\n";
			return true;
		}
		if (!analyze(bulls, cows, previous_bulls, previous_cows))
			return false;
		attempt_number++;
	}
	return true;
}

/**
 * ����� ���������� �������� ����� ������.
 * @param question: ������, �� ������� ����� ������ ���� �������� �����.
 * @return: ����� ������.
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
 * ����� ���������� ���� ���������� � ������ � ����.
 * @return: STOP_GAME, ���� ���� ����� ���������, COMP_CONCIVE, ���� ���������
 * ���������� �����, COMP_GUESS, ���� ��������� ���������� �����.
 */
char BullsAndCows::determine_roles()
{
	const char QUESTION[] = "�� ������ ���������� ��� ���������� ����� (0 - "
		"��������� ����, 1 - ����������, 2 - ����������)?\n��� �����: ";
	const std::vector<char> ANSWERS = { '0', '1', '2' };
	const char RESPONSE = select_response(QUESTION, ANSWERS);
	if (RESPONSE == '0')
		return STOP_GAME;
	else if (RESPONSE == '1')
		return COMP_CONCIEVE;
	return COMP_GUESS;
}

/**
 * ����� ��������� �����-������� ��� ���������� (� ����, ����� ���������
 * ������ �������� �����, ���������� �������).
 * @return: true, ���� ������� ��������� ����� ������� ��� ����������,
 * ����� false.
 */
bool BullsAndCows::iterate_number()
{
	if (attempt == "****")
	{
		// �������� ������ ������� ������� �����
		attempt = think_random_number();
		test_position = 0;
		variant = 1;
		return true;
	}
	// ���� � ����� �������, ��� ������� ���� �� ���������� �����
	while (test_position < N && number[test_position] != '*')
	{
		test_position++;
		pos = 0;
		variant = 1;
	}
	if (test_position >= N)
		// ���� �� ����������� �� ���� �������� ����� � �� ��� ��� �� ��������
		// �����, �� ����� ��� ��������� � ����� �������
		return false;
	// ������� ������� �������� ����� � ������� test_position
	if (variant == 1)
	{
		// ���������� ����� �� ��������� � digits
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
			// �� ������� ��������� ����� �������, ����� ��� ���� ����������
			return false;
	}
	// �� ������� �������� ����� � ������� test_position, ����� �������� �����
	// � ������� test_position_2
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
		// �� ������� ��������� ����� �������
		return false;
	}
}

/**
 * ����� ���������� ����� ������ �� ��������� ������ �������.
 * @param question: ������, �� ������� ������������ ������ ��������;
 * @param answers: ������ �� ��������� �������.
 * @return: ����� ������������ - ���� �� ��������� ������� answers.
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
 * ����� ���������� �������� ��������� ������ � �������� ���������.
 */
void BullsAndCows::set_to_default()
{
	attempt = "****"; // ������� �������� �����
	denied_digit = ""; // ���� �� ����, ������� ����� ��� � �����
	digits = "0123456789"; // �����, ������� ����� ���� � �����
	number = "****"; // ���������� �����
	pos = 0; // ������ ����� � ������� digits
	previous_digit = ' ';
	previous_digit_2 = ' ';
	test_position = 0; // ������� ��� ��������� ����� � �����
	test_position_2 = 0; // ������� ��� ��������� �������������� ����� � �����
	variant = 1;
}

/**
 * ����� ������� �� ����� ���������� ����� � ����� � ������� ������.
 * @param bulls, cows: ���������� ����� � ����� � ������� ������.
 */
void BullsAndCows::show_bulls_and_cows(const int bulls, const int cows)
{
	std::string result = "� ����� �������� ";
	// ���������� �����
	if (cows == 0)
		result += "��� ����� ";
	else if (cows == 1)
		result += " 1 ������ ";
	else if (cows < 5)
		result += std::to_string(cows) + " ������ ";
	else
		result += std::to_string(cows) + " ����� ";
	// ���������� �����
	if (bulls == 0)
		result += "� ��� �����.\n";
	else if (bulls == 1)
		result += "� 1 ���.\n";
	else if (bulls < 5)
		result += "� " + std::to_string(bulls) + " ����.\n";
	else
		result += "� " + std::to_string(bulls) + " �����.\n";
	std::cout << result;
}

/**
 * ����� ������� �� ����� ������� ����.
 */
void BullsAndCows::show_rules()
{
	std::cout << "������� ���� '���� � ������':\n" <<
		"����� ������ � �����������. ����� �������� ���� ���� � ����:\n"
		"���������� ��� ���������� �����.\n" <<
		"���� ����� ������ ���������� �����, �� ��������� ���������� 4-�������\n"
		"����� � ���������������� �������. ����� �������� �������� �����, �����\n"
		"4-������� �����. ��������� �������� � �����, ������� ���� ������� ���\n"
		"���������� � �� ��������� � ������ ����� (���������� '�����') � �������\n"
		"������� ������ �� ������� � ������ ����� (���������� '�����').\n" <<
		"��������, �������� ������ ����� 3219.\n"
		"�������: 2310.\n"
		"���������: ��� '������' (��� �����: 2 � 3 � ������� �� �������� ��������)\n"
		"� ���� '���' (���� ����� 1 ������� ������ �� �������).\n" <<
		"���� ����� ���������� �����, �� ��������� �������� ������� �����, � �����\n"
		"������ �������� ���������� '�����' � '�����'.\n\n";
}

/**
 * ����� ��������� ����.
 */
bool BullsAndCows::start_game()
{
	// ��������� ����������� � ������� ����
	std::cout << "\n����� ���������� � ���� '���� � ������'!\n\n";
	show_rules();
	while (true)
	{
		// ���������� �������� � �������� ���������
		set_to_default();
		// ���������� ���� ���������� � ������
		switch (determine_roles())
		{
		case COMP_CONCIEVE:
		{
			// ��������� ���������� �����
			if (!comp_concieve_number())
			{
				// ����� ����� ��������� ����
				std::cout << "����� ����.\n";
				return false;
			}
			break;
		}
		case COMP_GUESS:
		{
			// ��������� ���������� �����
			if (!comp_guess_number())
			{
				// ����� ����� ��������� ����
				std::cout << "����� ����.\n";
				return false;
			}
			break;
		}
		case STOP_GAME:
		{
			// ����� ����� ��������� ����
			std::cout << "����� ����.\n";
			return false;
		}
		}
		// ������ ���� ������� ��� ��������� ����?
		if (stop_game() == STOP_GAME)
		{
			// ����� ����� ��������� ����
			std::cout << "����� ����.\n";
			return false;
		}
	}
	return true;
}

/**
 * ����� ����������, ����� �� ��������� ����.
 * @return: STOP_GAME, ���� ���� ����� ���������, ����� START_GAME.
 */
const char BullsAndCows::stop_game()
{
	const char QUESTION[] = "\n��������� ��� ���������� ���� (0 - ���������, "
		"1 - ����������)?\n��� �����: ";
	const std::vector<char> ANSWERS = { '0', '1' };
	const char RESPONSE = select_response(QUESTION, ANSWERS);
	if (RESPONSE == '0')
		// ����� ����� ��������� ����
		return STOP_GAME;
	// ����� ����� ��������� ����
	return START_GAME;
}

/**
 * ����� ����������� ��������� N-������� �����.
 * @return: N-������� ����� �� ��������������� ����.
 */
std::string BullsAndCows::think_random_number()
{
	srand(time(NULL));
	std::string number; // ���������� ��� �����
	for (int i = 0; i < N; i++)
	{
		bool is_unique = false;
		char digit; // ����� ��� �����
		while (!is_unique)
		{
			// ������� �� ���������, ��� ����� digit � ����� number ���
			is_unique = true;
			// �������� ��������� ����� �� 0 �� 9
			digit = std::to_string(rand() % 10)[0];
			// ���������, ��� � ����� ��� ����� digit
			for (int j = 0; j < number.length(); j++)
			{
				if (number[j] == digit)
				{
					// � ����� number ��� ���� ����� digit
					is_unique = false;
					break;
				}
			}
		}
		// ����� �����, ������� � ����� �� ����, ��������� ��� �����
		number += digit;
	}
	return number;
}