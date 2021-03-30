#pragma once

class IdeasBank {
private:
	unordered_map<int, Idea>	bank;
	InvertIndex indexer;
	
	template<class T>
	void search_print		 (T ids) {
		if (!ids.empty()) {
			cout << "Relevent Ideas by ID: ";
			for (int x : ids) cout << x << ", ";
			cout << "\b\b.\n\n";

			for (int x : ids) idea_by_id(x);
		}
		else cout << "No relevant Ideas found!\n\n";
	}

public:

	void start_server			  (){
		int choice = 1;

		while (choice > 0 && choice < 10) {
			cout	<< "\n1) Insert Idea"
					<< "\n2) Insert Idea from file"
					<< "\n3) Search Idea by ID"
					<< "\n4) Print Database"
					<< "\n5) Delete Idea by ID"
					<< "\n6) Print inverted indexes"
					<< "\n7) Relevant Ideas form database"
					<< "\n8) Relevant Ideas from inverted indexes"
					<< "\n9) Relevant Ideas more that two words(same conditon)"
					<< "\nAny other number: Exit\n"
					<< "\nChoice: ";

			cin >> choice; 
			cin.ignore();
	
			int id;

			switch (choice) {
				case 1:
					insert_new_idea();
					break;
				case 2:
					import_file();
					break;
				case 3:
					cout << "Enter ID to search: ";
					cin >> id;
					idea_by_id(id);
					break;
				case 4:
					print();
					break;
				case 5:
					cout << "Enter ID to Delete: ";
					cin >> id;
					delete_idea(id);
					break;
				case 6:
					indexer.printTree();
					break;
				case 7:
					//search_print(search_bank());
					search_print(bonus_search_bank());
					break;
				case 8:
					//search_tree();
					search_print(bonus_search_tree());
					break;
				case 9:
					search_print(bonus2_search_bank());
					break;
				default: cout << "\n\n\nExit\n\n";
			}
		}
	
	}

	void insert_new_idea		  () {
		Idea newIdea;
		string proxy;
		
		cout << "Entering new Idea:\n\n" 
			 << "Proposer: ";
		getline(cin, proxy);
		newIdea.setProposer(proxy);

		cout << "Title   : ";
		getline(cin, proxy);
		newIdea.setTitle(proxy);

		cout << "\n(Empty word to finish entering)\n";
		int count = 1;
		do {
			cout << "Keywords " << count++
				<< ": ";
			getline(cin, proxy);
			if (proxy != "") newIdea.addKeyword(proxy);
		} while (proxy != "");

		cout << "\nContent:\n\n";
		getline(cin, proxy);
		newIdea.addContent(proxy);

		bank.insert(make_pair(newIdea.getID(), Idea(newIdea)));

		indexer.updateIndex(bank);
	}
	void import_file			  () {
		string f;
		//cout << "\nEnter File name :";
		//cin >> f;
		cout << "\n!!!!!!!!!!!!!!(SET TO file2.txt)";
		f = "file2.txt";

		ifstream in(f, ios_base::in);
		if (in.is_open()) {
			cout << "\nExtracting from " << f << "......\n";
			
			while (getline(in, f)) {
				Idea newIdea;
				newIdea.setProposer(f);
				getline(in, f);
				newIdea.setTitle(f);
				while (f != "") {
					getline(in, f);
					if(f!="")newIdea.addKeyword(f);
				}
				getline(in, f, '|');
				newIdea.addContent(f);

				bank.insert(make_pair(newIdea.getID(), Idea(newIdea)));
			}
			in.close();
			cout << "......Finished Extracting\n\n";
		}
		else perror("import_file(): ");

		indexer.updateIndex(bank);

	}
	void idea_by_id			(int  i) {
			
		auto it = bank.find(i);
		
		if (it != bank.end()) {
			cout << "\n\nIdea ID : " << it->second.getID()
				 <<   "\nProposer: " << it->second.getProposer()
				 <<   "\nTitle   : " << it->second.getTitle()
				 <<   "\nKeywords: ";
			for (string x : it->second.getKeywords())
				cout << x << ", ";

			cout << "\b\b." << "\nContent :\n\n\t"
				<< it->second.getContent();
		}
		else cout << "\n\nNo Ideas with given ID found!";

		cout << endl << endl;
	}
	void print					  () {
		cout << "\n\n\t\t............Printing Database:...........\n\n";
		for (auto& x : bank) idea_by_id(x.first);
		cout << "\n\n\t\t.............End of Database.............\n\n";
	}
	void delete_idea		(int id) {
		bank.erase(id);
		indexer.update_delete(id);
	}

