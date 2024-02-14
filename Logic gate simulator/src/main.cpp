#include <iostream>
#include <vector>
#include <string>
#include <conio.h>


struct Logic_Component
{
protected:
	static std::vector<Logic_Component*> ALL_GATES;
	static std::vector<Logic_Component*> ALL_INPUT_GATES;
	static std::vector<Logic_Component*> ALL_OUTPUT_GATES;
	static void ALL_GATES_SETUP()
	{
		for (size_t i = 0; i < ALL_GATES.size(); i++)
			ALL_GATES[i]->Setup();
	}
	static void ALL_INPUT_GATES_SETUP()
	{
		for (size_t i = 0; i < ALL_INPUT_GATES.size(); i++)
			ALL_INPUT_GATES[i]->Get_Input();
	}
	static void ALL_OUTPUT_GATES_PRINT()
	{
		for (size_t i = 0; i < ALL_OUTPUT_GATES.size(); i++)
			ALL_OUTPUT_GATES[i]->Print_Value();
	}

	static std::vector<Logic_Component*> CURRENT_GATES;
	static std::vector<Logic_Component*> NEW_GATES;

public:
	static void START_SIMULATION()
	{
		ALL_GATES_SETUP();
		ALL_GATES.~vector();
		ALL_INPUT_GATES_SETUP();

		for (size_t i = 0; i < ALL_INPUT_GATES.size(); i++)
			for (size_t j = 0; j < ALL_INPUT_GATES[i]->outputs.size(); j++)
				NEW_GATES.push_back(ALL_INPUT_GATES[i]->outputs[j]);

		ALL_INPUT_GATES.~vector();

		do
		{
			CURRENT_GATES = std::move(NEW_GATES);
			NEW_GATES.clear();

			for (size_t i = 0; i < CURRENT_GATES.size(); i++)
			{
				CURRENT_GATES[i]->Tick();
				for (size_t j = 0; j < CURRENT_GATES[i]->outputs.size(); j++)
					NEW_GATES.push_back(CURRENT_GATES[i]->outputs[j]);
			}
		} while (NEW_GATES.size() > 0);


		ALL_OUTPUT_GATES_PRINT();
		ALL_OUTPUT_GATES.~vector();
	}

	std::vector<Logic_Component*> outputs;
	bool output;

protected:
	Logic_Component()
		: output(false)
	{ ALL_GATES.push_back(this); }

	virtual void Tick() { return; }
	virtual void Setup() { return; }

	virtual void Get_Input() { return; }
	virtual void Print_Value() { return; }
};

std::vector<Logic_Component*> Logic_Component::ALL_GATES;
std::vector<Logic_Component*> Logic_Component::ALL_INPUT_GATES;
std::vector<Logic_Component*> Logic_Component::ALL_OUTPUT_GATES;

std::vector<Logic_Component*> Logic_Component::CURRENT_GATES;
std::vector<Logic_Component*> Logic_Component::NEW_GATES;

struct Pin_Component : public Logic_Component
{
	Logic_Component* input;
	virtual void Setup() override
	{
		input->outputs.push_back(this);
	}
	virtual void Tick() override
	{
		output = input->output;
	}
};

struct Constant_Analyzer_Component : public Logic_Component
{
	std::string name;

	Constant_Analyzer_Component(const std::string& Name)
		: name(Name)
	{}

	Logic_Component* input;
	virtual void Setup() override
	{
		input->outputs.push_back(this);
	}
	virtual void Tick() override
	{
		output = input->output;
		printf("%s: %d\n", name.c_str(), output);
	}
};

struct Dummy_Input_Component : public Logic_Component
{
	Dummy_Input_Component()
	{
		ALL_INPUT_GATES.push_back(this);
	}
};

struct User_Input_Component : public Dummy_Input_Component
{
	User_Input_Component(const std::string& name)
		: Name(name)
	{}

	std::string Name;

	virtual void Get_Input() override
	{
		printf("%s: ", Name.c_str());
		output =  _getch() == '1';
		printf("%d\n", output);
	}
};

struct Logic_Gate : public Logic_Component
{
	std::vector<Logic_Component*> inputs;
	virtual void Setup() override
	{
		for (size_t i = 0; i < inputs.size(); i++)
			inputs[i]->outputs.push_back(this);
	}
	virtual void Tick() = 0;
};

struct Dummy_Output_Gate : public Logic_Gate {
	Dummy_Output_Gate()
	{
		ALL_OUTPUT_GATES.push_back(this);
	}

