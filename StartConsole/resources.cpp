#include "resources.h"

resources::resources()
{
	std::ifstream reader(RESOURCES_PATH);
	data.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str());
	std::default_random_engine x(time(0));
	re = x;
}

int resources::rand()
{
	return re();
}

std::string resources::get_header()
{
	return get_header(rand() % data["headers"].Size());
}

std::string resources::get_header(int x)
{
	return (data["headers"].Begin() + x - 1)->GetString();
}

std::vector<std::string> resources::get_birds()
{
	std::vector<std::string> res;
	for (auto i = data["birds"].Begin(); i != data["birds"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::vector<std::string> resources::get_backgrounds()
{
	std::vector<std::string> res;
	for (auto i = data["backgrounds"].Begin(); i != data["backgrounds"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::vector<std::string> resources::get_langs()
{
	std::vector<std::string> res;
	for (auto i = data["lang"].Begin(); i != data["lang"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::vector<std::string> resources::get_grounds()
{
	std::vector<std::string> res;
	for (auto i = data["grounds"].Begin(); i != data["grounds"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::vector<std::string> resources::get_pipes()
{
	std::vector<std::string> res;
	for (auto i = data["pipes"].Begin(); i != data["pipes"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::vector<std::string> resources::get_bgm()
{
	std::vector<std::string> res;
	for (auto i = data["bgm"].Begin(); i != data["bgm"].End(); i++)
		res.push_back(i->GetString());
	return res;
}

std::string resources::get_sound(std::string x)
{
	return std::string(data[x.c_str()].GetString());
}
