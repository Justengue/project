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
  int cnt = 0;

  Graph gr("data.csv");

  QGraphicsItem *item;
  //Affichage des Vertices
  /*
  for(auto v: gr.getAllVertices()) {
    item = new VertexItem(v);
    scene_->addItem(item);

    cnt++;
  }
  //Affichage des Edges
  for(auto e: gr.getAllEdges()) {
    for(auto v: gr.getAllVertices()){
      if(v.getId() == e.getStartId()) {
        Vertex vStart = v;
      }
      else if(v.getId() == e.getEndId()) {
        Vertex vEnd = v;
      }
    }
    item = new EdgeItem(vStart, vEnd);
    scene_->addItem(item);
  }
  */

  Vertex v11(1, 20, 40);
  Vertex v22(2, 20, 100);
  Vertex v12(3, 100, 40);
  Vertex v23(4, 140, 100);
  Vertex v13(5, 200, 40);
  Vertex v24(6, 200, 100);

  Vertex vlist[6] = {v11, v22, v12, v23, v13, v24};

  for(int i = 0; i < 6; i++) {
    item = new VertexItem(vlist[i]);
    scene_->addItem(item);
  }

  Edge e1(1, 2, 50.0);
  Edge e2(3, 4, 50.0);
  Edge e3(5, 6, 50.0);

  Edge edges[3] = {e1, e2, e3};

  for(auto e: edges) {
      Vertex vStart, vEnd;
      for(auto v: vlist){
        if(v.getId() == e.getStartId()) {
          vStart = v;
          qDebug() << "Vstart : " << vStart.getLat() << "       " << vStart.getLong();
        }
        else if(v.getId() == e.getEndId()) {
          vEnd = v;
          qDebug() << "Vend : " << vEnd.getLat() << "       " << vEnd.getLong();
        }
      }
      item = new EdgeItem(vStart, vEnd);
      scene_->addItem(item);
  }
  qDebug() << "Created " << cnt << " vertex object";
}
