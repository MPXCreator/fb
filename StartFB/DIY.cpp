#include "DIY.h"

DIY::DIY(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DIYClass())
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

	ui->File1lineEdit->setFocusPolicy(Qt::NoFocus);
	ui->File2lineEdit->setFocusPolicy(Qt::NoFocus);
	ui->File3lineEdit->setFocusPolicy(Qt::NoFocus);
	ui->BackgroundlineEdit->setFocusPolicy(Qt::NoFocus);
	ui->GroundlineEdit->setFocusPolicy(Qt::NoFocus);
	ui->PipelineEdit->setFocusPolicy(Qt::NoFocus);
	ui->BGMlineEdit->setFocusPolicy(Qt::NoFocus);

	connect(ui->File1pushButton, &QPushButton::clicked, this, &DIY::BirdFile1_slot);
	connect(ui->File2pushButton, &QPushButton::clicked, this, &DIY::BirdFile2_slot);
	connect(ui->File3pushButton, &QPushButton::clicked, this, &DIY::BirdFile3_slot);
	connect(ui->BackgroundpushButton, &QPushButton::clicked, this, &DIY::BackgroundFile_slot);
	connect(ui->GroundpushButton, &QPushButton::clicked, this, &DIY::GroundFile_slot);
	connect(ui->PipepushButton, &QPushButton::clicked, this, &DIY::PipeFile_slot);
	connect(ui->BGMpushButton, &QPushButton::clicked, this, &DIY::BGMFile_slot);
	connect(ui->BirdClearpushButton, &QPushButton::clicked, this, &DIY::BirdClear);
	connect(ui->BackgroundClearpushButton, &QPushButton::clicked, this, &DIY::BackgroundClear);
	connect(ui->GroundClearpushButton, &QPushButton::clicked, this, &DIY::GroundClear);
	connect(ui->PipeClearpushButton, &QPushButton::clicked, this, &DIY::PipeClear);
	connect(ui->BGMClearpushButton, &QPushButton::clicked, this, &DIY::BGMClear);
	connect(ui->BirdCommitpushButton, &QPushButton::clicked, this, &DIY::BirdCommit);
	connect(ui->BackgroundCommitpushButton, &QPushButton::clicked, this, &DIY::BackgroundCommit);
	connect(ui->GroundCommitpushButton, &QPushButton::clicked, this, &DIY::GroundCommit);
	connect(ui->PipeCommitpushButton, &QPushButton::clicked, this, &DIY::PipeCommit);
	connect(ui->BGMCommitpushButton, &QPushButton::clicked, this, &DIY::BGMCommit);
}

DIY::~DIY()
{
	delete ui;
}

void DIY::update() {
	QFile file("resources/resources.json");
	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		QMessageBox::warning(NULL, "WARNING", "Cannot update resources.json!");
		return;
	}
	QTextStream writeStream(&file);
	writeStream.setEncoding(QStringConverter::Utf8);
	QJsonDocument doc(resources);
	writeStream << doc.toJson();
}

void DIY::BirdFile1_slot()
{
	ui->File1lineEdit->setText(QFileDialog::getOpenFileName(this, "Select Bird File 1.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::BirdFile2_slot()
{
	ui->File2lineEdit->setText(QFileDialog::getOpenFileName(this, "Select Bird File 2.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::BirdFile3_slot()
{
	ui->File3lineEdit->setText(QFileDialog::getOpenFileName(this, "Select Bird File 3.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::BackgroundFile_slot()
{
	ui->BackgroundlineEdit->setText(QFileDialog::getOpenFileName(this, "Select Background File.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::GroundFile_slot()
{
	ui->GroundlineEdit->setText(QFileDialog::getOpenFileName(this, "Select Ground File.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::PipeFile_slot()
{
	ui->PipelineEdit->setText(QFileDialog::getOpenFileName(this, "Select Pipe File.", QDir::currentPath(), "Image(*.png)"));
}

void DIY::BGMFile_slot()
{
	ui->BGMlineEdit->setText(QFileDialog::getOpenFileName(this, "Select BGM File.", QDir::currentPath(), "Music(*.mp3, *.flac, *.wav)"));
}

void DIY::BirdClear()
{
	ui->BirdNameLineEdit->clear();
	ui->File1lineEdit->clear();
	ui->File2lineEdit->clear();
	ui->File3lineEdit->clear();
}

void DIY::BackgroundClear()
{
	ui->BackgroundlineEdit->clear();
}

void DIY::GroundClear()
{
	ui->GroundlineEdit->clear();
}

void DIY::PipeClear()
{
	ui->PipelineEdit->clear();
}

void DIY::BGMClear()
{
	ui->BGMlineEdit->clear();
}

void DIY::BirdCommit()
{
	QString Name = ui->BirdNameLineEdit->text(),
		File1 = ui->File1lineEdit->text(),
		File2 = ui->File2lineEdit->text(),
		File3 = ui->File3lineEdit->text();
	if (Name.isEmpty() || File1.isEmpty() || File2.isEmpty() || File3.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Please do not leave blank.");
		return;
	}
	QFile::copy(File1, "resources/birds/" + Name + "_0.png");
	QFile::copy(File2, "resources/birds/" + Name + "_1.png");
	QFile::copy(File3, "resources/birds/" + Name + "_2.png");
	QJsonArray arr;
	arr.append(Name + "_0.png");
	arr.append(Name + "_1.png");
	arr.append(Name + "_2.png");
	QJsonObject tmp = resources["birds"].toObject();
	tmp.insert(Name, arr);
	resources["birds"] = tmp;
	update();
	QMessageBox::information(this, "Note", "Successfully imported a bird!");
}

void DIY::BackgroundCommit()
{
	QString fileName = ui->BackgroundlineEdit->text();
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Please do not leave blank.");
		return;
	}
	QFileInfo info(fileName);
	QFile::copy(fileName, "resources/backgrounds/" + info.fileName());
	QJsonArray tmp = resources["backgrounds"].toArray();
	tmp.append(info.fileName());
	resources["backgrounds"] = tmp;
	update();
	QMessageBox::information(this, "Note", "Successfully imported a background!");
}

void DIY::GroundCommit()
{
	QString fileName = ui->GroundlineEdit->text();
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Please do not leave blank.");
		return;
	}
	QFileInfo info(fileName);
	QFile::copy(fileName, "resources/grounds/" + info.fileName());
	QJsonArray tmp = resources["backgrounds"].toArray();
	tmp.append(info.fileName());
	resources["grounds"] = tmp;
	update();
	QMessageBox::information(this, "Note", "Successfully imported a ground!");
}

void DIY::PipeCommit()
{
	QString fileName = ui->PipelineEdit->text();
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Please do not leave blank.");
		return;
	}
	QFileInfo info(fileName);
	QFile::copy(fileName, "resources/pipes/" + info.fileName());
	QJsonArray tmp = resources["pipes"].toArray();
	tmp.append(info.fileName());
	resources["pipes"] = tmp;
	update();
	QMessageBox::information(this, "Note", "Successfully imported a pipe!");
}

void DIY::BGMCommit()
{
	QString fileName = ui->GroundlineEdit->text();
	if (fileName.isEmpty()) {
		QMessageBox::warning(this, "WARNING", "Please do not leave blank.");
		return;
	}
	QFileInfo info(fileName);
	QFile::copy(fileName, "resources/bgm/" + info.fileName());
	QJsonArray tmp = resources["bgm"].toArray();
	tmp.append(info.fileName());
	resources["bgm"] = tmp;
	update();
	QMessageBox::information(this, "Note", "Successfully imported a BGM!");
}
