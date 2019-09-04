#include <string>
#include <map>
#include <iostream>


class NPNTransistor;


// -----------------------------------------------------------------------------------
// STATES
// -----------------------------------------------------------------------------------
class NPNTransistorState {
    protected:
        NPNTransistor* transistor_;
    public:
        NPNTransistorState(NPNTransistor* transistor) : transistor_(transistor){}
        virtual double conduct()=0;
};


class SaturationState : public NPNTransistorState {
    public:
        SaturationState(NPNTransistor* transistor) : NPNTransistorState(transistor){}
        double conduct();
};


class CutoffState : public NPNTransistorState {
    public:
        CutoffState(NPNTransistor* transistor) : NPNTransistorState(transistor){}
        double conduct();
};


class ActiveState : public NPNTransistorState {
    public:
        ActiveState(NPNTransistor* transistor) : NPNTransistorState(transistor){}
        double conduct();
};


class ReverseActiveState : public NPNTransistorState {
    public:
        ReverseActiveState(NPNTransistor* transistor) : NPNTransistorState(transistor){}
        double conduct();
};

// -----------------------------------------------------------------------------------
// TRANSISTOR
// -----------------------------------------------------------------------------------
class NPNTransistor {
    private:
        std::map<std::string,NPNTransistorState*> states_;
        NPNTransistorState* currentState_;
        double internalResistance_;
        double baseCurrent_;
        double baseVoltage_;
        double collectorVoltage_;
        double emitterVoltage_;
    public:
        NPNTransistor(double internalResistance);

        void setState();
        double conduct();

        void setBaseCurrent(double current) {baseCurrent_ = current;}
        void setBaseVoltage(double voltage) {baseVoltage_ = voltage;}
        void setCollectorVoltage(double voltage) {collectorVoltage_ = voltage;}
        void setEmitterVoltage(double voltage) {emitterVoltage_ = voltage;}

        double baseCurrent() {return baseCurrent_;}
        double internalResistance() {return internalResistance_;}
        double baseVoltage() {return baseVoltage_;}
        double collectorVoltage() {return collectorVoltage_;}
        double emitterVoltage() {return emitterVoltage_;}
};