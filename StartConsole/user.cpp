#include "user.h"

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

#pragma warning(disable : 4996)


std::string generate_guid() {
	GUID guid;
	char buffer[64] = { 0 };
	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
		return "";
	}
	_snprintf_s(buffer, sizeof(buffer),
		"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buffer);
}

std::string sha256(const std::string str)
{
	char buf[128];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::string NewString = "";
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf_s(buf, "%02x", hash[i]);
		NewString = NewString + buf;
	}
	return NewString;
}

void prettyWritefile(std::string file, rapidjson::Document& document)
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> pwriter(buffer);
	document.Accept(pwriter);
	std::ofstream writer(file);
	writer << buffer.GetString();
}

void user::read_list()
{
	std::ifstream reader(USER_LIST);
	if (!reader.is_open()) {
		if (_access(USER_DIR, 0) == -1)
			_mkdir(USER_DIR);
		std::ofstream writer(USER_LIST);
		writer << "{}";
		writer.close();
		reader.open(USER_LIST);
	}
	list.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str());
}

void user::write()
{
	prettyWritefile(USER_LIST, list);
	prettyWritefile(std::string(USER_DIR) + data["guid"].GetString() + ".json", data);
}

user::user(std::string username, std::string password)
{
	read_list();
	if (!list.HasMember(username.c_str()))
		return;
	std::ifstream reader(std::string(USER_DIR) + list[username.c_str()].GetString() + ".json");
	if (!reader.is_open() || data.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str()).HasParseError())
		return;
	if (data["password"].GetString() == sha256(password.c_str()))
		flag = true;
}

user::user(std::string username, std::string password, bool signup)
{
	read_list();
	if (list.HasMember(username.c_str()))
		return;
	//rapidjson::Document data;
	data.Parse("{}");
	rapidjson::Value tmp, id;
	tmp.SetString(username.c_str(), username.length());
	data.AddMember("username", tmp, data.GetAllocator());
	password = sha256(password);
	tmp.SetString(password.c_str(), password.length());
	data.AddMember("password", tmp, data.GetAllocator());
	std::string guid = generate_guid();
	tmp.SetString(guid.c_str(), guid.length());
	data.AddMember("guid", tmp, data.GetAllocator());
	tmp.SetString(username.c_str(), username.length());
	id.SetString(guid.c_str(), guid.length());
	list.AddMember(tmp, id, list.GetAllocator());
	tmp.SetInt(0);
	data.AddMember("bs", tmp, data.GetAllocator());
	tmp.SetString("yellow", 6);
	data.AddMember("bird", tmp, data.GetAllocator());
	tmp.SetString("day.png", 7);
	data.AddMember("background", tmp, data.GetAllocator());
	tmp.SetString("normal.png", 10);
	data.AddMember("ground", tmp, data.GetAllocator());
	tmp.SetString("red.png", 7);
	data.AddMember("pipe", tmp, data.GetAllocator());
	tmp.SetBool(true);
	data.AddMember("sound", tmp, data.GetAllocator());
	tmp.SetBool(true);
	data.AddMember("bgm", tmp, data.GetAllocator());
	tmp.SetString("C418 - Cat.flac", 15);
	data.AddMember("bgm.file", tmp, data.GetAllocator());
	tmp.SetArray();
	data.AddMember("history", tmp, data.GetAllocator());
	write();
}

void user::change_username(std::string username)
{
	rapidjson::Value x;
	x.SetString(data["username"].GetString(), strlen(data["username"].GetString()));
	std::string debug = data["username"].GetString();
	list.RemoveMember(x);
	data["username"].SetString(username.c_str(), username.length());
	rapidjson::Value tmp, id;
	tmp.SetString(username.c_str(), username.length());
	id.SetString(data["guid"].GetString(), strlen(data["guid"].GetString()));
	list.AddMember(tmp, id, list.GetAllocator());
	write();
}

bool user::change_password(std::string past, std::string now)
{
	bool f = data["password"].GetString() == sha256(past);
	if (f)
		data["password"].SetString(sha256(now).c_str(), sha256(now).length());
	write();
	return f;
}

void user::change_settings(std::string key, std::string val)
{
	data[key.c_str()].SetString(val.c_str(), val.length());
	write();
}

void user::change_settings(std::string key, bool val)
{
	data[key.c_str()].SetBool(val);
	write();
}

void user::generator(std::string language)
{
	rapidjson::Document pass;
	pass.SetObject();
	rapidjson::Value tmp;
	tmp.SetString(language.c_str(), language.length());
	pass.AddMember("lang", tmp, pass.GetAllocator());
	tmp.SetString(data["bird"].GetString(), strlen(data["bird"].GetString()));
	pass.AddMember("bird", tmp, pass.GetAllocator());
	tmp.SetString(data["background"].GetString(), strlen(data["background"].GetString()));
	pass.AddMember("background", tmp, pass.GetAllocator());
	tmp.SetString(data["ground"].GetString(), strlen(data["ground"].GetString()));
	pass.AddMember("ground", tmp, pass.GetAllocator());
	tmp.SetString(data["pipe"].GetString(), strlen(data["pipe"].GetString()));
	pass.AddMember("pipe", tmp, pass.GetAllocator());
	tmp.SetBool(data["sound"].GetBool());
	pass.AddMember("sound", data["sound"].GetBool(), pass.GetAllocator());
	tmp.SetBool(data["bgm"].GetBool());
	pass.AddMember("bgm", tmp, pass.GetAllocator());
	tmp.SetString(data["bgm.file"].GetString(), strlen(data["bgm.file"].GetString()));
	pass.AddMember("bgm.file", tmp, pass.GetAllocator());
	prettyWritefile("pass.json", pass);
}

std::string user::get_name()
{
	return std::string(data["username"].GetString());
}

std::string user::get_guid()
{
	return std::string(data["guid"].GetString());
}

std::string user::get_bird()
{
	return std::string(data["bird"].GetString());
}

std::string user::get_bg()
{
	return std::string(data["background"].GetString());
}

std::string user::get_gd()
{
	return std::string(data["ground"].GetString());
}

std::string user::get_bgmf()
{
	return std::string(data["bgm.file"].GetString());
}

bool user::get_sound()
{
	return data["sound"].GetBool();
}

bool user::get_bgm()
{
	return data["bgm"].GetBool();
}

int user::get_bs()
{
	return data["bs"].GetInt();
}

void user::record(int score)
{
	if (data["bs"].GetInt() < score)
		data["bs"].SetInt(score);
	time_t now;
	time(&now);
	tm t;
	localtime_s(&t, &now);
	std::string rec_time = std::to_string(t.tm_year + 1900) + '-' + std::to_string(t.tm_mon + 1) + '-' + std::to_string(t.tm_mday);
	rapidjson::Value res((rec_time + "," + std::to_string(score)).c_str(), data.GetAllocator());
	data["history"].PushBack(res, data.GetAllocator());
	write();
}

std::vector<std::pair<std::string, int>> user::get_history()
{
	std::vector<std::pair<std::string, int>> history;
	const rapidjson::Value& tmp = data["history"];
	for (auto i = tmp.Begin(); i != tmp.End(); i++)
	{
		std::string rec = i->GetString();
		history.push_back(std::make_pair(rec.substr(0, rec.find(',')), atoi(std::string(rec, rec.find(',') + 1, rec.size() - rec.find(',') - 1).c_str())));
	}
	return history;
}

void user::clear_histrory()
{
	data["history"].Clear();
	write();
}
