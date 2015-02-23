#include "GameMessage.h"
#include "DataProvider.h"
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>

#define MSEC_PROCESS_DELAY 100 // ms to wait between processing events waiting in the message queue
#define SERVER_ADDR "tcp://127.0.0.1:7633"

void ProcessItem(const GameMessage*);

int main()
{
	// Protects access to the GameMessage queue that will be added to asynchronously
	std::mutex mtx;
	// Holds important GameMessages from the game server
	std::queue<GameMessage*> q;

	// Start the thread that will provide data to the GameMessage queue
	DataProvider ddp(mtx, q, SERVER_ADDR);
	ddp.BeginListening();

	// Main processing loop
	// Wait for queue to be populated and perform some work on it when items are available
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(MSEC_PROCESS_DELAY));
		mtx.lock();
		//std::cout << "Main thread got lock, processing all available items" << std::endl;
		while (!q.empty())
		{
			// Process this item 
			ProcessItem(q.front());
			delete q.front();
			q.pop();
		}
		mtx.unlock();
	}
}

void ProcessItem(const GameMessage* gm)
{
	// Speed up BPM, queue a bass kick on the next downbeat, decrease synth freq..
	std::cout << "Processing item [" << gm->eventType << "]: " << std::endl;
	if (gm->info == NULL)
	{
		std::cout << "\tgm.info == NULL" << std::endl;
		return;
	}

	for (auto& item : *gm->info)
	{
		// for now, just print out to the console all the events that happen
		std::cout << "\tgm.info[\"" << item.first << "\"]: " << item.second << std::endl;
	}
}