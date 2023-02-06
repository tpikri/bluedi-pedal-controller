#ifndef DAWSTATUS_H
#define DAWSTATUS_H

#include <Arduino.h>

class DawStatus
{
    public:
    	static DawStatus* getInstance();

    	void setTrackName(int track, String name);
    	String getTrackName(int track);

    	void setSelectedTrack(int track);
    	int getSelectedTrack();
    	String getSelectedTrackName();

        void setTrackMuted(int track, bool muted);
        bool isTrackMuted(int track);

    	void setIsPlaying(bool onOff);
        void setIsRecording(bool onOff);
    	String getPlayingStatus();
    
    private:
		static DawStatus* inst_;
        DawStatus();
		DawStatus(const DawStatus&);
		DawStatus& operator=(const DawStatus&);

		bool isPlaying;
        bool isRecording;
		String trackNames[6];
        bool trackMute[6];
		int selectedTrack;
};

#endif