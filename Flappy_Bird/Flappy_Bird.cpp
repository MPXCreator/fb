// Flappy_Bird.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <easyx.h>
#include <fstream>
#include <rapidjson/document.h>
#include <math.h>
#include <list>
#include <ColorfulConsoleIO.h>
#include <codecvt>
#include <irrKlang/irrKlang.h>
#include "renderman.h"
#define PASS "pass.json"
#pragma comment(lib, "irrKlang.lib")

rapidjson::Document settings, resources, lang;

#define WIDTH 288
#define HEIGHT 512
#define RESOURCES "resources/resources.json"
#define BACKGROUNDS "resources/backgrounds/"
#define GROUNDS "resources/grounds/"
#define PIPES "resources/pipes/"
#define BIRDS "resources/birds/"
#define SOUNDS "resources/sounds/"
#define BGM "resources/bgm/"
#define LANG "resources/lang/"

#define FLAP "resources/sounds/flap.wav"
#define HIT "resources/sounds/hit.wav"
#define DIE "resources/sounds/die.wav"
#define SCORE "resources/sounds/point.wav"

struct bird
{
    int x = 0, ps = 2;
    int pos = 190, stat = 0;
    int velocity = 0, acceleration = 1;
    double rad = 0, omega = 0, alpha = -PI / 200;
    const double max_rad = PI / 4, min_rad = -PI / 2;
};

