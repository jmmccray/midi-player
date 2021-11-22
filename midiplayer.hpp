#ifndef MIDIPLAYER_HPP
#define MIDIPLAYER_HPP


//#include //synthesizer, QPUshButton, QLineEidt, QSlider, QAudioOutput, QIODevice,

// define class MIDIPlayer here
#include "message_queue.hpp"
#include "synthesizer.hpp"
#include <thread>
#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QAudioOutput>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMessageBox>


using namespace std;

// TODO 
class MIDIPlayer : public QWidget {
	Q_OBJECT

private slots:
	void PlayButton();
	void MuteButton();
	void PauseButton();
	void StopButton();
	void volumeChanged();
	void getMIDIInputFile();
	void handleNotify();
	
public:
	
	MIDIPlayer(QWidget * parent = nullptr);
	~MIDIPlayer();
	void audioGenerator();


private:
	void DefaultState();

	QMessageBox * messageBox_;
	QLineEdit * midiInputLine_;
	QString inputMIDIFilePath_;
	QPushButton * playButton_;
	QPushButton * pauseButton_;
	QPushButton * stopButton_;
	QLabel * volume_;
	QSlider * volumeSlide_;
	QPushButton * muteButton_;
	QPushButton * midiBrowseBtn_;
	

	TrackListType listOfTracks_;
	Signal sample_signal_;
	MessageQueue * messageQueue_;
	SharedDoubleBuffer * doubleBuffer_;
	Synthesizer * synthesizer_;
	std::thread* synthThread_;

	enum MessageID{Default, Play, Pause, Stop, Mute, Kill} messageID_;

	QAudioOutput * audio_;
	bool ON_OFF;
	QIODevice * device;
	std::size_t buffer_size;
	std::vector<char> buffer;
	bool muted_ = true;
	int savedVolume_;

	//SharedDoubleBuffer buffer_;

};



#endif
