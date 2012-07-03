#include <LoggingHub.hpp>

int
main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainw;
    mainw.setWindowTitle("qartm");
    mainw.showMaximized();
    mainw.raise();

    QArtm::LoggingHub::setup(&mainw);

    qDebug() << "Program started";
    return app.exec();
}
