#include <stdio.h>
#include <iostream>
<<<<<<< HEAD
using namespace std;

int main(int argc, char* argv[])
{	
=======
#include "hostInterface.cpp"
using namespace std;


int main(int argc, char* argv[])
{
	HostInterface hostIF;
	hostIF.ParseCommand(argc, argv);
	
>>>>>>> 503577d44a7fdd7288c68c2a90df9a49ab5ead26
	return 0;
}