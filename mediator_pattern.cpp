#include <iostream>
#include <string>
/**
The mediator pattern is designed as a solution to large number of interactions between modular classes.
eg. in a dialog box the may be many widgets which are reusable classes, however they all land up needing
to know about each other when the listbox changes fields in th entry box etc etc.
If instead we brin in a mediator class, the mediator acts as a central point of interation. ( which can mean
that the mediator class becomes monolithic)
*/
class Collegue;
/// Mediator - the central hub for comunication between collegues
class Mediator
{
public:
	 Mediator(){};
	virtual ~ Mediator(){};

	virtual void CreateCollegues() = 0;
	virtual void CollegueChanged(Collegue*) = 0;
	
};

/// The Collegue - the objects that you wan to be loosely coupled but impact many other objects, instead of direct communication, only a single link to the Mediator is required
class Collegue
{
public:
	Collegue(Mediator* mediator)
	{
		m_Mediator = mediator;
	}
	virtual ~Collegue(){};
	
	virtual void Changed() {
		m_Mediator->CollegueChanged(this);
	}

	virtual void SetText(std::string text){
		std::cout << "Setting List text to: " << text << std::endl;
		m_text = text;
		Changed();
	}

	virtual std::string GetText()
	{
		return m_text;
	}

private:
	std::string m_text;
	Mediator* m_Mediator;
};


/// A concrete Collegue - that affects EntryBoxes
class aListBox : public Collegue
{
public:
	aListBox(Mediator* mediator) : Collegue(mediator) {};
	
};

/// another concrete Collegue - that is affected by listBoxes
class anEntryBox : public Collegue
{
public:
	anEntryBox(Mediator* mediator) : Collegue(mediator) {};
};

/// The Concrete Mediator that handles the interactions between the collegues. We trade off the complexity of this class against keeping the collegues loosely coupled.
class aDialogDirector : public Mediator
{
public:
	aDialogDirector(){};
	~aDialogDirector() {
		delete m_List;
		delete m_Entry;
	}

	void CollegueChanged(Collegue* changedCollegue)
	{
		if (changedCollegue == m_List) 
		{
			std::cout << "setting entry text to: " << m_List->GetText() <<std::endl;			
		}
	}

	void CreateCollegues()
	{
		m_List = new aListBox(this);
		m_Entry = new anEntryBox(this);
	}

	void ShowColleguesAndFakeInput() {
		std::cout << "Collegues have been shown" << std::endl;
		m_List->SetText("ChangedListText");
	}
private:
	aListBox* m_List;
	anEntryBox* m_Entry;	
};


int main(int argc, char const *argv[])
{
	aDialogDirector m_Director;
	m_Director.CreateCollegues();
	m_Director.ShowColleguesAndFakeInput();

	return 0;
}