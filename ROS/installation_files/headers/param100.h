#pragma once

#include <unordered_map>
#include <fstream>
#include <string>

//load the param.csv into a map for quick finding
void loadParams(std::unordered_map<std::string, std::string>& params)
{
	std::ifstream fin("param.csv");
	std::string cur, key, values;

	while (fin >> cur)
	{
		int pos = -1;
		for (int i = 0; i < 3; i++) pos = cur.find(',', pos + 1); // find x,y,val

		key = cur.substr(0, pos);
		values = cur.substr(pos + 1, cur.size());

		params.insert({ key,values });
	}
}

//change delimeter of provided string for words
void changeKeyDelim(std::string& change, char from, char to)
{
	int pos = 0;
	if ((pos = change.find(from, pos)) != std::string::npos)
	{
		change[pos] = to;
		pos = pos + 1;
	}

	if ((pos = change.find(from, pos)) != std::string::npos)
	{
		change[pos] = to;
	}
}