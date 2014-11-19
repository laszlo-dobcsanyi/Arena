#ifndef CORE_PROCESSOR_H
#define CORE_PROCESSOR_H

#include <boost\atomic.hpp>
#include <boost\thread.hpp>
#include <boost\asio\io_service.hpp>

class Processor
{
public:
	Processor(const unsigned int &_threads);

	boost::asio::io_service & Service() { return service; };

	void Dispose();


private:
	boost::atomic< bool > disposed;

	boost::asio::io_service service;
	boost::asio::io_service::work work;
	boost::thread_group threads;

	~Processor();

	Processor(const Processor &_other);
	Processor & operator=(const Processor &_other);
};

#endif