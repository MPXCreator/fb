#pragma once
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <io.h>
#include <direct.h>
#include <conio.h>
#include <Windows.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <openssl/sha.h>

#define USER_DIR "./users/"
#define USER_LIST "./users/list.json"

class user
{
private:
	rapidjson::Document list;
	rapidjson::Document data;
	bool flag = false;
public:
	void read_list();
	void write();
	user(std::string username, std::string password);
	user(std::string username, std::string password, bool signup);
	void change_username(std::string username);
	bool change_password(std::string past, std::string now);
	void change_settings(std::string key, std::string val);
	void change_settings(std::string key, bool val);
	void generator(std::string language);
	std::string get_name();
	std::string get_guid();
	std::string get_bird();
	std::string get_bg();
	std::string get_gd();
	std::string get_bgmf();
	bool get_sound();
	bool get_bgm();
	int get_bs();
	void record(int score);
	std::vector<std::pair<std::string, int>> get_history();
	bool is_good() { return flag;  }
	void clear_histrory();
};

