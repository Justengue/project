#include "vertexitem.h"
#include "edgeitem.h"
#include "graph.h"
#include "mainwindow.h"
#include "view.h"
#include <fstream>


MainWindow::MainWindow(QWidget */*parent*/)
    : scene_(new QGraphicsScene(this))
{
    scene_->setBackgroundBrush(Qt::black);
    populateScene();

    View *view = new View("Main Map View");
    view->view()->setScene(scene_);

    setCentralWidget(view);

    setWindowTitle(tr("MapGui Simple Example"));
}

void MainWindow::populateScene()
{
  // read a dummy graph file
  // vertexid  X Y
  std::string file_name{"./mapdata.txt"};
  std::ifstream fin{file_name};
  std::string line;
  size_t cnt{0};
  while (std::getline(fin, line)) {
    ++cnt;
    QGraphicsItem *item = new VertexItem(line);
    scene_->addItem(item);
  }
  qDebug() << "Created " << cnt << " vertex object";
}
