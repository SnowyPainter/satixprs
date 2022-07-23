#include <iostream>
#include <vector>
#include "Set.h"
using namespace std;

int main() {
	Set<int> a((int)SetType::Inf, "A");
	Set<int> b((int)SetType::Inf, "B");
	a.Add(vector<int>{1, 2, 3});
	b.Add(vector<int>{1, 2, 3, 4, 5});

	a.PPrint();
	b.PPrint();
	return 0;
}