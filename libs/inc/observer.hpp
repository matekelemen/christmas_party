#include <array>
#include <map>
#include <iostream>
#include <vector>



/*
struct Event{
    std::map data;
};
*/

// Forward declaration of the Observer interface
class Observer;


// -----------------------------------------------------------------
// SUBJECT
// -----------------------------------------------------------------
class Screen {

    private:
        std::array<size_t,2>        size_;
        std::map<std::string,bool>  states_;
        std::vector<Observer*>      observers_;

    public:
        // Constructor
        Screen();
        ~Screen();
        // State setters
        void wakeUp();
        void sleep();
        // Observer management
        void attach(Observer* target);
        void onChange();
        // Get
        bool getState(std::string stateName) { return states_[stateName]; }
};


// -----------------------------------------------------------------
// OBSERVERS
// -----------------------------------------------------------------
class Observer{
    protected:
        Screen* subject_;
        bool state_;
    public:
        Observer(Screen* screen) : subject_(screen), state_(false){}
        virtual ~Observer(){};
        virtual void onSubjectChange()=0;
        virtual bool query(){return false;}
};

class Mouse : public Observer{
    public:
        Mouse(Screen* screen) : Observer(screen){}
        ~Mouse(){}
        void onSubjectChange();
        bool query();
};

class Keyboard : public Observer{
    public:
        Keyboard(Screen* screen) : Observer(screen){}
        ~Keyboard(){}
        void onSubjectChange();
        bool query();
};