#ifndef __GAME_HELPER_H__
#define __GAME_HELPER_H__

#include <vector>
#include <sstream>
using namespace std;

namespace GameObjects {

	class Helper
	{

	public:	
		static vector<string> &split(const string &s, char delim, vector<string> &elems);
		static vector<string> split(const string &s, char delim);
	};
}

#endif /*__GAME_HELPER_H__*/

