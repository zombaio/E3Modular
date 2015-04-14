/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <memory>
#include "JuceHeader.h"
#include "e3_Profiler.h"
#include "core/GlobalHeader.h"
#include "core/ProfilerHelper.h"
#include "core/Settings.h"
#include "core/Sink.h"



namespace e3 {

    class Polyphony;
    class Bank;
    class Instrument;

    //-----------------------------------------------------------------
    //
    //-----------------------------------------------------------------
    //
    class Processor : public AudioProcessor
    {
    public:
        Processor();
        ~Processor();

        Settings* getSettings()    { return &settings_; }
        Polyphony* getPolyphony()  { return polyphony_.get(); }

        void prepareToPlay(double sampleRate, int samplesPerBlock) override;

        void processBlock(AudioSampleBuffer&, MidiBuffer&) override;
        // temporary
        void juceProcessBlock(AudioSampleBuffer&, MidiBuffer&);

        AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override                                     { return true; }
        bool isPlugin() const;
                                                                           
        const String getName() const override                               { return JucePlugin_Name; }
                                                                           
        int getNumParameters() override                                     { return 0; }
        float getParameter(int) override                                    { return 0.0f;  }
        void setParameter(int, float) override                              {}
                                                                           
        const String getParameterName(int) override                         { return String(); }
        const String getParameterText(int) override                         { return String(); }

        const String getInputChannelName(int channelIndex) const override   { return String(channelIndex + 1); }
        const String getOutputChannelName(int channelIndex) const override  { return String(channelIndex + 1); }
        bool isInputChannelStereoPair(int) const override                   { return true; }
        bool isOutputChannelStereoPair(int) const override                  { return true; }

        bool acceptsMidi() const override                                   { return true; }
        bool producesMidi() const override                                  { return true; }
        bool silenceInProducesSilenceOut() const override                   { return false; }
        double getTailLengthSeconds() const override                        { return 0.0; }

        int getNumPrograms() override                                       { return 1; }
        int getCurrentProgram() override                                    { return 0; }
        void setCurrentProgram(int) override                                {}
        const String getProgramName(int) override                           { return String(); }
        void changeProgramName(int, const String&) override                 {}

        void getStateInformation(MemoryBlock& destData) override;
        void setStateInformation(const void* data, int sizeInBytes) override;

        void suspend();
        void resume();

        void releaseResources() override                                    {}


        //enum Parameters
        //{
        //    gainParam = 0,
        //    delayParam,

        //    totalNumParams
        //};

        float gain_ = 0.75;

    private:
        void loadBank();
        void loadInstrument(int hash=0);

        Settings settings_;
        
        Sink sink_;
        std::unique_ptr<Polyphony> polyphony_;
        std::unique_ptr<Bank> bank_;
        Instrument* instrument_ = nullptr;

        Synthesiser juceSynth_;  // temporary

        e3::common::Profiler profiler_;
        e3::ProfilerHelper profilerHelper_;

        CriticalSection lock_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Processor)
    };



    // temporary method. Will be removed when modular processing is implemented
    inline void Processor::juceProcessBlock(AudioSampleBuffer& audioBuffer, MidiBuffer& midiBuffer)
    {
        const int numSamples = audioBuffer.getNumSamples();
        int channel = 0;

        // Go through the incoming data, and apply our gain to it...
        for (channel = 0; channel < getNumInputChannels(); ++channel)
            audioBuffer.applyGain(channel, 0, numSamples, gain_);

        // and now get the synth to process these midi events and generate its output.
        //synth_.renderNextBlock(buffer, midiMessages, 0, numSamples);
        juceSynth_.renderNextBlock(audioBuffer, midiBuffer, 0, numSamples);
    }


}  // namespace e3