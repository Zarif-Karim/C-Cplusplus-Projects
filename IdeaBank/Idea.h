#pragma once

class Idea {
private:

	static	int			ID_GENERATOR;
	
			int			ID;
			string		proposer;
			string		title;
	list  < string >	keywords;
			string		content;

public:
	
	 Idea(): ID(++ID_GENERATOR)	   { }
	~Idea()						   { }
	 Idea          (const Idea& c) :
		 ID(c.ID),
		 proposer(c.proposer),
		 title(c.title),
		 keywords(c.keywords),
		 content(c.content)		{ }


	bool	searchWord	(string f) {
		
		for ( string& x : keywords )
			if (x.compare(f) == 0) 
				return true;
		
		if (content.find(f) != string::npos) 
				return true;

		return false;
	}
	

	void	setProposer	(string p) {
		proposer = p;
	}
	void	setTitle    (string p) {
		title = p;
	}
	void	addKeyword	(string k) {
		keywords.push_back(k);
	}
	void	addContent	(string c) {
		content = c;
	}


	int		getID	   () { return ID;		 }
	string	getProposer() { return proposer; }
	string  getTitle   () { return title; }
	list<string>
			getKeywords() { return keywords; }
	string	getContent () { return content;  }
};
