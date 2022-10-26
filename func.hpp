#include <vector>

bool not_in(int x, vector<int> n) {
    for (int i = 0; i < n.size(); ++i) {
        if (x == n.at(i)) {
            return false;
        }
    }
    return true;
}

//(7 11 4 23 13 26 1 )
