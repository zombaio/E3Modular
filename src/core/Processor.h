/*
  ==============================================================================

  This file was auto-generated by the Introjucer!

  It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
  */

#pragma once

#include <string>

#include "JuceHeader.h"
#include "core/GlobalHeader.h"


namespace e3 {

    class CpuMeter;
    class Polyphony;
    class Database;
    class Instrument;
    class Sink;
    class Module;
    class Link;

    enum ProcessorState {
        ProcessorNotInitialized = 0,
        ProcessorReady          = 1,
        ProcessorSuspended      = 2,
        ProcessorCrashed        = 3,
    };


    //-----------------------------------------------------------------
    //
    //-----------------------------------------------------------------
    //
    class Processor : public AudioProcessor
    {
    public:
        Processor();
        ~Processor();

        Polyphony* getPolyphony()  { return polyphony_.get(); }

        void prepareToPlay( double sampleRate, int samplesPerBlock ) override;
        void releaseResources() override;
        void processBlock( AudioSampleBuffer&, MidiBuffer& ) override;

        AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override                                     { return true; }
        bool isPlugin() const;

        const String getName() const override                               { return JucePlugin_Name; }

        int getNumParameters() override                                     { return 0; }
        float getParameter( int ) override                                    { return 0.0f; }
        void setParameter( int, float ) override                              {}

        const String getParameterName( int ) override                         { return String(); }
        const String getParameterText( int ) override                         { return String(); }

        const String getInputChannelName( int channelIndex ) const override   { return String( channelIndex + 1 ); }
        const String getOutputChannelName( int channelIndex ) const override  { return String( channelIndex + 1 ); }
        bool isInputChannelStereoPair( int ) const override                   { return true; }
        bool isOutputChannelStereoPair( int ) const override                  { return true; }

        bool acceptsMidi() const override                                     { return true; }
        bool producesMidi() const override                                    { return true; }
        bool silenceInProducesSilenceOut() const override                     { return false; }
        double getTailLengthSeconds() const override                          { return 0.0; }
                                                                          
        int getNumPrograms() override                                         { return 1; }
        int getCurrentProgram() override                                      { return 0; }
        void setCurrentProgram( int ) override                                {}
        const String getProgramName( int ) override                           { return String(); }
        void changeProgramName( int, const String& ) override                 {}

        void getStateInformation( MemoryBlock& destData ) override;
        void setStateInformation( const void* data, int sizeInBytes ) override;

        bool suspend();
        void resume( bool nested = false );

        void loadBank( const std::string& path );
        void newBank();
        void saveBank( const std::string& path = "" );
        void loadInstrument( int id = -1, bool saveCurrent = true );
        void loadInstrument( const std::string& path, bool saveCurrent = true );

        bool addLink( Link& link );
        void removeLink( const Link& link );

        Module* addModule( int moduleType );
        void deleteModule( Module* module );

        Instrument* getInstrument() const   { return instrument_; }
        XmlElement* getDatabaseXml() const;

        void setInstrumentAttributes( const std::string& name, const var& value );
        void setInstrumentAttribute( int instrumentId, const std::string& name, const var& value );

        Gallant::Signal2<int, int> midiControllerSignal;

    private:
        void initInstrument();
        void resetAndInitInstrument();
        void setNumVoices( int numVoices );
        void setState( ProcessorState state );


        Sink* sink_ = nullptr;
        ScopedPointer<Database> database_;
        ScopedPointer<Polyphony> polyphony_;
        ScopedPointer<Instrument> instrument_;
        ScopedPointer<CpuMeter> cpuMeter_;

        ProcessorState state_ = ProcessorNotInitialized;
        CriticalSection lock_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( Processor )
    };

}  // namespace e3