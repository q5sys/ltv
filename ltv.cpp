#include "ltv.h"
#include "ui_ltv.h"
#include <QDir>
#include <QDebug>
#include <QPixmap>

ltv::ltv(QWidget *parent) : QMainWindow(parent), ui(new Ui::ltv){
  ui->setupUi(this);

  // ~~ Dir Window ~~ //
  dirModel = new QFileSystemModel(this);
  dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs); // set filter
  dirModel->setRootPath(QDir::rootPath()); // set root path
  ui->dirview->setModel(dirModel); // link to the ui
  // ui->dirview->setRootIndex(dirModel->setRootPath(QDir::homePath())); // for home dir only

  // ~~ File Window ~~ //
  fileModel = new QFileSystemModel(this);
  //fileInfoList = dir.entryInfoList(filters, QDir::Files|QDir::NoDotAndDotDot);
  fileModel->setFilter(QDir::Files); // set initial filter
  QStringList filters;
  filters << "*.png" << "*.jpg" << "*.bmp";
  fileModel->setNameFilters(filters); // set more filters
  fileModel->setRootPath(QDir::homePath()); // set root path
  ui->fileview->setModel(fileModel); // link to the ui
  ui->fileview->setColumnHidden(2, true);
  ui->fileview->setColumnHidden(3, true);

  // ui->fileview->setRootIndex(fileModel->setRootPath(QDir::homePath())); // for home dir only

  // set the UI to look the way we want
  ui->dirview->setHeaderHidden(true);
  //ui->fileview->setHeaderHidden(true);
  ui->dirview->resizeColumnToContents(0);
  ui->dirview->setColumnHidden(1, true);
  ui->dirview->setColumnHidden(2, true);
  ui->dirview->setColumnHidden(3, true);

}

ltv::~ltv(){
  delete ui;
}

void ltv::on_dirview_clicked(const QModelIndex &index){
  QString newPath = dirModel->fileInfo(index).absoluteFilePath(); // get new path
  ui->fileview->setRootIndex(fileModel->setRootPath(newPath));
}

void ltv::on_fileview_clicked(const QModelIndex &index){
  QString newPath = fileModel->fileInfo(index).absoluteFilePath(); // get new path
  QFile file(newPath);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QString text = file.readAll();
    QTextDocument *document = new QTextDocument(ui->textBrowserWindow);
    document->setPlainText(text);
    ui->textBrowserWindow->setDocument(document);
    }
}
