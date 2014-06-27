#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>


#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4996)


// color상수 지정 
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 

#define HIDDEN 10
#define TWINKLE 11

int isLeapYear(int);                // 윤년 검사 함수
int dayOfWeek(int, int, int);       // 요일 반환 함수
static int daysOfMonth(int, int);   // 일수 반환 함수

int currentTime();
int currentYear();
int currentMonth();
int currentDay();

void renderCalendar(int, int);

void traceTextColor(int, int, int);

void clear();

void textColor(int);
void textColor(int, int);

void gotoXY(int, int);

int main(void) {
	char input;

	int
		year = currentYear(),
		month = currentMonth();

	renderCalendar(year, month);

	while ((input = getch()) != EOF) {
		system("cls");

		switch (input) {
		case 'w':
		case 'W':
			year += 1;
			break;
		case 'a':
		case 'A':
			month -= 1;
			break;
		case 's':
		case 'S':
			year -= 1;
			break;
		case 'd':
		case 'D':
			month += 1;
		default:
			break;
		}

		if (month < 1) {
			month = 12;
			year -= 1;
		}

		if (month > 12) {
			month = 1;
			year += 1;
		}

		if (year < 1700) {
			year = 1700;
		}

		renderCalendar(year, month);
	}

	return 0;
}

inline int isLeapYear(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

void clear() {
	int i;

	gotoXY(0, 0);

	for (i = 0; i < 100; i++) {
		printf("%*s", 100, " ");
	}
}

static int daysOfMonth(int year, int month) {
	int daysOfNormalYearMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	month -= 1;

	if (month == 1) {   // 2월달일때만 윤년 검사
		if (isLeapYear(year)) {
			return daysOfNormalYearMonth[month] + 1;
		}
	}

	return daysOfNormalYearMonth[month];
}

int dayOfWeek(int year, int month, int day) {
	int frontYear, backYear;

	if (month <= 2) {
		month += 10;
		year -= 1;
	}

	frontYear = year / 100;
	backYear = year % 100;

	return ((21 * frontYear / 4) + (5 * backYear / 4) + (26 * (month + 1) / 10) + day - 1) % 7;
}

void renderCalendar(int year, int month) {
	char *dayName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	int
		i,

		marginRepeatCount = dayOfWeek(year, month, 1),

		totalDays = daysOfMonth(year, month),

		totalLoops = totalDays + marginRepeatCount,

		day = 1;

	textColor(LIGHTRED);

	gotoXY(0, 0);

	printf("\n   이젠 숫자만 늘어간다.... %d-%02d\n\n", year, month);

	for (i = 0; i < 7; i++) {
		if (i % 7 == 0) {
			textColor(LIGHTRED);
		}
		else if (i % 6 == 0) {
			textColor(LIGHTBLUE);
		}
		else {
			textColor(LIGHTCYAN);
		}

		printf("%5s ", dayName[i]);
	}

	for (i = 0; i < totalLoops; i++) {

		if (i % 7 == 0) {
			printf("\n\n");
		}

		if (marginRepeatCount > 0) {
			printf("%6s", " ");

			marginRepeatCount--;

			continue;
		}
		else {
			traceTextColor(year, month, day);
			printf(" %4d ", day++);
		}
	}
}

void traceTextColor(int year, int month, int day) {
	int n = dayOfWeek(year, month, day);

	if (n == 0) {
		textColor(LIGHTRED);
	}
	else if (n == 6) {
		textColor(LIGHTBLUE);
	}
	else if (year == currentYear() && month == currentMonth() && day == currentDay()) {
		textColor(LIGHTBLUE, YELLOW);
	}
	else if (month == 8 && day == 26) {
		textColor(LIGHTBLUE, WHITE);
	}
	else {
		textColor(LIGHTCYAN);
	}
}


void textColor(int foreground) { // foreground: 글자색
	int color = foreground + BLACK * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void textColor(int foreground, int background) { // foreground: 글자색, background: 배경색
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoXY(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int currentTime() {
	// 중복되는 부분을 처리하려 했으나 생략함
	return 0;
}

int currentYear() {
	time_t clock;
	struct tm *t;

	clock = time(NULL);

	t = localtime(&clock);

	return t->tm_year + 1900;
}

int currentMonth() {
	time_t clock;
	struct tm *t;

	clock = time(NULL);

	t = localtime(&clock);

	return t->tm_mon + 1;
}

int currentDay() {
	time_t clock;
	struct tm *t;

	clock = time(NULL);

	t = localtime(&clock);

	return t->tm_mday;
}