	virtual void Tick() override
	{
		output = inputs[0]->output;					//WORST BUG |=
		for (size_t i = 0; i < inputs.size(); i++)	//took 1h to debug :/
			output |= inputs[i]->output;
	}
};

struct User_Output_Gate : public Dummy_Output_Gate
{
	User_Output_Gate(const std::string& name)
		: Name(name)
	{
		output = false;
	}

	std::string Name;

	virtual void Print_Value() override
	{
		printf("%s: %d\n", Name.c_str(), output);
	}
};

struct OR_Gate : public Logic_Gate
{
	virtual void Tick() override
	{
		output = inputs[0]->output || inputs[1]->output;
		for (size_t i = 2; i < inputs.size(); i++)
			output |= inputs[i]->output;
	}
};

struct AND_Gate : public Logic_Gate
{
	virtual void Tick() override
	{
		output = inputs[0]->output && inputs[1]->output;
		for (size_t i = 2; i < inputs.size(); i++)
			output &= inputs[i]->output;
	}
};

struct XOR_Gate : public Logic_Gate
{
	virtual void Tick() override
	{
		output = inputs[0]->output ^ inputs[1]->output;
		for (size_t i = 2; i < inputs.size(); i++)
			output ^= inputs[i]->output;
	}
};

struct NOT_Gate : public Logic_Gate
{
	virtual void Tick() override
	{
		output = !inputs[0]->output;
	}
};


struct Delay_Line
{
	Pin_Component** D;
	size_t Delay;

	Delay_Line(size_t delay)
		: Delay(delay)
	{
		D = new Pin_Component*[delay];
		for (size_t i = 0; i < Delay; i++)
		{
			std::cout << i << '\n';
			D[i] = new Pin_Component();
			if (i > 0)
				D[i - 1]->input = D[i];
		}
	}

	~Delay_Line()
	{
		for (size_t i = 0; i < Delay; i++)
			delete D[i];
		delete[] D;
	}

	Pin_Component* Output()
	{
		return D[0];
	}

	Logic_Component*& Input()
	{
		return D[Delay - 1]->input;
	}
};





struct X_Bit_User_Input_Component : public Logic_Component {
	Dummy_Input_Component** I;

	X_Bit_User_Input_Component(uint8_t bits, const std::string& name)
		: Bits(bits), Name(name)
	{
		ALL_INPUT_GATES.push_back(this);
		I = new Dummy_Input_Component *[Bits];
		for (size_t i = 0; i < Bits; i++)
			I[i] = new Dummy_Input_Component;
	}

	~X_Bit_User_Input_Component()
	{
		for (size_t i = 0; i < Bits; i++)
			delete I[i];
		delete[] I;
	}

protected:
	uint8_t Bits;
	std::string Name;

	virtual void Get_Input() override
	{
		printf("%s: ", Name.c_str());
		for (size_t i = 0; i < Bits; i++) {
			I[i]->output = _getch() == '1';
			printf("%d", I[i]->output);
		}
		puts("");
	}
};

struct X_Bit_User_Output_Component : public Logic_Component {
	Dummy_Output_Gate** O;

	X_Bit_User_Output_Component(uint8_t bits, const std::string& name)
		: Bits(bits), Name(name)
	{
		ALL_OUTPUT_GATES.push_back(this);
		O = new Dummy_Output_Gate*[Bits];
		for (size_t i = 0; i < Bits; i++)
			O[i] = new Dummy_Output_Gate;
	}

	~X_Bit_User_Output_Component()
	{
		for (size_t i = 0; i < Bits; i++)
			delete O[i];
		delete[] O;
	}

protected:
	uint8_t Bits;
	std::string Name;
	
	virtual void Print_Value() override
	{
		printf("%s: ", Name.c_str());
		for (size_t i = 0; i < Bits; i++)
			printf("%d", O[i]->output);
		puts("");
	}
};


struct Full_Adder {
	Pin_Component* A;
	Pin_Component* B;
	Pin_Component* Cin;

	Pin_Component* S;
	Pin_Component* Cout;

