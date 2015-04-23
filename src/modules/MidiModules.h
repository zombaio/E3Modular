
#pragma once

#include "core/Module.h"


namespace e3 {
    class Polyphony;

    class MidiGate : public Module 
    {
    public:
        MidiGate();

        void initSignals() override;
        void resetSignals() override;
        void onMidiGate( double gate, uint16_t voice);

    protected:
        EventOutport gateOutport_;
    };

    class MidiPitch : public Module 
    {
    public:
        MidiPitch();
        MidiPitch(
            ModuleType moduleType,
            const std::string& label,
            VoicingType voicingType,
            ProcessingType processingType);

        void initSignals() override;
        void resetSignals() override;

        void initVoices() override;
        void setParameter( uint16_t paramId, double value, double modulation=0.f, int16_t voice=-1 );
        void onMidiNote( double pitch, double gate, uint16_t voice );
        void onMidiPitchbend(int value);
        
        void processControl() throw() override;

    protected:
        void createParameters();
        void calcGlide( double freq, uint16_t voice );
        void setGlideTime( double time );

        enum Params { 
            kParamBendRange  = 0,
            kParamGlideTime  = 1,
            kParamGlideAuto  = 2,
        };

        Buffer< double > glideDeltaBuffer_, glideTargetBuffer_, freqBuffer_;

        double* freq_        = nullptr;
        double* glideTarget_ = nullptr;
        double* glideDelta_  = nullptr;

        double glideFrames_  = 0;
        bool glideAuto_      = true;

        double bendFactor_   = 1.0;
        int16_t bendRange_   = 2;

        EventOutport freqOutport_;
    };


    class MidiInput : public MidiPitch
    {
    public:
        MidiInput();

        void initSignals() override;
        void resetSignals() override;
        void onMidiNote(double pitch, double gate, uint16_t voice);

    protected:
        EventOutport gateOutport_;
    };

}
