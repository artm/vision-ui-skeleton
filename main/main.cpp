#include "artmgl.h"
#include <LoggingHub.hpp>

int
main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainw;
    mainw.setWindowTitle("qartm");
    mainw.showMaximized();
    mainw.raise();

    ArtmGL * gl = new ArtmGL();
    mainw.setCentralWidget(gl);

    QArtm::LoggingHub::setup(&mainw);

    qDebug() << "Program started";
    return app.exec();
}
