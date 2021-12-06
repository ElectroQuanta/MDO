#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{	
	// Application instanciation
	QApplication app (argc, argv);

	// Creating the two buttons
 	QPushButton button1 ("test");
 	QPushButton button2 ("other", &button1);
	
	// Show button
 	button1.show();

 	// Exectution in loop of the application,
	// waiting for its events to trigger the functions
	return app.exec();
}
