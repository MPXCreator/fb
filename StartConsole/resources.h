#pragma once
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>

#define RESOURCES_PATH "resources/resources.json"
#define HEADER_PATH "resources/header/"

class resources
{
private:
	rapidjson::Document data;
	std::default_random_engine re;
public:
	resources();
	int rand();
	std::string get_header();
	std::string get_header(int x);
	std::vector<std::string> get_birds();
	std::vector<std::string> get_backgrounds();
	std::vector<std::string> get_langs();
	std::vector<std::string> get_grounds();
	std::vector<std::string> get_pipes();
	std::vector<std::string> get_bgm();
	std::string get_sound(std::string x);
};

