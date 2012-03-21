int
main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    QMainWindow mainw;
    mainw.setWindowTitle("qartm");
    mainw.showMaximized();
    mainw.raise();
    return app.exec();
}
