#include <QApplication>
#include <MainWindow.h>


#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	MainWindow iface;
	iface.show();

    return app.exec();
}
