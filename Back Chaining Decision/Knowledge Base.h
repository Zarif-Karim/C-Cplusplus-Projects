#pragma once

class KnowledgeBase 
{
	uM(char,uM(char, char)) kb;

public:
	KnowledgeBase() 
	{
		cout << "Enter Knowledge Base: \n"
			<< "(finish with '%')\n\n";

		string in;
		do
		{
		REENTER:
			getline(cin, in);

			uM(char, char) tmp;
			if (in.size() > 1)
			{
				for (int i = 0; i < in.size()-3; i += 2)
				{
					if (in[i + 1] != '^' && in[i + 1] != 'v' && in[i+1] != '=')
					{
						cout << "\nWrong Proposition format! REENTER: \n\n";
						goto REENTER;
					}
					tmp[in[i]] = in[i + 1];
				}
			} 

			if (in == "%") break;

			kb[in[in.size()-1]] = tmp;

		} while (1);

		cout << "\n\nFinished Entering knowledge base.\n\n";
	}

	void printProp(uM(char,uM(char, char))::iterator i) {
		cout << "\n\nProposition: \n\n";
		for (auto j : i->second)
		{
			cout << j.first << j.second;
		}
		if (i->second.size() > 0) cout << '>';
		cout << i->first << endl;
		cout << endl << endl;
	}

	void printKB() {
		cout << "\n\nKnowledge Base: \n\n";
		for (auto i = kb.begin(); i != kb.end(); ++i)
		{
			for (auto j : i->second)
			{
				cout << j.first << j.second;
			}
			if (i->second.size() > 0) cout << '>';
			cout << i->first << endl;
		}

		cout << endl << endl;
	}

	auto findKey(char k)
	{
		return kb.find(k);
	}

	auto end()
	{
		return kb.end();
	}
};