inline std::wstring string_to_wstring(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

std::string get_time() {
    time_t now;
    time(&now);
    tm t;
    localtime_s(&t, &now);
    return std::to_string(t.tm_year + 1900) + '-' + std::to_string(t.tm_mon + 1) + '-' + std::to_string(t.tm_mday) + ' ' + std::to_string(t.tm_hour) + ':' + std::to_string(t.tm_min) + ':' + std::to_string(t.tm_sec);
}

int main()
{
    srand(time(0));
    irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
    std::ifstream reader(PASS);
    if (!reader.is_open() || settings.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str()).HasParseError())
        return -1;
    reader.close();
    reader.open(RESOURCES);
    if (!reader.is_open() || resources.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str()).HasParseError())
        return -1;
    reader.close();
    reader.open(std::string(LANG) + settings["lang"].GetString() + ".json");
    if (!reader.is_open() || lang.Parse(std::string(std::istreambuf_iterator<char>(reader), std::istreambuf_iterator<char>()).c_str()).HasParseError())
        return -1;
    reader.close();
    renderman* pixar = new renderman(WIDTH, HEIGHT, 1);
    pixar->load_bg(std::string(BACKGROUNDS) + settings["background"].GetString());
    pixar->load_gd(std::string(GROUNDS) + settings["ground"].GetString());
    pixar->load_pp(std::string(PIPES) + settings["pipe"].GetString(), std::string(PIPES) + "mask.png");
    const rapidjson::Value& mks = resources["birds"]["mask"];
    const rapidjson::Value& bds = resources["birds"][settings["bird"].GetString()];
    std::vector<std::string> ori, del;
    for (auto i = bds.Begin(); i != bds.End(); i++)
        ori.push_back(std::string(BIRDS) + i->GetString());
    for (auto i = mks.Begin(); i != mks.End(); i++)
        del.push_back(std::string(BIRDS) + i->GetString());
    pixar->load_bd(ori, del);
    std::string sbg = settings["background"].GetString();
    if (sbg == "minecraft.png")
        pixar->load_title("MC.png");
    else if (sbg == "ironman.png")
        pixar->load_title("IRONMAN.png");
    else if (sbg == "angrybird.png")
        pixar->load_title("ANGRY.png");
    else
    pixar->load_title("CLASSIC.png");

    std::wcout << ConsoleBackgroundColor::White << ConsoleColor::Black << string_to_wstring(std::string(lang["log"].GetString())) << ConsoleColor::None << ConsoleBackgroundColor::None << std::endl;

    bird nemo;

    std::vector<int> stats = { 0,1,2,1 };

    cleardevice();
    timeBeginPeriod(1);
    LARGE_INTEGER startCount, endCount, F;
    QueryPerformanceFrequency(&F);

    BeginBatchDraw();


    while (true) {
        QueryPerformanceCounter(&startCount);
        cleardevice();

        pixar->render_bg();
        pixar->render_gd(nemo.x);
        pixar->render_bd(nemo.pos, nemo.stat, nemo.rad);
        pixar->render_start();
        nemo.x += nemo.ps;
        nemo.stat = stats[(nemo.x / nemo.ps / 8) % 4];

        QueryPerformanceCounter(&endCount);
        long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 1000000 / 120)
		{
			Sleep(1);

			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;

		}
        ExMessage msg;
        if (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN)
            break;
        FlushBatchDraw();
    }

    if (settings["bgm"].GetBool())
        engine->play2D((std::string(BGM) + settings["bgm.file"].GetString()).c_str(), true);
    nemo.x = 0;
    nemo.stat = 0;
    std::list<std::pair<int, int>> pipes;
    pipes.push_back(std::make_pair(288, rand() %200 + 100));
    pipes.push_back(std::make_pair(288 + 144 + 25, rand() % 200 + 100));
    int score = 0;
    bool gotit = false, sound = settings["sound"].GetBool();
    while (true) {
        QueryPerformanceCounter(&startCount);
        cleardevice();

        pixar->render_bg();
        pixar->render_gd(nemo.x);
        for (auto i : pipes)
            pixar->render_pp(i.first - nemo.x, i.second);
        pixar->render_bd(nemo.pos, nemo.stat, nemo.rad);
        pixar->render_score(score);
        
        nemo.x += nemo.ps;
        nemo.pos += nemo.velocity / 8;
        nemo.velocity += nemo.acceleration;
        nemo.stat = stats[(nemo.x / nemo.ps / 8) % 4];
        nemo.rad += nemo.omega;
        nemo.omega += nemo.alpha;
        if (nemo.rad > nemo.max_rad)
            nemo.rad = nemo.max_rad;
        else if (nemo.rad < nemo.min_rad)
            nemo.rad = nemo.min_rad;

        if (nemo.x >= pipes.front().first - 65 && nemo.x <= pipes.front().first)
            if (!(nemo.pos >= 320 - pipes.front().second - 3 && nemo.pos <= 480 - pipes.front().second + 3))
            {
                if (sound)
                    engine->play2D(HIT, false);
                break;
            }
        if (nemo.pos >= 380)
            break;
        if (pipes.front().first + 52 - 100 <= nemo.x && !gotit)
        {
            if (sound)
                engine->play2D(SCORE, false);
            score += gotit = !gotit;
        }
        if (pipes.front().first + 52 <= nemo.x)
        {
            pipes.pop_front();
            pipes.push_back(std::make_pair(nemo.x + 288, rand() % 200 + 100));
            gotit = false;
            //std::wcout << string_to_wstring(get_time()) << " " << ConsoleColor::Green << string_to_wstring(std::string(lang["plus"].GetString())) << ConsoleColor::None << std::endl;
        }

        QueryPerformanceCounter(&endCount);
        long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
        while (elapse < 1000000 / 120)
        {
            Sleep(1);

            ExMessage msg;
            if (peekmessage(&msg, EX_MOUSE)) {
                if (msg.message == WM_LBUTTONDOWN) {
                    if (sound)
                        engine->play2D(FLAP);
                    nemo.velocity = -32;
                    nemo.omega = PI / 4;
                }
                if (msg.ctrl)
                    nemo.ps = 3;
                else if (msg.shift)
                    nemo.ps = 1;
                else
                    nemo.ps = 2;
                if (msg.rbutton)
                {
                    engine->play2D("resources/sounds/select_1.wav");
                    pixar->render_pause();
                    FlushBatchDraw();
                    while (!msg.lbutton)
                        peekmessage(&msg, EX_MOUSE);
                }
                //std::wcout << string_to_wstring(get_time()) << " " << ConsoleColor::Blue << string_to_wstring(std::string(lang["click"].GetString())) << ConsoleColor::None << std::endl;
            }

            QueryPerformanceCounter(&endCount);
            elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;

        }
        FlushBatchDraw();
    }
    Sleep(250);
    if (sound)
        engine->play2D(DIE);
    if (nemo.pos < 380)
        nemo.velocity = -16, nemo.omega = PI / 16;
    while (nemo.pos < 380)
    {
        QueryPerformanceCounter(&startCount);
        cleardevice();

        pixar->render_bg();
        pixar->render_gd(nemo.x);
        for (auto i : pipes)
            pixar->render_pp(i.first - nemo.x, i.second);
        pixar->render_bd(nemo.pos, nemo.stat, nemo.rad);
        pixar->render_score(score);
        QueryPerformanceCounter(&endCount);

        nemo.pos += nemo.velocity / 2;
        nemo.velocity += nemo.acceleration;
        nemo.stat = stats[(nemo.x / nemo.ps / 8) % 4];
        nemo.rad += nemo.omega;
        nemo.omega += nemo.alpha;
        if (nemo.rad > nemo.max_rad)
            nemo.rad = nemo.max_rad;
        else if (nemo.rad < nemo.min_rad)
            nemo.rad = nemo.min_rad;

        long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
        while (elapse < 1000000 / 120)
        {
            Sleep(1);
            QueryPerformanceCounter(&endCount);
            elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
        }
        FlushBatchDraw();
    }

    pixar->render_bg();
    pixar->render_gd(nemo.x);
    for (auto i : pipes)
        pixar->render_pp(i.first - nemo.x, i.second);
    pixar->render_bd(nemo.pos, nemo.stat, nemo.rad);
    pixar->render_over();

    FlushBatchDraw();

    ExMessage msg;
    while (!(peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN));

    EndBatchDraw();

    std::ofstream writer("result");
    writer << score;
    return 0;
}

