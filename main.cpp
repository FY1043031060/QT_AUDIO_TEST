#include <QApplication>
#include <QSoundEffect>
#include <Form.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form m;
    m.show();
    return a.exec();
}
