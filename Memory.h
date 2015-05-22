#pragma once
#include "Data.h"


#include <string>
#include <exception>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>



#define SHM_SIZE 1024 //1KB

class Memory
{
public:
	Memory(int _key = -1)
	{
		if(_key == -1)
		{
			srand(time(0));
			_key = rand()%10000;
		}
		key = (key_t) _key;
		if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
		{
			throw std::exception();
		}
	}

	int getKey()
	{
		return (int) key;
	}

	std::string read(int delay = 0)
	{
		void * data = shmat(shmid, (void *)0, 0);
    	if (data == (void *)(-1)) 
    	{
    		throw std::exception();
	    }

	    Data * dt = (Data *) data;
	    dt->isUsed = true;
	    if(delay != 0)
	    	sleep(delay);
	    dt->isUsed = false;
	    return dt->data.c_str();
	} 

	void write(std::string txt)
	{
		void * data = shmat(shmid, (void *)0, 0);
    	if (data == (void *)(-1)) 
    	{
    		throw std::exception();
	    }

	    Data * dt = (Data *) data;
	    while(dt->isUsed);
	    dt->data = txt;
	}

private:
	int shmid;
	key_t key;

};