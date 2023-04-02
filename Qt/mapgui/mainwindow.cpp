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

  //Affichage des Edges
  for(auto e: gr.getAllEdges()) {
    Vertex vStart, vEnd;

    for(auto v: gr.getAllVertices()){
      if(v.getId() == e.getStartId()) {
        vStart = v;
      }
      else if(v.getId() == e.getEndId()) {
        vEnd = v;
      }
    }
    item = new EdgeItem(vStart, vEnd);
    scene_->addItem(item);
    cnt++;
  }


  qDebug() << "Created " << cnt << " edge object";

  //Affichage des Vertices
  cnt = 0;
  for(auto v: gr.getAllVertices()) {
    item = new VertexItem(v);
    scene_->addItem(item);

    cnt++;
  }

  qDebug() << "Created " << cnt << " vertex object";

/*
  Vertex v11(1, -76.9296620544, 38.8925491793);
  Vertex v22(2, -77.0189335838, 38.8983222165);
  Vertex v12(3, -77.029695521,38.962182951);
  Vertex v23(4, -77.0261459838,38.9684738155);
  Vertex v13(5, -77.0007707257,38.9322592501);
  Vertex v24(6, -77.0223271184,38.9245525663);

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
*/
}
