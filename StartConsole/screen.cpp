#include "screen.h"
#include <ColorfulConsoleIO.h>

#define OS_TYPE_WINDOWS_CC

extern resources all;
extern lang *word;

std::string birds[] = {
	"        ...*****##***..               ...*****##***..               ...*****##***..       ",
	"      .=***:::::*=   **.            .=***:::::*=   **.            .=***:::::*=   **.      ",
	"    :-+-:::===*#.    ::+=:        :-+-:::===*#.    ::+=:      :::=#+-::===*#.    ::+=:    ",
	"  -=+=:-======*#:.   ## :#:     -=+=:-======*#:.   ## :#:   :-=======++===*#:.   ## :#:   ",
	"  #*==========+++-.  -- :#:     ##+++++++++=+++-.  =- :#:   =#.......==++=+++-.  == :#:   ",
	"  ##*******=====++++++++*#++. -=---------#*===++++++++*#++. =#-:.....--#*===+++++++++#++. ",
	"=*=-:::::==#*==-#************=+#-:.....--#*===#************= .*+-----##=====#************=",
	"=#::..:::*#+++****##########-  .+********+++****##########-   .-##**#+*+++****##########- ",
	"-+---=+*#+++++++**********++.    .++***+++++++#*********++.    .++***+++++++#*********++. ",
	"  ++++==+********+++++++++.        .+=+********+==++++++.        .+=+********++======+.   "
};

std::string get_password() {
	std::string pw;
	char x;
	while (x = _getch())
	{
		if (x == '\n' || x == '\r')
			break;
		if (x == 8 && pw.length())
			pw = pw.substr(0, pw.length() - 1);
		else
			pw += x;
	}
	return pw;
}

/*wchar_t* string_to_wchar(const std::string& pKey)
{
	const char* pCStrKey = pKey.c_str();
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}*/


inline std::wstring string_to_wchar(const std::string& input)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(input);
}

void screen::clear()
{
	std::wcout << ConsoleBackgroundColor::None << ConsoleColor::None;
	system("cls");
}

int screen::wait() {
	std::wcout << ConsoleColor::Red << string_to_wchar(word->get_normal("wait")) << ConsoleColor::None;
	return _getch();
}

void screen::print_header()
{
	if (header.empty())
	{
		std::ifstream in(std::string(HEADER_PATH) + all.get_header());
		header = std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
	}
	std::cout << header << std::endl;
	std::cout << std::endl;
}

void screen::print_image()
{
	for (auto i : birds)
		std::wcout << ConsoleBackgroundColor::Green << ConsoleColor::Yellow << string_to_wchar(i) << std::endl;
	std::wcout << ConsoleBackgroundColor::None << ConsoleColor::None;
	std::cout << std::endl;
	std::wcout << ConsoleColor::Red << string_to_wchar(word->get_normal("loaded")) << ConsoleColor::None;
	_getch();
}

void screen::print_info(user* usr) {
	std::wcout << string_to_wchar(word->get_normal("username")) << ConsoleColor::Green << string_to_wchar(usr->get_name()) << ConsoleColor::None << "\t"
		<< string_to_wchar(word->get_normal("best")) << ConsoleColor::Green << usr->get_bs() << ConsoleColor::None
		<< std::endl;
}

void screen::print_image(int percent)
{
	clear();
	print_header();
	for (auto i : birds)
		std::cout << i.substr(20 + (percent - 39 > 0 ? percent - 39 : 0)) << std::endl;
}

void screen::construction() {
	clear();
	print_header();
	std::wcout << ConsoleColor::Red << string_to_wchar(word->get_normal("construction")) << ConsoleColor::None;
}

