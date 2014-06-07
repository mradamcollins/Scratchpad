#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>
using namespace std;

class Expression
{
public:
	virtual bool Interpret(string str) =0;
};

class TerminalExpression : public Expression
{
public:
	TerminalExpression(string str) : m_literal(str) {};

	virtual bool Interpret(string str)
	{
		stringstream strstr(str); // construct a string steam
		istream_iterator<string> iit(strstr); // construct string iterator from string stream
		istream_iterator<string> eos; // construct end of stream iterator
		while (iit != eos)
		{
			if (( *iit).compare(m_literal) == 0)
			{
				return true;
			}
			++iit;
		}
		return false;
	}
private:
	string m_literal;
};

class OrExpression : public Expression
{
public:
	OrExpression(shared_ptr<Expression> exp1, shared_ptr<Expression> exp2) : m_exp1(exp1), m_exp2(exp2) {};
	virtual bool Interpret(string str)
	{
		return m_exp1->Interpret(str) || m_exp2->Interpret(str);
	}

private:
	shared_ptr<Expression> m_exp1, m_exp2;
};

class AndExpression : public Expression
{
public:
	AndExpression(shared_ptr<Expression> exp1, shared_ptr<Expression> exp2) : m_exp1(exp1), m_exp2(exp2) {};
	virtual bool Interpret(string str)
	{
		return m_exp1->Interpret(str) && m_exp2->Interpret(str);
	}

private:
	shared_ptr<Expression> m_exp1, m_exp2;
};


shared_ptr<Expression> BuildInterpreterTree()
{
	shared_ptr<Expression> terminal1 = make_shared<TerminalExpression>("John");
	shared_ptr<Expression> terminal2 = make_shared<TerminalExpression>("Henry");
	shared_ptr<Expression> terminal3 = make_shared<TerminalExpression>("Mary");
	shared_ptr<Expression> terminal4 = make_shared<TerminalExpression>("Owen");

	shared_ptr<Expression> alternation1 = make_shared<OrExpression>(terminal2, terminal3); // henry or mary
	shared_ptr<Expression> alternation2 = make_shared<OrExpression>(terminal1, alternation1); // john or (henry or mary)

	return make_shared<AndExpression>(terminal4, alternation2); // Owen and (john or (henry or mary))
}


int main(int argc, char const *argv[])
{
	shared_ptr<Expression> rule = BuildInterpreterTree();
	cout << "For the rule (Owen and ( John or ( Henry or Mary) ) )" << endl;

	string context1("Mary John");
	string context2("Owen John");
	string context3("Owen Mary");
	cout << boolalpha;
	cout << context1 << " is " << rule->Interpret(context1) << endl;
	cout << context2 << " is " << rule->Interpret(context2) << endl;
	cout << context3 << " is " << rule->Interpret(context3) << endl;
	return 0;
}