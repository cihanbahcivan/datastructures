#include <iostream>
#include "Control.hpp"

using namespace std;


int main()
{
	Control ctrl;
	ctrl.ListCount();
	ctrl.ReadLines();
	ctrl.FindMinMax();

	system("PAUSE");  //Ekranin hemen kapanmamasi ve yazilanlarin gorulebilmesi icin sonlanmayi durduran PAUSE islemi.

	return 0;
}


