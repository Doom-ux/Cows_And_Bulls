/*
������ �������� ����������� ������ BullsAndCows, ������� ��������� ����
"���� � ������".
*/

#pragma once
#ifndef BULLS_AND_COWS_H
#define BULLS_AND_COWS_H

#include <vector>

/**
 * ����� ��� ���� "���� � ������".
 */
class BullsAndCows
{
public:
	// ������:
	// ����� ��������� ���������� ����� � ����� � ������� ������
	int* calculate_bulls_and_cows(std::string&, std::string&);
	// ����� ���������� ���� ���������� � ������ � ����
	char determine_roles();
	// ����� ��������� ����
	bool start_game();
	// ����� ����������� ��������� N-������� �����
	std::string think_random_number();

private:
	// ���������� ��������
	const bool DEBUG = true; // true, �� ����� �������
	static const char STOP_GAME = '0';
	static const char START_GAME = '1';
	static const char COMP_CONCIEVE = '2';
	static const char COMP_GUESS = '3';
	static const int N = 4; // ���������� ���� � ������������ �����
	// ��������:
	std::string attempt; // ������� ���������� �������� �����
	std::string denied_digit; // ���� �� ����, ������� ����� ��� � �����
	std::string digits; // �����, ������� ����� ���� � �����
	std::string number; // ���������� �����
	int pos;
	char previous_digit; // �����, �������������� ����� � test_position
	char previous_digit_2; // �����, �������������� ����� � test_position_2
	int test_position; // ������� ��� ��������� ����� � �����
	int test_position_2; // ������� ��� ��������� �������������� ����� � �����
	int variant;
	// ������:
	// ����� ����������� ��������� ���������� ����� � ����� ��� ����������
	bool analyze(int, int, int&, int&);
	// ����� ��������� ������� �������, ����� ��������� ���������� �����
	bool comp_concieve_number();
	// ����� ��������� ������� �������, ����� ��������� ���������� �����
	bool comp_guess_number();
	// ����� ���������� �������� ����� ������
	int determine_response(const char*);
	// ����� ��������� �����-������� ��� ����������
	bool iterate_number();
	// ����� ���������� ����� ������ �� ��������� ������ �������
	const char select_response(const char*, const std::vector<char>&);
	// ����� ���������� �������� ��������� � �������� ���������
	void set_to_default();
	// ����� ������� �� ����� ���������� ����� � ����� � ������� ������
	void show_bulls_and_cows(const int, const int);
	// ����� ������� �� ����� ������� ����
	void show_rules();
	// ����� ����������, ����� �� ��������� ����
	const char stop_game();
};

#endif // !BULLS_AND_COWS_H
