// StartConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "user.h"
#include "resources.h"
#include "screen.h"
#include "lang.h"

resources all;
lang* word;
user* usr;
screen* window;
menu ops;

std::string get_time() {
    time_t now;
    time(&now);
    tm t;
    localtime_s(&t, &now);
    return std::to_string(t.tm_year + 1900) + '-' + std::to_string(t.tm_mon + 1) + '-' + std::to_string(t.tm_mday) + '/' + std::to_string(t.tm_hour) + ':' + std::to_string(t.tm_min) + ':' + std::to_string(t.tm_sec);
}

int main()
{
    std::string language;
    std::ifstream lr("lang");
    std::ofstream lw;
    if (!lr.is_open())
        language = "en_us";
    lr >> language;
    word = new lang(language);
    window = new screen();
    window->print_header();
    window->print_image();
    window->clear();
    ops = word->get_menu("menu_welcome");
    std::pair<std::string, std::string> np;
    switch (window->choose(ops.intro, ops.options, ops.ask)) {
    case 1:
        np = window->login(false);
        usr = new user(np.first, np.second);
        while (!usr->is_good())
        {
            delete usr;
            np = window->login(true);
            usr = new user(np.first, np.second);
        }
        break;
    case 2:
        np = window->signup(false);
        usr = new user(np.first, np.second, true);
        delete usr;
        usr = new user(np.first, np.second);
        while (!usr->is_good())
        {
            np = window->signup(true);
            usr = new user(np.first, np.second, true);
            delete usr;
            usr = new user(np.first, np.second);
        }
        break;
    case 3:
        language = all.get_langs()[window->choose(word->get_normal("lang_changer"), all.get_langs(), "") - 1];
        lw.open("lang");
        lw << language;
        exit(0);
    case 4:
        window->view_about();
    default:exit(0);
    }
    ops = word->get_menu("menu_main");
    std::ifstream reader;
    std::ofstream writer;
    int score;
    menu nxt = word->get_menu("menu_user");
    while (true)
        switch (window->choose(ops.intro, ops.options, ops.ask, usr)) {
        case 1:
            usr->generator(language);
            window->clear();
            window->print_header();
            system("call Flappy_Bird.exe");
            reader.open("result");
            reader >> score;
            usr->record(score);
            if (window->choose(word->get_normal("leaderboard"), { "Yes.","No" }, "") == 1)
            {
                writer.open("leaderboard", std::ios::app);
                writer << usr->get_name() << " " << get_time() << " " << score << std::endl;
            }
            break;
        case 2:
            window->view_history(usr);
            break;
        case 3:
            window->view_information(usr);
            break;
        case 4:
            switch (window->choose(nxt.intro, nxt.options, nxt.ask))
            {
            case 1:
                window->change_username(usr);
                break;
            case 2:
                window->change_password(usr);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                window->change_others(usr);
                break;
            case 9:
                usr->clear_histrory();
                break;
            default:
                break;
            }
            break;
        case 5:
            window->view_leaderboard();
            break;
        default:
            exit(0);
        }
    return 0;
}
