#include "Settings.h"

Settings::Settings(UserInfo *u, QWidget *parent)
	: usr(u),
	QWidget(parent)
	, ui(new Ui::SettingsClass())
{
	ui->setupUi(this);

	QFile file("resources/resources.json");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, "WARNING", "Cannot open resources.json!");
		this->close();
		return;
	}
	QJsonDocument tmp;
	QTextStream stream(&file);
	stream.setEncoding(QStringConverter::Utf8);
	QString str = stream.readAll();
	tmp = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	resources = tmp.object();

	QButtonGroup* soundbutton = new QButtonGroup(this);
	QButtonGroup* musicbutton = new QButtonGroup(this);
	soundbutton->addButton(ui->SoundOnradioButton, 0);
	soundbutton->addButton(ui->SoundOff, 1);
	musicbutton->addButton(ui->BGMOnradioButton, 0);
	musicbutton->addButton(ui->BGMOffradioButton, 1);

	reset();

	connect(ui->ResetpushButton, &QPushButton::clicked, this, &Settings::reset);
	connect(ui->RecoverpushButton, &QPushButton::clicked, this, &Settings::reset_default);
	connect(ui->ConfirmpushButton, &QPushButton::clicked, this, &Settings::confirm);
	connect(ui->ClassicpushButton, &QPushButton::clicked, this, &Settings::set_classic);
	connect(ui->AngryBirdpushButton, &QPushButton::clicked, this, &Settings::set_angrybird);
	connect(ui->IronManpushButton, &QPushButton::clicked, this, &Settings::set_ironman);
	connect(ui->MinecraftpushButton, &QPushButton::clicked, this, &Settings::set_minecraft);

	set_unknown();
}

Settings::~Settings()
{
	delete ui;
}

void Settings::reset() {
	update_box(usr->getInfo("bird").toString(), usr->getInfo("background").toString(),
		usr->getInfo("ground").toString(), usr->getInfo("pipe").toString(),
		usr->getInfo("bgm.file").toString());
	if (usr->getInfo("sound").toBool())
		ui->SoundOnradioButton->setChecked(true);
	else
		ui->SoundOff->setChecked(true);
	if (usr->getInfo("bgm").toBool())
		ui->BGMOnradioButton->setChecked(true);
	else
		ui->BGMOffradioButton->setChecked(true);
	set_unknown();
}

void Settings::reset_default()
{
	update_box("yellow", "day.png", "normal.png", "green.png", "C418 - Cat.flac");
	ui->BGMOnradioButton->setChecked(true);
	ui->SoundOnradioButton->setChecked(true);
	set_unknown();
}

void Settings::confirm()
{
	QString bd = ui->BirdcomboBox->currentText();
	QString bg = ui->BackgroundcomboBox->currentText();
	QString gd = ui->GroundcomboBox->currentText();
	QString pp = ui->PipecomboBox->currentText();
	QString bgm = ui->BGMcomboBox->currentText();
	usr->settings("bird", bd);
	usr->settings("background", bg);
	usr->settings("ground", gd);
	usr->settings("pipe", pp);
	usr->settings("bgm.file", bgm);
	usr->switcher("bgm", ui->BGMOnradioButton->isChecked());
	usr->switcher("sound", ui->SoundOnradioButton->isChecked());
	this->close();
}

void Settings::set_classic()
{
	QImage *img = new QImage;
	img->load("resources/posters/CLASSIC.png");
	QPixmap pixmap = QPixmap::fromImage(*img);
	int with = ui->showlabel->width();
	int height = ui->showlabel->height();
	QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->showlabel->setPixmap(fitpixmap);
	update_box("yellow", "day.png", "normal.png", "green.png", "");
}

void Settings::set_angrybird()
{
	QImage* img = new QImage;
	img->load("resources/posters/ANGRYBIRD.png");
	QPixmap pixmap = QPixmap::fromImage(*img);
	int with = ui->showlabel->width();
	int height = ui->showlabel->height();
	QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->showlabel->setPixmap(fitpixmap);
	update_box("angry", "angrybird.png", "angrybird.png", "gold.png", "");
}

void Settings::set_ironman()
{
	QImage* img = new QImage;
	img->load("resources/posters/IRONMAN.png");
	QPixmap pixmap = QPixmap::fromImage(*img);
	int with = ui->showlabel->width();
	int height = ui->showlabel->height();
	QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->showlabel->setPixmap(fitpixmap);
	update_box("ironman", "ironman.png", "ironman.png", "silver.png", "");
}

void Settings::set_minecraft()
{
	QImage* img = new QImage;
	img->load("resources/posters/MINECRAFT.png");
	QPixmap pixmap = QPixmap::fromImage(*img);
	int with = ui->showlabel->width();
	int height = ui->showlabel->height();
	QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->showlabel->setPixmap(fitpixmap);
	update_box("steve", "minecraft.png", "minecraft.png", "mc_green.png", "");
}

void Settings::set_unknown()
{
	QImage* img = new QImage;
	img->load("resources/posters/UNKNOWN.png");
	QPixmap pixmap = QPixmap::fromImage(*img);
	int with = ui->showlabel->width();
	int height = ui->showlabel->height();
	QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	ui->showlabel->setPixmap(fitpixmap);
}

void Settings::update_box(QString bd, QString bg, QString gd, QString pp, QString bgm)
{
	ui->BirdcomboBox->clear();
	ui->BackgroundcomboBox->clear();
	ui->GroundcomboBox->clear();
	ui->PipecomboBox->clear();
	if (!bgm.isEmpty())
		ui->BGMcomboBox->clear();

	QStringList strl;

	ui->BirdcomboBox->addItem(bd);
	QJsonObject obj = resources["birds"].toObject();
	for (auto i = obj.begin(); i != obj.end(); i++)
		if (i.key() != "mask" && i.key() != bd)
			strl << i.key();
	ui->BirdcomboBox->addItems(strl);

	ui->BackgroundcomboBox->addItem(bg);
	strl.clear();
	QJsonArray arr = resources["backgrounds"].toArray();
	for (auto i = arr.begin(); i != arr.end(); i++)
		if (i->toString() != bg)
			strl << i->toString();
	ui->BackgroundcomboBox->addItems(strl);

	ui->GroundcomboBox->addItem(gd);
	strl.clear();
	arr = resources["grounds"].toArray();
	for (auto i = arr.begin(); i != arr.end(); i++)
		if (i->toString() != gd)
			strl << i->toString();
	ui->GroundcomboBox->addItems(strl);

	ui->PipecomboBox->addItem(pp);
	strl.clear();
	arr = resources["pipes"].toArray();
	for (auto i = arr.begin(); i != arr.end(); i++)
		if (i->toString() != pp)
			strl << i->toString();
	ui->PipecomboBox->addItems(strl);

	if (!bgm.isEmpty()) {
		ui->BGMcomboBox->addItem(bgm);
		strl.clear();
		arr = resources["bgm"].toArray();
		for (auto i = arr.begin(); i != arr.end(); i++)
			if (i->toString() != bgm)
				strl << i->toString();
		ui->BGMcomboBox->addItems(strl);
	}
		
}
