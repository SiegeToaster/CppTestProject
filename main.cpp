#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv) {
 QApplication app (argc, argv);
 QWidget window;
 window.setFixedSize(720, 480);

 QPushButton *button = new QPushButton("wee woo", &window);
 QPushButton *button2 = new QPushButton("other", &window);
 button->setGeometry(360-40, 240-15, 80, 30); // 1st is windowWidth/2 - buttonWidth/2; 2nd is same but with height
 button2->setGeometry(400, 240-15, 80, 30);
 window.show();

 return app.exec();
}

// https://wiki.qt.io/Qt_for_Beginners
