#include <QTest>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>

#include "midiplayer.hpp"

class TestMIDIPlayer : public QObject {
  Q_OBJECT

private slots:

  void initTestCase();

  // TODO: add your tests
  void compareTest();
  void buttonsTest();
  void errorMessagesTest();
  
private:

  MIDIPlayer widget;
};

void TestMIDIPlayer::initTestCase(){

  {
	widget.show();
	QTest::qWait(2000);
    auto w = widget.findChild<QLineEdit *>("inputpath");
    QVERIFY2(w, "Could not find a QLineEdit widget");
  }

  {
    auto w = widget.findChild<QPushButton *>("play");
    QVERIFY2(w, "Could not find play button");
  }

  {
    auto w = widget.findChild<QPushButton *>("pause");
    QVERIFY2(w, "Could not find pause button");
  }
  
  {
    auto w = widget.findChild<QPushButton *>("stop");
    QVERIFY2(w, "Could not find stop button");
  }

  {
    auto w = widget.findChild<QSlider *>("volume");
    QVERIFY2(w, "Could not find volume slider");
  }
  
  {
    auto w = widget.findChild<QPushButton *>("mute");
    QVERIFY2(w, "Could not find mute button");
  }
}


//Tests Buttons
void TestMIDIPlayer::buttonsTest() //Maybe state test?
{
	//Test if buttons work...say like hey if Play is pressed, then Play should be enabled, Mute should be enabled, and so on.
	widget.show();
	QTest::qWait(1000);
	//When Play Is Pressed, Play Button (false), mute Button (true) etc
	auto inputFilePath = widget.findChild<QLineEdit*>("inputpath");
	auto browseButton = widget.findChild<QPushButton*>("browse");
	auto playButton = widget.findChild<QPushButton*>("play");
	auto pauseButton = widget.findChild<QPushButton*>("pause");
	auto stopButton = widget.findChild<QPushButton*>("stop");
	auto muteButton = widget.findChild<QPushButton*>("mute");
	auto volumeSlider = widget.findChild<QSlider*>("volume");

	//PLAYS EVERY SOUND FILE
	inputFilePath->setText("/vagrant/test/test0.mid");
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test0.mid");
	QTest::mouseClick(playButton, Qt::LeftButton);
	QTest::qWait(5000); //Waits 6 seconds
	QTest::mouseClick(stopButton, Qt::LeftButton);
	QTest::qWait(1000);
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test1.mid");
	inputFilePath->setText("/vagrant/test/test1.mid");
	QTest::mouseClick(playButton, Qt::LeftButton);
	QTest::qWait(5000); //Waits 6 seconds
	QTest::mouseClick(stopButton, Qt::LeftButton);
	QTest::qWait(1000);
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test2.mid");
	inputFilePath->setText("/vagrant/test/test2.mid");
	QTest::mouseClick(playButton, Qt::LeftButton);
	QTest::qWait(5000); //Waits 6 seconds
	QTest::mouseClick(stopButton, Qt::LeftButton);
	QTest::qWait(1000);
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test3.mid");
	inputFilePath->setText("/vagrant/test/test3.mid");
	QTest::mouseClick(playButton, Qt::LeftButton);
	QTest::qWait(4000); //Waits 6 seconds
	QTest::mouseClick(stopButton, Qt::LeftButton);
	QTest::qWait(1000);
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test4.mid");
	inputFilePath->setText("/vagrant/test/test4.mid");
	QTest::mouseClick(playButton, Qt::LeftButton);
	QTest::qWait(5000); //Waits 6 seconds
	QTest::mouseClick(stopButton, Qt::LeftButton);
	QTest::qWait(500);	 
	
	//Check States
	cout << "Checking States..." << endl;

///////Play Button Pressed//////////////

	inputFilePath->setText("/vagrant/test/test3.mid");
	//inputFilePath->setText("C:/ECE3574/project3-jmmccray/build/Debug/test3.mid");
	
	//PASSES in Visual Studio
	/*QVERIFY(!browseButton->isEnabled());
	QVERIFY(!playButton->isEnabled());
	QVERIFY(pauseButton->isEnabled());
	QVERIFY(stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled()); //causes an error!
	QTest::qWait(1000);*/	
	
	//PASSES in Vagrant
	QTest::mouseClick(playButton, Qt::LeftButton);
	cout << "$$$ PLAY Values $$$" << endl;
	cout << "Browse: " << browseButton->isEnabled() << endl;
	cout << "Play: " << playButton->isEnabled() << endl;
	cout << "Pause: " << pauseButton->isEnabled() << endl;
	cout << "Stop: " << stopButton->isEnabled() << endl;
	cout << "Slider: " << volumeSlider->isEnabled() << endl;
	cout << "Mute: " << muteButton->isEnabled() << endl;
	QVERIFY(!browseButton->isEnabled());
	QVERIFY(!playButton->isEnabled());
	QVERIFY(pauseButton->isEnabled());
	QVERIFY(stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled()); //causes an error!
	QTest::qWait(1000);
	
///////Pause Button Pressed///////////

	//PASSES in Visual Studio
	/*QTest::mouseClick(pauseButton, Qt::LeftButton);
	QVERIFY(!browseButton->isEnabled());
	QVERIFY(playButton->isEnabled());
	QVERIFY(!pauseButton->isEnabled());
	QVERIFY(stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled());
	QTest::qWait(1000);*/

	

	QTest::mouseClick(pauseButton, Qt::LeftButton);
	cout << "$$$ PAUSE Values $$$" << endl;
	cout << "Browse: " << browseButton->isEnabled() << endl;
	cout << "Play: " << playButton->isEnabled() << endl;
	cout << "Pause: " << pauseButton->isEnabled() << endl;
	cout << "Stop: " << stopButton->isEnabled() << endl;
	cout << "Slider: " << volumeSlider->isEnabled() << endl;
	cout << "Mute: " << muteButton->isEnabled() << endl;
	QVERIFY(!browseButton->isEnabled());
	QVERIFY(playButton->isEnabled());
	QVERIFY(!pauseButton->isEnabled());
	QVERIFY(stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled());
	QTest::qWait(1000);

///////Stop Button Presssed////////////

	//PASSES IN Visual Studio!
	/*QTest::mouseClick(pauseButton, Qt::LeftButton);
	QVERIFY(!browseButton->isEnabled());
	QVERIFY(playButton->isEnabled());
	QVERIFY(!pauseButton->isEnabled());
	QVERIFY(stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled());
	QTest::qWait(1000);*/

	

	QTest::mouseClick(stopButton, Qt::LeftButton);
	cout << "$$$ STOP Values $$$" << endl;
	cout << "Browse: " << browseButton->isEnabled() << endl;
	cout << "Play: " << playButton->isEnabled() << endl;
	cout << "Pause: " << pauseButton->isEnabled() << endl;
	cout << "Stop: " << stopButton->isEnabled() << endl;
	cout << "Slider: " << volumeSlider->isEnabled() << endl;
	cout << "Mute: " << muteButton->isEnabled() << endl;
	QVERIFY(browseButton->isEnabled());
	QVERIFY(playButton->isEnabled());
	QVERIFY(!pauseButton->isEnabled());
	QVERIFY(!stopButton->isEnabled());
	QVERIFY(volumeSlider->isEnabled());
	QVERIFY(muteButton->isEnabled());
	QTest::qWait(1000);
	
///////Mute Button Pressed//////////////

	//PASSES IN Visual Studio
	/*QTest::mouseClick(muteButton, Qt::LeftButton); //Mute
	QVERIFY(muteButton->isEnabled());
	QVERIFY(!volumeSlider->isEnabled());
	QTest::mouseClick(muteButton, Qt::LeftButton); //Unmute
	QVERIFY(volumeSlider->isEnabled());
	QTest::qWait(1000);*/
	QTest::mouseClick(muteButton, Qt::LeftButton); //Mute
	cout << "$$$ MUTE Values $$$" << endl;
	cout << "Slider: " << volumeSlider->isEnabled() << endl;
	cout << "Mute: " << muteButton->isEnabled() << endl;
	QVERIFY(muteButton->isEnabled());
	QVERIFY(!volumeSlider->isEnabled());
	QTest::mouseClick(muteButton, Qt::LeftButton); //Unmute
	QVERIFY(volumeSlider->isEnabled());
	QTest::qWait(1000);

}

//Test whether WAV Output to Test Output
void TestMIDIPlayer::compareTest()
{
	
}



void TestMIDIPlayer::errorMessagesTest()
{
//Test if Error messages are called 

}

QTEST_MAIN(TestMIDIPlayer)
#include "test_midiplayer.moc"




//QVERIFY2(!browseButton->isChecked(), "Browse Button is not disabled");
//QVERIFY2(!playButton->isChecked(), "Play Button is not disabled");
//QVERIFY2(!pauseButton->isChecked(), "Pause Button is not enabled");
//QVERIFY2(stopButton->isChecked(), "Stop Button is not enabled");
//QVERIFY2(volumeSlider->isEnabled(), "Volume Slider is not enabled");
//QVERIFY2(!pauseButton->isChecked(), "Pause Button is not enabled");