	Full_Adder()
	{
		A = new Pin_Component();
		B = new Pin_Component();
		Cin = new Pin_Component();

		xor1 = new XOR_Gate();
		xor2 = new XOR_Gate();

		and1 = new AND_Gate();
		and2 = new AND_Gate();

		or1 = new OR_Gate();

		S = new Pin_Component();
		Cout = new Pin_Component();

		xor1->inputs.reserve(2);
		xor1->inputs.emplace_back(A);
		xor1->inputs.emplace_back(B);

		xor2->inputs.reserve(2);
		xor2->inputs.emplace_back(xor1);
		xor2->inputs.emplace_back(Cin);

		and1->inputs.reserve(2);
		and1->inputs.emplace_back(xor1);
		and1->inputs.emplace_back(Cin);

		and2->inputs.reserve(2);
		and2->inputs.emplace_back(A);
		and2->inputs.emplace_back(B);

		or1->inputs.reserve(2);
		or1->inputs.emplace_back(and1);
		or1->inputs.emplace_back(and2);

		S->input = xor2;
		Cout->input = or1;
	}

	~Full_Adder()
	{
		delete A;
		delete B;
		delete Cin;
		delete xor1;
		delete xor2;
		delete and1;
		delete and2;
		delete or1;
		delete S;
		delete Cout;
	}
private:
	XOR_Gate* xor1;
	XOR_Gate* xor2;

	AND_Gate* and1;
	AND_Gate* and2;

	OR_Gate* or1;
};

struct Full_X_Bit_Adder {
	Pin_Component* Cin;
	Pin_Component* Cout;

	Pin_Component** A;
	Pin_Component** B;

	Pin_Component** S;

	Full_X_Bit_Adder(uint8_t bits)
		: Bits(bits)
	{
		Cin = new Pin_Component;
		Cout = new Pin_Component;

		A = new Pin_Component *[Bits];
		B = new Pin_Component *[Bits];
		ADDERS = new Full_Adder*[Bits];
		S =  new Pin_Component *[Bits];

		for (size_t i = 0; i < Bits; i++) {
			A[i] = new Pin_Component;
			B[i] = new Pin_Component;
			ADDERS[i] = new Full_Adder;
			S[i] = new Pin_Component;
		}

		Pin_Component* last = Cin;
		for (size_t i = 0; i < Bits; i++) {
			ADDERS[i]->Cin->input = last;
			ADDERS[i]->A->input = A[i];
			ADDERS[i]->B->input = B[i];
			S[i]->input = ADDERS[i]->S;
			last = ADDERS[i]->Cout;
		}
		Cout->input = ADDERS[Bits - 1]->Cout;
	}

	~Full_X_Bit_Adder()
	{
		delete Cout;
		delete Cin;
		for (size_t i = 0; i < Bits; i++) {
			delete A[i];
			delete B[i];
			delete ADDERS[i];
			delete S[i];
		}
		delete[] A;
		delete[] B;
		delete[] ADDERS;
		delete[] S;
	}
private:
	uint8_t Bits = 0;
	Full_Adder** ADDERS;
};

int main()
{
	//User_Input_Component* X = new User_Input_Component("X");
	//XOR_Gate* Xor = new XOR_Gate();
	//Constant_Analyzer_Component* analyzer = new Constant_Analyzer_Component("Xor");
	//Constant_Analyzer_Component* analyzer2 = new Constant_Analyzer_Component("Delay");
	//Delay_Line* delay = new Delay_Line(10);
	//
	//Xor->inputs.push_back(X);
	//Xor->inputs.push_back(Xor);
	//delay->D[delay->Delay - 1]->input = X;
	//analyzer->input = delay->D[0];
	//analyzer->input = Xor;
	//delay->Input() = X;
	//analyzer2->input = delay->Output();
	//
	//Logic_Component::START_SIMULATION();

	std::cout << "BITS: ";
	uint16_t bits = 0;
	std::cin >> bits;
	
	Full_X_Bit_Adder* Adder = new Full_X_Bit_Adder(bits);
	
	User_Input_Component* Cin = new User_Input_Component("Cin");
	
	X_Bit_User_Input_Component* A = new X_Bit_User_Input_Component(bits, "A");
	X_Bit_User_Input_Component* B = new X_Bit_User_Input_Component(bits, "B");
	X_Bit_User_Output_Component* S = new X_Bit_User_Output_Component(bits, "S");
	
	User_Output_Gate* Cout = new User_Output_Gate("Cout");
	
	
	Adder->Cin->input = Cin;
	Cout->inputs.push_back(Adder->Cout);
	
	for (size_t i = 0; i < bits; i++) {
		Adder->A[i]->input = A->I[bits - 1 - i];
		Adder->B[i]->input = B->I[bits - 1 - i];
		S->O[bits - 1 - i]->inputs.push_back(Adder->S[i]);
	}


	Logic_Component::START_SIMULATION();
	
	
	delete A;
	delete B;
	delete S;
	
	delete Cin;
	delete Cout;
	
	delete Adder;
}