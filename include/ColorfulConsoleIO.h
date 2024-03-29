// ColorfulConsole.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <string>


//#define OS_TYPE_WINDOWS_CC
//#define OS_TYPE_LINUX_CC

#ifdef OS_TYPE_WINDOWS_CC
       #include <Windows.h>
#endif // OS_TYPE_WINDOWS_CC





enum class ConsoleColor
{
	Green, Red, Blue, White, Black,Yellow,Purple,Gray,Cyan,None,
	GreenIntensity, RedIntensity, BlueIntensity, WhiteIntensity, BlackIntensity, YellowIntensity, PurpleIntensity, GrayIntensity,CyanIntensity
};

enum class ConsoleBackgroundColor
{
	Green, Red, Blue, White, Black, Yellow, Purple, Gray, Cyan,None,
	GreenIntensity, RedIntensity, BlueIntensity, WhiteIntensity, BlackIntensity, YellowIntensity, PurpleIntensity, GrayIntensity
};

std::wostream& operator<< (std::wostream& os, ConsoleColor  data)
{
	switch (data)
	{
	case ConsoleColor::Green: {

#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
#else 
		std::wcout << L"\033[32m";
#endif



	}break;
	case ConsoleColor::Black: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0);
#else 
		std::wcout << L"\033[30m";
#endif

	}break;
	case ConsoleColor::Blue: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
#else 
		std::wcout << L"\033[34m";
#endif

	}break;
	case ConsoleColor::Gray: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
#else 
		std::wcout << L"\033[37m";
#endif

	}break;
	case ConsoleColor::Purple: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED);
#else 
		std::wcout << L"\033[35m";
#endif

	}break;
	case ConsoleColor::Red: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
#else 
		std::wcout << L"\033[31m";
#endif

	}break;
	case ConsoleColor::White: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
#else 
		std::wcout << L"\033[37m";
#endif

	}break;
	case ConsoleColor::Cyan: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
#else 
		std::wcout << L"\033[36m";
#endif

	}break;
	case ConsoleColor::Yellow: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
#else 
		std::wcout << L"\033[33m";
#endif

	}break;
	case ConsoleColor::None: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
#else 
		std::wcout << L"\033[0m";
#endif

	}break;

	case ConsoleColor::GreenIntensity: {

#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[32m;1m";
#endif



	}break;
	case ConsoleColor::BlackIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0);
#else 
		std::wcout << L"\033[30m;1m";
#endif

	}break;
	case ConsoleColor::BlueIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[34m;1m";
#endif

	}break;
	case ConsoleColor::GrayIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[37m;1m";
#endif

	}break;
	case ConsoleColor::PurpleIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[35m;1m";
#endif

	}break;
	case ConsoleColor::RedIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[31m;1m";
#endif

	}break;
	case ConsoleColor::WhiteIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[37m;1m";
#endif

	}break;
	case ConsoleColor::YellowIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[33m;1m";
#endif

	}break;
	case ConsoleColor::CyanIntensity: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#else 
		std::wcout << L"\033[36m;1m";
#endif

	}break;

	default:
		break;
	}

	return os;
}

std::wostream& operator<< (std::wostream& os, ConsoleBackgroundColor  data)
{
	switch (data)
	{
	case ConsoleBackgroundColor::Green: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_GREEN);
#else 
		std::wcout << L"\033[42m";
#endif

	}break;
	case ConsoleBackgroundColor::Black: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0);
#else 
		std::wcout << L"\033[40m";
#endif

	}break;
	case ConsoleBackgroundColor::Blue: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_BLUE);
#else 
		std::wcout << L"\033[44m";
#endif

	}break;
	case ConsoleBackgroundColor::Gray: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0);
#else 
		std::wcout << L"\033[40m";
#endif

	}break;
	case ConsoleBackgroundColor::Purple: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE);
#else 
		std::wcout << L"\033[45m";
#endif

	}break;
	case ConsoleBackgroundColor::Red: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_RED);
#else 
		std::wcout << L"\033[41m";
#endif

	}break;
	case ConsoleBackgroundColor::White: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
#else 
		std::wcout << L"\033[47m";
#endif

	}break;
	case ConsoleBackgroundColor::Yellow: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN);
#else 
		std::wcout << L"\033[43m";
#endif

	}break;
	case ConsoleBackgroundColor::Cyan: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, BACKGROUND_BLUE | BACKGROUND_GREEN);
#else 
		std::wcout << L"\033[46m";
#endif

	}break;
	case ConsoleBackgroundColor::None: {
#ifdef OS_TYPE_WINDOWS_CC
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 0);
#else 
		std::wcout << L"\033[40m";
#endif

	}break;
	default:
		break;
	}

	return os;
}


