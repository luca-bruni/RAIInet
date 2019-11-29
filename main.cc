#include "controller.h"

using namespace std;

int main(int argc, char* argv[]){
	Controller *con = new Controller();
	con->loop();
	delete con;
}
