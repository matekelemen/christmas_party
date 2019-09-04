#include "state.hpp"

// -----------------------------------------------------------------------------------
// STATES
// -----------------------------------------------------------------------------------
double SaturationState::conduct(){
    return (transistor_->collectorVoltage() - transistor_->emitterVoltage()) / transistor_->internalResistance();
}

double CutoffState::conduct(){
    return 0.0;
}

double ActiveState::conduct(){
    double maxCurrent = (transistor_->collectorVoltage()-transistor_->emitterVoltage())/transistor_->internalResistance();
    return (transistor_->baseVoltage()- transistor_->emitterVoltage())/transistor_->collectorVoltage() * maxCurrent;
}

double ReverseActiveState::conduct(){
    double maxCurrent = (transistor_->collectorVoltage()-transistor_->emitterVoltage())/transistor_->internalResistance();
    return -(transistor_->baseVoltage()- transistor_->emitterVoltage())/transistor_->collectorVoltage() * maxCurrent;
}

// -----------------------------------------------------------------------------------
// TRANSISTOR
// -----------------------------------------------------------------------------------
NPNTransistor::NPNTransistor(double internalResistance) : 
    states_({
                {"SaturationState",     new SaturationState(this)},
                {"CutoffState",         new CutoffState(this)},
                {"ActiveState",         new ActiveState(this)},
                {"ReverseActiveState",  new ReverseActiveState(this)}
            }),
    currentState_(states_["CutoffState"]),
    internalResistance_(internalResistance), 
    baseCurrent_(0),
    baseVoltage_(0),
    collectorVoltage_(0),
    emitterVoltage_(0)
{
    setState();
}


void NPNTransistor::setState(){
    std::string newState="";
    // Determine state
    if(baseVoltage_<=collectorVoltage_ && baseVoltage_<=emitterVoltage_){
        newState = "CutoffState";
    }
    else if (emitterVoltage_<=baseVoltage_ && baseVoltage_<=collectorVoltage_){
        newState = "ActiveState";
    }
    else if (collectorVoltage_<=baseVoltage_ && baseVoltage_<=emitterVoltage_){
        newState = "ReverseActiveState";
    }
    else if (emitterVoltage_<=baseVoltage_ && collectorVoltage_<=baseVoltage_){
        newState = "SaturationState";
    }
    // Set new state if necessary
    if (states_[newState] != currentState_ && newState!=""){
        std::cout << "Switching to " << newState << "\n";
        currentState_ = states_[newState];
    }
}


double NPNTransistor::conduct(){
    setState();
    return currentState_->conduct();
}


// -----------------------------------------------------------------------------------
// MAIN
// -----------------------------------------------------------------------------------
int main(){

    double internalResistance=1.0;
    NPNTransistor transistor(internalResistance);
    
    transistor.setCollectorVoltage(8.0);
    transistor.setEmitterVoltage(2.0);
    
    transistor.setBaseCurrent(1.0);
    for (int i=0;i<11;++i){
        transistor.setBaseVoltage((double)i);
        std::cout << transistor.conduct() << std::endl;
    }
    return 0;
}