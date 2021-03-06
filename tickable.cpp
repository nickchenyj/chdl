// Tickable.
#include "tickable.h"

using namespace std;
using namespace chdl;

vector<tickable*> chdl::tickables;

template <typename T> void remove_from_vector(vector<T> &v, const T &val) {
  vector<T> new_v;
  for (size_t i = 0; i < v.size(); ++i)
    if (v[i] != val) new_v.push_back(v[i]);
  v = new_v;
}

tickable::~tickable() { remove_from_vector(tickables, this); }
