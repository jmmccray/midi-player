#include "midiplayer.hpp"
#include "synthesizer.hpp" //Track and Signal implemented in this header
#include "midi.hpp"


#include <QGridLayout>
#include <QObject>
#include <QDebug>
#include <QGroupBox>
#include <QString>
#include <QFileDialog>
#include <QAudioDeviceInfo>
#include <QAudioInput>

// Implement class MIDIPlayer here
//button->setFlat(bool flag)


void MIDIPlayer::getMIDIInputFile()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	inputMIDIFilePath_ = dialog.getOpenFileName(this, "Open Document", QDir::currentPath(), "MIDI files (*.mid)");
	midiInputLine_->setText(inputMIDIFilePath_);
	QFileInfo info(inputMIDIFilePath_);
	inputMIDIFilePath_ = info.fileName();
	cout << "Input MIDIPath: " << inputMIDIFilePath_.toStdString() << endl;
	qDebug() << inputMIDIFilePath_;

}

void MIDIPlayer::DefaultState()
{
	/*playButton_->setEnabled(false);
	pauseButton_->setEnabled(false);
	stopButton_->setEnabled(false);
	midiBrowseBtn_->setEnabled(true);
	muteButton_->setEnabled(false);*/
	messageID_ = Default;
	messageQueue_->push(messageID_);
}

//Play Button State
void MIDIPlayer::PlayButton()
{
	//Send Message to Queue
	if (midiInputLine_->text().isEmpty())
	{
		messageBox_->setText("You Must Input a MIDI File.");
		messageBox_->exec();

	}
	else
	{
		audio_->resume();
		playButton_->setEnabled(false);
		pauseButton_->setEnabled(true);
		stopButton_->setEnabled(true);
		midiBrowseBtn_->setEnabled(false);

		if (!ON_OFF)
		{
			//audio_->resume();
			pauseButton_->setEnabled(true);
			ON_OFF = true;
		}
		else
		{
			playButton_->setEnabled(false);
			pauseButton_->setEnabled(true);
			stopButton_->setEnabled(true);
			midiBrowseBtn_->setEnabled(false);
			//muteButton_->setEnabled(true);
			//audio_->resume();
			//Gets MIDI File from QLineEdit
			string filename = inputMIDIFilePath_.toStdString(); 
			//cout << "Filename: " << filename << endl;
			 filename = midiInputLine_->text().toStdString();
			//cout << "Filename: " << filename << endl;
			synthesizer_->getMIDIFile(filename);
			messageID_ = Play;
			messageQueue_->push(messageID_);
		}
	}
}

//Mute Button State
void MIDIPlayer::MuteButton()
{
	//mute_ initially = true	
	if (muted_)
	{
		//cout << "Muted" << endl;
		savedVolume_ = volumeSlide_->value();
		volumeSlide_->setValue(0);
		audio_->setVolume((double) volumeSlide_->value() / 100.0);
		volumeSlide_->setEnabled(false);
		muteButton_->setText("Unmute");//Rename Mute Button to "UnMute"
		muted_ = false;
	}
	else
	{
		//cout << "Unmuted" << endl;
		muteButton_->setText("Mute");
		volumeSlide_->setValue(savedVolume_);
		audio_->setVolume((double) volumeSlide_->value() / 100.0);
		volumeSlide_->setEnabled(true);
		cout << "Unmuted Vol: " << volumeSlide_->value() << endl;
		muted_ = true;
	}
	//cout << "Mute Button Clicked" << endl;


}

//Pause Button State
void MIDIPlayer::PauseButton()
{
	pauseButton_->setEnabled(false);
	playButton_->setEnabled(true);
	stopButton_->setEnabled(true);
	messageID_ = Pause;
	messageQueue_->push(messageID_);

	//Pause Audio
	audio_->suspend();
	ON_OFF = false; // FALSE = OFF/Pause
	//cout << "Pause Button Clicked" << endl; //Debugging 
}


