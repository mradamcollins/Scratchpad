/**
The strategy pattern is used to allow selection of algorithms at run time, or when you have many variants of an algorithm
It contains a Context class which is cofigured with ConcreteStrategies
**/
#include <iostream>
class Strategy
{
public:
	virtual void StrategyInterface() = 0;	
};

class Context
{
public:
	Context(Strategy* theStrategy)
	{
		m_strategy = theStrategy;
	}

	void ContextInterface()
	{
		m_strategy->StrategyInterface();
	}

private:
	Strategy* m_strategy;
};

class ConcreteStrategyA : public Strategy
{
public:
	virtual void StrategyInterface()
	{
		std::cout << "Using StrategyA" << std::endl;
	}	
};

class ConcreteStrategyB : public Strategy
{
public:
	virtual void StrategyInterface()
	{
		std::cout << "Using StrategyB" << std::endl;
	}	
};

int main(int argc, char const *argv[])
{
	Context* aContext = new Context(new ConcreteStrategyA);
	Context* bContext = new Context(new ConcreteStrategyB);
	aContext->ContextInterface();
	bContext->ContextInterface();
	return 0;
}

/**
Note: there's two approaches to managing the data strategies require. You can either create a suitably generic interface, that allows
passing in the required data as parameters. This may mean that certain strategies don't use all the parameters passed in.
The other option is to pass in a reference to the Context and ensuring that the Context has a suitably flexible interface to allow the 
strategies retrieve the information they require directly.

Strategies are also good candiates for the flywieght patten
**/