int screen::choose(std::string intro, std::vector<std::string> option, std::string ask, user* usr)
{
	int choice = 1;
	bool wrong = false;
	while (true)
	{
		clear();
		print_header();
		if (usr)
			print_info(usr);
		std::cout << std::endl;
		std::wcout << ConsoleColor::Yellow << string_to_wchar(intro) << ConsoleColor::None << std::endl;
		for (int i = 1; i <= option.size(); i++)
			std::wcout << (choice == i ? ConsoleBackgroundColor::Green : ConsoleBackgroundColor::None) << (i == choice ? L">>> " : L"    ") << "[" << i << "]" << L" " << string_to_wchar(option[i - 1]) << ConsoleBackgroundColor::None << std::endl;
		std::wcout << ConsoleColor::Red << string_to_wchar(word->get_normal("choose_notice")) << ConsoleColor::None << std::endl;
		int op = _getch();
		if (op == 224)
		{
			int tmp = _getch();
			if (tmp == 72)
			{
				if (choice > 1)
				{
					choice--;
				}
				else
					std::cout << "\a";
			}
			else if (tmp == 80)
			{
				if (choice < option.size())
				{
					choice++;
				}
				else
					std::cout << "\a";
			}
			else
				std::cout << "\a";
		}
		else if (op == '\r' || op == '\n')
		{
			return choice;
		}
		else
			std::cout << "\a";
	}
	return 0;
}

std::pair<std::string, std::string> screen::login(bool retry)
{
	clear();
	print_header();
	std::string un, pw;
	if (retry)
		std::wcout << ConsoleBackgroundColor::Red << string_to_wchar(word->get_error("login")) << ConsoleBackgroundColor::None << std::endl;
	else
		std::wcout << ConsoleColor::Yellow << string_to_wchar(word->user_simple("user_login", "status")) << ConsoleColor::None << std::endl;
	std::vector<std::string> tmp = word->user_complex("user_login", "username");
	std::wcout << string_to_wchar(tmp[0]) << (retry ? ConsoleBackgroundColor::Red : ConsoleBackgroundColor::Green) << string_to_wchar(tmp[1]) << ConsoleBackgroundColor::None << string_to_wchar(tmp[2]);
	std::cin >> un;
	tmp = word->user_complex("user_login", "password");
	std::wcout << string_to_wchar(tmp[0]) << (retry ? ConsoleBackgroundColor::Red : ConsoleBackgroundColor::Green) << string_to_wchar(tmp[1]) << ConsoleBackgroundColor::None << string_to_wchar(tmp[2]);
	pw = get_password();
	return std::pair<std::string, std::string>(un, pw);
}

std::pair<std::string, std::string> screen::signup(bool retry)
{
	clear();
	print_header();
	std::string un, pw, tmp;
	if (retry)
		std::wcout << ConsoleBackgroundColor::Red << string_to_wchar(word->get_error("signup")) << ConsoleBackgroundColor::None << std::endl;
	else
		std::wcout << ConsoleColor::Yellow << string_to_wchar(word->user_simple("user_creator", "status")) << ConsoleColor::None << std::endl;
	std::vector<std::string> abc = word->user_complex("user_creator", "username");
	std::wcout << string_to_wchar(abc[0]) << ConsoleBackgroundColor::Green << string_to_wchar(abc[1]) << ConsoleBackgroundColor::None << string_to_wchar(abc[2]);
	std::cin >> un;
	std::wcout << ConsoleColor::Red << string_to_wchar(word->user_simple("user_creator", "note")) << ConsoleColor::None << std::endl;
	abc = word->user_complex("user_creator", "password");
	std::wcout << string_to_wchar(abc[0]) << ConsoleBackgroundColor::Green << string_to_wchar(abc[1]) << ConsoleBackgroundColor::None << string_to_wchar(abc[2]);
	pw = get_password();
	std::cout << std::endl;
	abc = word->user_complex("user_creator", "reinput");
	std::wcout << string_to_wchar(abc[0]) << ConsoleBackgroundColor::Yellow << string_to_wchar(abc[1]) << ConsoleBackgroundColor::None << string_to_wchar(abc[2]);
	tmp = get_password();
	while (pw != tmp)
	{
		clear();
		print_header();
		abc = word->get_special("hello");
		std::wcout << string_to_wchar(abc[0]) << ConsoleColor::Green << string_to_wchar(un) << ConsoleColor::None << string_to_wchar(abc[1]) << std::endl;
		std::wcout << ConsoleColor::Red << string_to_wchar(word->get_error("pwd_not_match")) << ConsoleColor::None << std::endl;
		abc = word->user_complex("user_creator", "password");
		std::wcout << string_to_wchar(abc[0]) << ConsoleBackgroundColor::Red << string_to_wchar(abc[1]) << ConsoleBackgroundColor::None << string_to_wchar(abc[2]);
		pw = get_password();
		abc = word->user_complex("user_creator", "reinput");
		std::wcout << string_to_wchar(abc[0]) << ConsoleBackgroundColor::Red << string_to_wchar(abc[1]) << ConsoleBackgroundColor::None << string_to_wchar(abc[2]);
		tmp = get_password();
	}
	//std::wcout << ConsoleColor::Green << string_to_wchar(word->user_simple("user_creator", "success")) << ConsoleColor::None << std::endl;
	return std::pair<std::string, std::string>(un, pw);
}