//Stop Button State
void MIDIPlayer::StopButton()
{
	stopButton_->setEnabled(false);
	pauseButton_->setEnabled(false);
	playButton_->setEnabled(true);
	midiBrowseBtn_->setEnabled(true);
	doubleBuffer_->clearBuffers();
	messageID_ = Stop;
	messageQueue_->push(messageID_);

	//audio_->reset();
	//audio_->setBufferSize(80000);
	//audio_->suspend();
	ON_OFF = true;
	cout << "Stop Button Clicked" << endl;
}

void MIDIPlayer::volumeChanged()
{
	audio_->setVolume((double) volumeSlide_->value()/100);
}

 void MIDIPlayer::handleNotify()
{
	// cout << "HandleNotify() called..." << endl;
		/*int bytesFree = audio_->bytesFree();
		int samplesToWrite = bytesFree > doubleBuffer_->getWriteBufferSize() ? doubleBuffer_->getWriteBufferSize() : bytesFree;
		//int bytesToWrite = bytesFree > buffer_size ? buffer_size : bytesFree;
		//int samplesToWrite = bytesToWrite * 2;
		//int samplesToWrite = bytesToWrite >> 1;
		int bytesToWrite = 2 * samplesToWrite;
		
		//buffer.reserve(samplesToWrite);*/

	 int bytesFree = audio_->bytesFree();
	 int bytesToWrite = bytesFree > buffer_size ? buffer_size : bytesFree;
	 int samplesToWrite = bytesToWrite >> 1;
	 bytesToWrite = 2 * samplesToWrite;



		buffer.reserve(bytesToWrite);


		double sample = 0.0;
		for (int i = 0; i <samplesToWrite; ++i)
		{
			sample = doubleBuffer_->readFromBuffer(); //samples = doubleBuffer->popFromRead();
			int16_t temp = static_cast<int16_t>(sample); //normalize it.
			char *byte1 = reinterpret_cast<char *>(&temp);
			char *byte2 = ++byte1;
			buffer.push_back(*byte1);
			buffer.push_back(*byte2);
		}

		if (bytesToWrite > 0) 
		{
			device->write(buffer.data(), bytesToWrite);
		}
		buffer.clear();
}

 void MIDIPlayer::audioGenerator()
{
	  //Audio 	
	cout << endl;
	cout << "Calls Audio Generator...";

		 //NOISE GENERATOR
		 QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
		 auto rates = info.supportedSampleRates();

		 int sampleRate = rates.at(0);
		 for (int i = 1; i < rates.size(); ++i) 
		 {
			 if (rates.at(i) < sampleRate)
				 sampleRate = rates.at(i);
		 }

		 QAudioFormat format;
		 format.setSampleRate(sampleRate);
		 format.setChannelCount(1);
		 format.setSampleSize(16);
		 format.setCodec("audio/pcm");
		 format.setByteOrder(QAudioFormat::LittleEndian);
		 format.setSampleType(QAudioFormat::SignedInt);

		 if (!info.isFormatSupported(format)) 
		 {
			 qWarning()	 << "Raw audio format not supported by backend, cannot play audio.";
		 }
		 else 
		 {
			 /*audio_ = new QAudioOutput(format, this);
			 audio_->setBufferSize(50000);
			 connect(audio_, SIGNAL(notify()), this, SLOT(handleNotify()));
			 //buffer_size = buffer_size > 0 ? buffer_size : 1024;
			 buffer_size = 50000;
			 audio_->setNotifyInterval(25); //Milliseconds, checks		
			 audio_->setVolume(1);
			 device = audio_->start();
			 handleNotify();*/

			 audio_ = new QAudioOutput(format);
			 connect(audio_, SIGNAL(notify()), this, SLOT(handleNotify()));
			 buffer_size = audio_->bufferSize();
			 buffer_size = buffer_size > 0 ? buffer_size : 80000;
			 audio_->setNotifyInterval(1); //Milliseconds, checks		
			 audio_->setVolume(1);
			 device = audio_->start();
			 handleNotify();
		 }
}