	list<int> search_bank	      () {
		cout << "Search Word: ";
		string s; cin >> s;

		list<int> ids;

		for (auto it = bank.begin(); it != bank.end(); it++) {

			if(it->second.searchWord(s)) ids.push_back(it->first);
		}

		return ids;
	}
	list<int> bonus_search_bank   () {
		cout << "Search Word: ";
		string s; 
		getline(cin, s);
		
		string searchList[2]; // max no of words is 2
		bool AND = false; // if condition is and
		
		if (s.find(" ") != string::npos) { // " " character indicates there are more than 1 word
			istringstream search(s);
			string temp; int index = 0;
			while (search >> temp) {
				
				if (temp != "OR" && temp != "AND") {
					searchList[index++] = temp;
					if (index == 1) break;
				}
				else if (temp == "AND") AND = true;
			}
		}
		else {
			searchList[0] = s;
		}

		list<int> ids;

		for (auto it = bank.begin(); it != bank.end(); it++) {
			int foundCount = 0;	// for And condition to check if all words found

			if (it->second.searchWord(searchList[0])) foundCount += 1;
			if (searchList[1] != "" && it->second.searchWord(searchList[1])) foundCount += 1;
			
			if (AND && foundCount == 2) ids.push_back(it->first);
			else if (!AND && foundCount > 0) ids.push_back(it->first);
			
		}

		return ids;
	}
	set<int> bonus2_search_bank	  () {
		cout << "Search Word: ";
		string s;
		getline(cin, s);

		list<string> searchList; 
		list<bool> AND; // True if AND and False if OR

		if (s.find(" ") != string::npos) { // " " character indicates there are more than 1 word
			istringstream search(s);
			string temp;
			while (search >> temp) {

				if (temp != "OR" && temp != "AND") {
					searchList.push_back(temp);
				}
				else {
					if (temp == "AND") AND.push_back(true);
					else AND.push_back(false);
				}
			}
		}
		else {
			searchList.push_back(s);
			AND.push_back(false);
		}

		//run each pair in sequence 

		set<int> ids;

		auto word = searchList.begin();
		auto condition = AND.begin();

		int fCount = count(AND.begin(),AND.end(),true);

		for (auto it = bank.begin(); it != bank.end(); it++) {
			int foundCount = 0;	// for And condition to check if all words found

			for (auto word = searchList.begin(); word != searchList.end();){

				if (it->second.searchWord(*word)) foundCount += 1;
				if ((++word) != searchList.end() && it->second.searchWord(*word)) foundCount += 1;

				//if (*condition && foundCount == 2) ids.insert(it->first);
				/*else*/ if (*condition && foundCount < 2) foundCount = 0;//ids.clear();
				else if (!*condition && foundCount == 1) foundCount -= 1;

				if (++condition == AND.end()) {
					condition = AND.begin();
					break;
				}
			}
			if (foundCount >= fCount + 1) ids.insert(it->first);
		}

		return ids;
	}
	
	void search_tree	 		  () {
		cout << "Search Word: ";
		string s; cin >> s;

		Index buff;
		indexer.findIndex(s, buff);
		/*if (indexer.findIndex(s, buff) && !buff.idList.empty()) {
			cout << "Relevent Ideas by ID: ";
			for (int& x : buff.idList) cout << x << ", ";
			cout << "\b\b.\n\n";

			for (int& x : buff.idList) idea_by_id(x);
		}
		else cout << "No relevant Ideas found!\n\n";*/
		search_print(buff.idList);
	}
	set<int> bonus_search_tree	  () {
		
		cout << "Search Word: ";
		string s;
		getline(cin, s);

		string searchList[2]; // max no of words is 2
		bool AND = false; // if condition is and

		if (s.find(" ") != string::npos) { // " " character indicates there are more than 1 word
			istringstream search(s);
			string temp; int index = 0;
			while (search >> temp) {

				if (temp != "OR" && temp != "AND") {
					searchList[index++] = temp;
				}
				else if (temp == "AND") AND = true;
			}
		}
		else {
			searchList[0] = s;
		}

		Index buff;
		Index buff2;	// for second word

		bool  first_word = (indexer.findIndex(searchList[0], buff) && !buff.idList.empty()) ? true : false;
		bool second_word = (searchList[1] != "" && indexer.findIndex(searchList[1], buff2) && !buff2.idList.empty()) ? true : false;
		
		set<int> ids;
		
		if (AND) {
			if (first_word && second_word) {
				for (int& x : buff.idList)
					for (int& y : buff2.idList)
						if (x == y) ids.insert(x);//id.push_back(x);
			}
		}
		else {
			if (first_word) for (int& x : buff.idList) ids.insert(x);//push_back(x);
			if(second_word) for (int& x : buff2.idList) ids.insert/*push_back*/(x);
		}
		
		return ids;
	}

	auto& getBank				  () { 
		return bank; 
	}
};