void screen::view_history(user* usr) {
	clear();
	print_header();
	print_info(usr);
	std::wcout << "Time/Score" << std::endl;
	auto data = usr->get_history();
	for (auto i : data)
		std::wcout << ConsoleColor::Blue << string_to_wchar(i.first) << ConsoleColor::None << "/" << i.second << std::endl;
	wait();
}

void screen::view_information(user* usr) {
	clear();
	print_header();
	std::cout << std::endl;
	std::cout << word->get_normal("username") << usr->get_name() << std::endl
		<< word->get_normal("bird") << usr->get_bird() << std::endl
		<< word->get_normal("background") << usr->get_bg() << std::endl
		<< word->get_normal("ground") << usr->get_gd() << std::endl
		<< word->get_normal("sound") << (usr->get_sound() ? word->get_normal("enabled") : word->get_normal("disabled")) << std::endl
		<< word->get_normal("bgm") << (usr->get_bgm() ? word->get_normal("enabled") : word->get_normal("disabled")) << std::endl
		<< word->get_normal("bgm.file") << usr->get_bgmf() << std::endl;
	wait();
}

void screen::view_about()
{
	clear();
	print_header();
	std::cout << word->get_normal("about");
	wait();
}

struct rec {
	std::string name;
	std::string when;
	int score;
	bool operator<(rec x) {
		return score < x.score;
	}
};

void screen::view_leaderboard()
{
	clear();
	print_header();
	std::ifstream reader("leaderboard");
	rec tmp;
	std::vector<rec> records;
	while (reader >> tmp.name >> tmp.when >> tmp.score)
		records.push_back(tmp);
	sort(records.begin(), records.end());
	for (auto i = records.rbegin(); i != records.rend(); i++)
		std::cout << i->name << " " << i->when << " " << i->score << std::endl;
	wait();
}

void screen::change_username(user* usr)
{
	clear();
	print_header();
	std::cout << word->get_normal("change_username");
	std::string newer;
	std::cin >> newer;
	usr->change_username(newer);
}

void screen::change_password(user* usr)
{
	std::vector<std::string> hint = word->get_special("change_password");
	std::string p, n, t;
	std::cout << hint[0];
	p = get_password();
	std::cout << hint[1];
	n = get_password();
	std::cout << hint[2];
	t = get_password();
	while (n != t)
	{
		std::cout << hint[3] << std::endl << hint[1];
		n = get_password();
		std::cout << hint[2];
		t = get_password();
	}
	while (!usr->change_password(p, n)) {
		std::cout << hint[3] << std::endl;
		change_password(usr);
	}
}

void screen::change_others(user* usr)
{
	std::cout << word->get_normal("change_others") << std::endl
		<< std::string("users/") + usr->get_guid() + ".json" << std::endl;
	wait();
}
