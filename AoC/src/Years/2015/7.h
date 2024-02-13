#pragma once

START

	std::string nextWord(const std::string& str, size_t& i)
	{
		std::string r = "";
		while (str[i] == ' ' || str[i] == '\n')
			i++;
		while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0') {
			r += str[i];
			i++;
		}
		return r;
	}

	uint16_t toNum(const std::string& str)
	{
		uint16_t r = 0;
		for (size_t i = 0; i < str.size(); i++)
			r = r * 10 + str[i] - '0';
		return r;
	}

	struct LogicComponent
	{
		static std::vector<LogicComponent*> references;
		LogicComponent()
		{ references.push_back(this); }
		virtual uint16_t Compute() = 0;
		static void Delete();
	};
	std::vector<LogicComponent*> LogicComponent::references;

	struct Constant : public LogicComponent
	{
		Constant(uint16_t val) : value(val) {}
		uint16_t value;
		uint16_t Compute() { return value; }
	};

	struct Wire : public LogicComponent
	{
		int32_t computed = -1;
		Wire() : input(NULL) {}
		Wire(LogicComponent* input) : input(input) {}
		LogicComponent* input;
		uint16_t Compute() {
			if (computed == -1)
				computed = input->Compute();
			return computed;
		}
		void Reset()
		{ computed = -1; }
	};

	void LogicComponent::Delete()
	{
		for (auto ref : references)
			if (dynamic_cast<Wire*>(ref) == nullptr)
				delete ref;
		references.clear();
	}

	struct AND : public LogicComponent
	{
		AND(LogicComponent* input1, LogicComponent* input2)
		{
			input[0] = input1;
			input[1] = input2;
		}
		LogicComponent* input[2];
		uint16_t Compute() { return input[0]->Compute() & input[1]->Compute(); }
	};

	struct OR : public LogicComponent
	{
		OR(LogicComponent* input1, LogicComponent* input2)
		{
			input[0] = input1;
			input[1] = input2;
		}
		LogicComponent* input[2];
		uint16_t Compute() { return input[0]->Compute() | input[1]->Compute(); }
	};

	struct RS : public LogicComponent
	{
		RS(LogicComponent* input1, LogicComponent* input2)
		{
			input[0] = input1;
			input[1] = input2;
		}
		LogicComponent* input[2];
		uint16_t Compute() { return input[0]->Compute() >> input[1]->Compute(); }
	};

	struct LS : public LogicComponent
	{
		LS(LogicComponent* input1, LogicComponent* input2)
		{
			input[0] = input1;
			input[1] = input2;
		}
		LogicComponent* input[2];
		uint16_t Compute() { return input[0]->Compute() << input[1]->Compute(); }
	};

	struct NOT : public LogicComponent
	{
		NOT(LogicComponent* input1) : input(input1) {}
		LogicComponent* input;
		uint16_t Compute() { return ~input->Compute(); }
	};

	void CreateComponents(std::string& input, std::unordered_map<std::string, Wire>& wires)
	{
		for (size_t i = 0; i < input.size(); i++) {
			std::string first = nextWord(input, i);
			if (first == "NOT") {
				std::string arg1 = nextWord(input, i);
				nextWord(input, i);
				int32_t arg1C = -1;
				LogicComponent* arg1p = nullptr;
				if (arg1[0] >= '0' && arg1[0] <= '9') {
					arg1C = toNum(arg1);
					arg1p = new Constant(arg1C);
				}
				else
					arg1p = &wires[arg1];
				std::string output = nextWord(input, i);
				LogicComponent* gate = new NOT(arg1p);
				wires[output].input = gate;
			}
			else {
				std::string arg1 = first;
				int32_t arg1C = -1;
				LogicComponent* arg1p = nullptr;
				if (arg1[0] >= '0' && arg1[0] <= '9') {
					arg1C = toNum(arg1);
					arg1p = new Constant(arg1C);
				}
				else
					arg1p = &wires[arg1];
				std::string second = nextWord(input, i);
				if (second == "->") {
					std::string output = nextWord(input, i);
					wires[output].input = arg1p;
				}
				else {
					std::string instruction = second;
					std::string arg2 = nextWord(input, i);
					nextWord(input, i);
					std::string output = nextWord(input, i);
					int32_t arg2C = -1;
					LogicComponent* arg2p = nullptr;
					if (arg2[0] >= '0' && arg2[0] <= '9') {
						arg2C = toNum(arg2);
						arg2p = new Constant(arg2C);
					}
					else
						arg2p = &wires[arg2];
					LogicComponent* gate = nullptr;
					if (instruction == "AND")
						gate = new AND(arg1p, arg2p);
					else if (instruction == "OR")
						gate = new OR(arg1p, arg2p);
					else if (instruction == "RSHIFT")
						gate = new RS(arg1p, arg2p);
					else
						gate = new LS(arg1p, arg2p);
					wires[output].input = gate;
				}
			}
		}
	}

	void Part1(std::string& input)
	{
		std::unordered_map<std::string, Wire> wires;
		CreateComponents(input, wires);
		size_t result = 0;
		result = wires["a"].Compute();
		std::cout << result;
		LogicComponent::Delete();
	}

	void Part2(std::string& input)
	{
		std::unordered_map<std::string, Wire> wires;
		CreateComponents(input, wires);
		uint16_t newB = wires["a"].Compute();
		for (auto& wire : wires)
			wire.second.Reset();
		wires["b"].input = new Constant(newB);
		size_t result = 0;
		result = wires["a"].Compute();
		std::cout << result;
		LogicComponent::Delete();
	}

END