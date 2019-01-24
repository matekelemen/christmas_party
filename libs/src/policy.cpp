#include <iostream>



/* -----------------------------------------------------------
BASIC EXAMPLE FOR POLICY BASED DESIGN, TO ACCOMPANY THE THEORY
- Several models of A/C machines with different output powers
- Different units of measurement
Task: we need to get the power output of any machine in any
units of measurements.
----------------------------------------------------------- */




// Derived template class -> inherits from two other template classes (policies)
template <class policy_machine, class policy_units>
class ACpower : public policy_machine, public policy_units {
	// Member function
public:
	void getVal() {
		// Using functions implemented in the base classes
		std::cout 
			<< policy_units::unitOfPower(	policy_machine::powerOutput()	)
			<< "\n";
	}
};





// Machine base class: Siemens machine -----------------------------------------
struct siemensMachine {
	double powerOutput() { return 2200; } // Power output in watts
};

// Machine base class: GE machine
struct geMachine {
	double powerOutput() { return 1500; } // Power output in watts
};

// Unit base class: metric (kilowatts) -----------------------------------------
struct metricUnits {
	double unitOfPower(double watts) { return watts / 1000; } // Return input power in kilowatts
};

// Unit base class: imperial (tons)
struct imperialUnits {
	double unitOfPower(double watts) { return watts / 3504; } // Return input power in tons
};




// Main
int main() {
	// Create instances
	ACpower<siemensMachine, metricUnits> pow1;
	ACpower<geMachine, imperialUnits> pow2;

	// Call the function of the derived class
	pow1.getVal();
	pow2.getVal();
}