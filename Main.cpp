#include "StadiumTripPlanner.h"
#include "SetLogin.h"
#include "LoadStadiumFile.h"
#include "Settings.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if (!AppSettings.LoadCredentials())
		if ((new SetLogin)->exec() != QDialog::Accepted)
			return 0;

	if (!AppSettings.LoadStadiums())
		if ((new LoadStadiumFile)->exec() != QDialog::Accepted)
			return 0;

	(new StadiumTripPlanner)->show();

	return app.exec();
}
