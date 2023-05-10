#pragma once
#include <easyx.h>
#include <string>
#include <vector>

#define PI 3.14159265358979323846
#define OPTIONS "resources/options.png"
#define _OPTIONS "resources/options_.png"
#define NUMS "resources/num_b.png"

class renderman
{
private:
	double rate;
	const int width, height;
	IMAGE bg, gd, pp, _pp, bd[3], mk[3], ops, _ops, num, tt, _tt, at, _at;
	struct node {
		int val;
		node* nxt = NULL;
		node(int x) : val(x) {}
	};
public:
	renderman(int w, int h, double r) : width(w), height(h), rate(r) {
		initgraph(w * r, h * r);
		loadimage(&ops, _T(OPTIONS), 314, 748);
		loadimage(&_ops, _T(_OPTIONS), 314, 748);
		loadimage(&num, _T(NUMS), 252, 36);
	}
	~renderman() {
		closegraph();
	}
	void load_title(std::string x);
	void load_bd(std::vector<std::string> path, std::vector<std::string> _path);
	void load_bg(std::string path);
	void load_gd(std::string path);
	void load_pp(std::string path, std::string _path);
	void render_bd(int h, int stat, double rad);
	void render_pp(int pos, int height);
	void render_bg();
	void render_gd(int pos);
	void render_score(int score);
	void render_start();
	void render_over();
	void render_pause();
	void del_node(node *p);
};