MIDIPlayer::MIDIPlayer(QWidget * parent) : QWidget(parent)
{	
	messageQueue_ = new MessageQueue;
	doubleBuffer_ = new SharedDoubleBuffer(70000);
	synthesizer_ = new Synthesizer;
	messageBox_ = new QMessageBox;
	
	synthThread_ = new std::thread(&Synthesizer::synthesize, synthesizer_, messageQueue_, doubleBuffer_);
	audioGenerator();

	QVBoxLayout * mainLayout = new QVBoxLayout; //could probably set grid
	QGroupBox * MIDIInputGroup = new QGroupBox(tr("MIDI Input"), this);
	QGroupBox * AudioConGroup = new QGroupBox(tr("Audio Controls"), this);

	//MIDI Group
	QHBoxLayout * midiLayout = new QHBoxLayout;
	midiInputLine_ = new QLineEdit(this);
	midiBrowseBtn_ = new QPushButton(tr("Browse"), this);
	midiInputLine_->setObjectName("inputpath");
	midiBrowseBtn_->setObjectName("browse");
	midiLayout->addWidget(midiInputLine_);
	midiLayout->addWidget(midiBrowseBtn_);
	MIDIInputGroup->setLayout(midiLayout);

	//AUDIO Group
	QGridLayout * audioLayout = new QGridLayout;
	playButton_ = new QPushButton(tr("Play"), this);
	pauseButton_ = new QPushButton(tr("Pause"), this);
	stopButton_ = new QPushButton(tr("Stop"), this);
	volume_ = new QLabel(tr("Volume: "), this);
	volumeSlide_ = new QSlider(Qt::Horizontal, this);
		volumeSlide_->setMinimum(0);
		volumeSlide_->setMaximum(100);
		volumeSlide_->setValue(50);
	muteButton_ = new QPushButton(tr("Mute"), this); 
	playButton_->setObjectName("play");
	pauseButton_->setObjectName("pause");
	stopButton_->setObjectName("stop");
	volumeSlide_->setObjectName("volume");
	muteButton_->setObjectName("mute");
	playButton_->setEnabled(true);
	pauseButton_->setEnabled(false);
	stopButton_->setEnabled(false);
	midiBrowseBtn_->setEnabled(true);
	muteButton_->setEnabled(true);
	volumeSlide_->setEnabled(true);
	audioLayout->addWidget(playButton_, 0, 0); //(widget, row, column)
	audioLayout->addWidget(pauseButton_, 0, 1);
	audioLayout->addWidget(stopButton_, 0, 2);
	audioLayout->addWidget(volume_, 1, 0);
	audioLayout->addWidget(volumeSlide_, 1, 1);
	audioLayout->addWidget(muteButton_, 1, 2);
	audioLayout->setHorizontalSpacing(50);
	audioLayout->setVerticalSpacing(50);
	AudioConGroup->setLayout(audioLayout);

	mainLayout->addWidget(MIDIInputGroup);
	mainLayout->addWidget(AudioConGroup);
	mainLayout->setSpacing(50);

	DefaultState();
	//SETUP CONNECTIONS
	QObject::connect(midiBrowseBtn_, SIGNAL(clicked()), this, SLOT(getMIDIInputFile())); //Create separate slots
	//Create connection signal and slot, for when "Enter" is pressed on QLineEdit to call PlayButton()
	QObject::connect(playButton_, SIGNAL(clicked()),this,  SLOT(PlayButton()));
	QObject::connect(pauseButton_, SIGNAL(clicked()), this, SLOT(PauseButton()));
	QObject::connect(stopButton_, SIGNAL(clicked()), this, SLOT(StopButton()));
	QObject::connect(volumeSlide_, SIGNAL(valueChanged(int)), this, SLOT(volumeChanged()));
	QObject::connect(muteButton_, SIGNAL(clicked()), this, SLOT(MuteButton()));

	setLayout(mainLayout);
	setWindowTitle(tr("Thread Synthesizer"));
}

MIDIPlayer::~MIDIPlayer()
{

	//send a quite message to the SYNTHESIZER
	//wait for the synthesizer thread to terminate usinga join()
	//delete the Synthesizer adn QAudioOutput, MessageQueue, SharedDouble objects?
	//Pointers: synthesizer_ | synthThread_ | audio_ | messageQueue_ | doubleBuffer_ | device
	messageID_ = Kill;
	messageQueue_->push(messageID_);
	synthThread_->join();
	//delete synthThread_;
	delete synthesizer_;
	//delete audio_;
	//delete messageQueue_;
	//delete doubleBuffer_;
	//device = nullptr;
}
