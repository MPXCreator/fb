#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <rapidjson/document.h>

#define DEFAULT_LANG "en_us"

struct menu
{
	std::string intro;
	std::vector<std::string> options;
	std::string ask;
};

class lang
{
private:
	rapidjson::Document data;
	bool success = false;
public:
	lang(std::string file) {
		std::ifstream reader("resources/lang/" + file + ".json");
		if (!reader.is_open())
			return;
		if (data.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str()).HasParseError())
			return;
		success = true;
	}
	std::string get_property() {
		return data["property"].GetString();
	}
	std::string get_normal(std::string info) {
		assert(data[info.c_str()].IsString());
		return data[info.c_str()].GetString();
	}
	std::vector<std::string> get_special(std::string info) {
		std::vector<std::string> res;
		const rapidjson::Value& arr = data[info.c_str()];
		assert(arr.IsArray());
		for (rapidjson::Value::ConstValueIterator i = arr.Begin(); i != arr.End(); i++)
			res.push_back(i->GetString());
		return res;
	}
	menu get_menu(std::string info) {
		menu res;
		const rapidjson::Value& obj = data[info.c_str()];
		assert(obj.IsObject());
		res.intro = obj["intro"].GetString();
		res.ask = obj["ask"].GetString();
		const rapidjson::Value& arr = obj["options"];
		for (auto i = arr.Begin(); i != arr.End(); i++)
			res.options.push_back(i->GetString());
		return res;
	}
	std::string get_error(std::string info) {
		std::string res;
		const rapidjson::Value& obj = data["error"];
		assert(obj.IsObject());
		assert(obj[info.c_str()].IsString());
		return obj[info.c_str()].GetString();
	}
	std::string user_simple(std::string type, std::string info) {
		const rapidjson::Value& obj = data[type.c_str()];
		assert(obj.IsObject());
		assert(obj[info.c_str()].IsString());
		return obj[info.c_str()].GetString();
	}
	std::vector<std::string> user_complex(std::string type, std::string info) {
		std::vector<std::string> res;
		const rapidjson::Value& obj = data[type.c_str()];
		assert(obj.IsObject());
		assert(obj[info.c_str()].IsArray());
		const rapidjson::Value& arr = obj[info.c_str()];
		for (auto i = arr.Begin(); i != arr.End(); i++)
			res.push_back(i->GetString());
		return res;
	}
};

