#include "observer.hpp"

// ------------------------------------------------------------------
// SUBJECT
// ------------------------------------------------------------------
Screen::Screen() : 
                    size_({800,600}),
                    states_({ 
                        { "enableMouse", true },
                        { "enableKeyboard", true } 
                        })
{   
}


Screen::~Screen(){
    for (auto it=observers_.begin();it!=observers_.end();++it){
        delete *it;
    }
}


void Screen::wakeUp(){
    std::cout << "Waking up Screen...\n";
    // Set all states to true
    for (auto it=states_.begin(); it!=states_.end(); ++it){
        it->second = true;
    }
    onChange();
}


void Screen::sleep(){
    std::cout << "Putting Screen to sleep...\n";
    states_["enableMouse"]    = false;
    states_["enableKeyboard"] = true;
    onChange();
}


void Screen::attach(Observer* observer){
    std::cout << "Attaching new Observer to Screen...\n";
    observers_.push_back(observer);
    onChange();
}


void Screen::onChange(){
    if (observers_.size()>0){
        for (auto it=observers_.begin(); it!=observers_.end(); ++it){
            (*it)->onSubjectChange();
        }
    }
}

// -----------------------------------------------------------------
// OBSERVERS
// -----------------------------------------------------------------
void Mouse::onSubjectChange(){
    bool newState = query();

    if (newState != state_){
        state_ = newState;
        std::string message;
        if (newState) message = "enabled";
        else message = "disabled";
        std::cout << "Mouse state changed to: " << message << std::endl;
    }
}


bool Mouse::query(){
    std::cout << "Mouse queried Screen\n";
    return subject_->getState("enableMouse");
}


void Keyboard::onSubjectChange(){
    bool newState = query();

    if (newState != state_){
        state_ = newState;
        std::string message;
        if (newState) message = "enabled";
        else message = "disabled";
        std::cout << "Keyboard state changed to: " << message << std::endl;
    }
}


bool Keyboard::query(){
    std::cout << "Keyboard queried Screen\n";
    return subject_->getState("enableKeyboard");
}

// -----------------------------------------------------------------
// MAIN1
// -----------------------------------------------------------------
void wait(){
    std::cin.get();
    std::cout << "\n";
}



int main(){
    Screen* screen = new Screen;

    wait();
    screen->attach( new Mouse(screen) );

    wait();
    screen->attach( new Keyboard(screen) );

    wait();
    screen->sleep();

    wait();
    screen->wakeUp();

    return 0;
}



/**/