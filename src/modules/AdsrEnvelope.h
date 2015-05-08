
#pragma once

#include <string>
#include "core/Module.h"

namespace e3 {

    class AdsrEnvelope : public Module
    {
    public:
        AdsrEnvelope();

        ParameterSet& getDefaultParameters() const override;
        void initData() override;

        void processAudio() throw();
        void processControl() throw() override;

        void setParameter(int paramId, double value, double modulation=0.f, int voice=-1) override;
        void setSentinel(bool sentinel) { sentinel_ = sentinel; }

        enum ParamId {                 // TODO: can ParamId's be protected?
            ParamAudioIn  = 0,         // TODO: what's the use?
            ParamGate     = 1,
            ParamAttack   = 2,
            ParamDecay    = 3,
            ParamSustain  = 4,
            ParamRelease  = 5,
            ParamNumParams
        };

    protected:  
        void keyOn(double amplitude,int voice);
        void keyOff(int voice);

        void setSampleRate(double sampleRate);

        // ranges for all times: 0-1, 1=10sec
        void setAttackRate( double time, int voice=-1 );
        void setDecayRate( double time, int voice=-1 );
        void setSustainLevel( double level, int voice=-1 );
        void setReleaseRate( double time, int voice=-1 );
        
        double calcRate( double time );

        std::string debugLabel_ = "AdsrEnvelope";

        Buffer<double> valueBuffer_, targetBuffer_, deltaBuffer_, velocityBuffer_;
        double *value_, *target_, *delta_, *velocity_;

        Buffer<double> attackRateBuffer_, decayRateBuffer_, sustainLevelBuffer_, releaseRateBuffer_;
        double* attackRate_   = nullptr;
        double* decayRate_    = nullptr; 
        double* sustainLevel_ = nullptr;
        double* releaseRate_  = nullptr;

        Buffer<int16_t> stateBuffer_;
        int16_t* state_;

        bool sentinel_ = false;

        Inport audioInport_;
        Outport audioOutport_;
        Inport gateInport_;
        double* audioInportPointer_ = nullptr;

        enum State {
            StateAttack,
            StateDecay,
            StateSustain,
            StateRelease,
            StateDone    
        };
    };
} // namespace e3