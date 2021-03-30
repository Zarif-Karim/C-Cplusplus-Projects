#pragma once

class InvertIndex {
private:
	//AvlTree<Index, string> indexTree;
	IDEA_AVL indexTree;

	void add_key      (string x, Idea *it) {
		Index* buffer;
		bool add = true;
		if (indexTree.AVL_Modify(x, &buffer)) { // if match found for keyword

			for (int& i : (*buffer).idList)	// check if already added
				if (i == it->getID()) {
					add = false; break;
				}

			if (add) (*buffer).idList.push_back(it->getID()); // if not added. Add to list
		}
		else {	// if match not found update buffer and add to tree
			buffer = new Index{};
			(*buffer).key = x;
			(*buffer).idList.push_back(it->getID());
			indexTree.AVL_Insert(*buffer);
			delete buffer;
		}
		add = true; // reset add boolean
	}
	void delete_id	     		 (int& id) {
	/*	list<string> zeroIdList;*/
		auto update = [] (Index& d, int& id){
			for (auto i = d.idList.begin(); i != d.idList.end(); i++) {
				if (*i == id) {
					d.idList.erase(i);
					break;
				}
			}
		};
		indexTree.AVL_Update_Traverse(update, id);
	}
public:
	//c and d?

	void updateIndex
		( unordered_map<int,Idea>&    db )		 {
		
		for (auto it = db.begin(); it != db.end(); it++) { // iterate through Ideas in the database
			
			// for keywords in Idea object
			for (string& x : it->second.getKeywords()) {					
				add_key(x, &(it->second));
			}

			//check each word in content and add or update as necessary
			istringstream is(it->second.getContent());
			string buff;
			int c = 0;
			while (is >> buff) {
				c++;
				for (int i = 0; i < buff.size(); i++) {
					if (!isalpha(buff[i])) {
						buff.erase(buff.begin() + i);
						i--;
					}
				}
				
				add_key(buff, &(it->second));
			}
		}
	}
	void update_delete			 (int& id) {
		delete_id(id);
	}
	
	bool findIndex (string s, Index &buff) {
		if (indexTree.AVL_Retrieve(s, buff)) return true;
		return false;
	}
	void printTree		   		        () {
		indexTree.Print_Dictionary();
	}
};
