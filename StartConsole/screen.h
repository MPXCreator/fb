#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "user.h"
#include "resources.h"
#include "lang.h"

class screen
{
private:
	std::string header;
public:
	void clear();
	int wait();
	void print_header();
	void construction();
	void print_image();
	void print_image(int percent);
	void print_info(user* usr);
	int choose(std::string intro, std::vector<std::string> option, std::string ask, user* usr = NULL);
	std::pair<std::string, std::string> login(bool retry);
	std::pair<std::string, std::string> signup(bool retry);
	void game_start();
	void view_history(user* usr);
	void view_information(user* usr);
	void view_about();
	void view_leaderboard();
	void change_username(user* usr);
	void change_password(user* usr);
	void change_others(user* usr);
};

