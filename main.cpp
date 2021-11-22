#include <QApplication>
#include "midiplayer.hpp"


int main(int argc, char *argv[])
{
  // TODO
	QApplication app(argc, argv);

	MIDIPlayer player;

	player.show();

	return app.exec();
}
