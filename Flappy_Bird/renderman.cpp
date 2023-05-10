#include "renderman.h"

wchar_t* string_to_wchar(const std::string& pKey)
{
	const char* pCStrKey = pKey.c_str();
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	wchar_t* pWCStrKey = new wchar_t[pSize];
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
	return pWCStrKey;
}

void renderman::load_title(std::string x)
{
	std::string path = "resources/title/" + x;
	loadimage(&tt, string_to_wchar(path), 180, 52);
	loadimage(&_tt, L"resources/title/MASK.png", 180, 52);
	loadimage(&at, L"resources/title/fu.png", 140, 16);
	loadimage(&_at, L"resources/title/fuu.png", 140, 16);
}

void renderman::load_bd(std::vector<std::string> path, std::vector<std::string> _path)
{
	for (int i = 0; i < 3; i++) {
		loadimage(&bd[i], string_to_wchar(path[i]), 42, 42, true);
		loadimage(&mk[i], string_to_wchar(_path[i]), 42, 42, true);
	}
}

void renderman::load_bg(std::string path)
{
	loadimage(&bg, string_to_wchar(path), 288, 512, true);
}

void renderman::load_gd(std::string path)
{
	loadimage(&gd, string_to_wchar(path), 336, 112, true);
}

void renderman::load_pp(std::string path, std::string _path)
{
	loadimage(&pp, string_to_wchar(path), 60, 800);
	loadimage(&_pp, string_to_wchar(_path), 60, 800);
}

void renderman::render_bd(int h, int stat, double rad)
{
	IMAGE rbd, rmk;
	rotateimage(&rbd, &bd[stat], rad, BLACK);
	rotateimage(&rmk, &mk[stat], rad, WHITE);
	putimage(44, h, 34, 34, &rmk, 4, 4, SRCAND);
	putimage(44, h, 34, 34, &rbd, 4, 4, SRCPAINT);
	//putimage(100, h, &rmk, SRCAND);
	//putimage(100, h, &rbd, SRCPAINT);
}

void renderman::render_pp(int pos, int height)
{
	putimage(pos, -height, 52, 800, &_pp, 0, 0, SRCAND);
	putimage(pos, -height, 52, 800, &pp, 0, 0, SRCPAINT);
	//putimage(pos, -height, &_pp, SRCAND);
	//putimage(pos, -height, &pp, SRCPAINT);
}

void renderman::render_bg()
{
	putimage(0, 0, &bg);
}

void renderman::render_gd(int pos)
{
	//putimage(0, 400, 288, 112, &gd, pos % 48, 0);
	if (pos % 336 <= 47)
		putimage(0, 400, 288, 112, &gd, pos % 336, 0);
	else {
		putimage(0, 400, 336 - (pos % 336), 112, &gd, pos % 336, 0);
		putimage(336 - (pos % 336) - 1, 400, 288 - (336 - (pos % 336)), 112, &gd, 0, 0);
	}
}

const int st[10] = { 0, 13, 22, 35, 48, 61, 74, 87, 100, 113 };

void renderman::render_score(int score)
{
	//settextstyle(20, 0, L"Consolas");
	//outtextxy(3, 3, string_to_wchar(std::to_string(score)));
	node* head = new node(score % 10);
	score /= 10;
	while (score) {
		node* tmp = new node(score % 10);
		score /= 10;
		tmp->nxt = head;
		head = tmp;
	}
	node* p = head;
	int last = 10;
	while (p) {
		putimage(last, 10, (p->val == 1 ? 14 : 26), 36, &num, st[p->val] * 2, 0);
		last += (p->val == 1 ? 14 : 26);
		p = p->nxt;
	}
	del_node(head);
}
//0,47 89*24
//98,0 57*53
void renderman::render_start()
{
	putimage(144 - 89, 60, 178, 58, &_tt, 0, 0, SRCAND);
	putimage(144 - 89, 60, 178, 58, &tt, 0, 0, SRCPAINT);
	putimage(144 - 70, 110, &_at, SRCAND);
	putimage(144 - 70, 110, &at, SRCPAINT);
	putimage(144 - 57, 400 - 106, 114, 106, &_ops, 196, 0, SRCAND);
	putimage(144 - 57, 400 - 106, 114, 106, &ops, 196, 0, SRCPAINT);
}

//0,25 96*21
void renderman::render_over()
{
	putimage(144 - 96, 60, 194, 44, &_ops, 0, 50, SRCAND);
	putimage(144 - 96, 60, 194, 44, &ops, 0, 50, SRCPAINT);
}

void renderman::render_pause()
{
	putimage(252, 10, 26, 28, &ops, 0, 190);
}

void renderman::del_node(node* p)
{
	if (p->nxt)
		del_node(p->nxt);
	delete p;
}
