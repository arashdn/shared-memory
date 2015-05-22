#include "Data.h"
#include "Memory.h"

#include <string>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{

    Memory mr;
    cout << "Enter a key number (write 0 to generate a random key): ";
    int key;
    cin>> key;
    if(key<=0)
    	mr = Memory();
    else
    	mr=Memory(key);

    cout << "\nKey is:" <<mr.getKey();
    char x;
    while(1)
    {
    	cout <<"\n\n-----------\nChoose one: \nr:Read\nd:Read with delay (to test concurrency)\nw:write\nx:exit\n-----------\n";
    	cin >> x;
    	if(x == 'r')
    	{
    		cout << "Data is: "<<mr.read();
    	}
        else if(x == 'd')
        {
            cout << "Data is: "<<mr.read(8);
        }
    	else if(x == 'w')
    	{
    		string s;
    		cout << "Enter data to input: ";
    		cin >> s;
    		mr.write(s);
    	}
    	else if(x == 'x')
    		exit(0);
    }

    return 0;
}