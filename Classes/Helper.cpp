#include "Helper.h"

namespace GameObjects {

	vector<string> &Helper::split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	vector<string> Helper::split(const string &s, char delim) {
		std::vector<string> elems;
		split(s, delim, elems);
		return elems;
	}
}
