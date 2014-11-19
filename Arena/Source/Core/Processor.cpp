#include <boost\bind.hpp>

#include "Macro"
#include "Core\Processor.h"

Processor::Processor(const unsigned int &_threads) :
	disposed(false),
	service(),
	work(service)
{
	for (unsigned int current = 0; current < _threads; ++current)
		threads.create_thread(boost::bind(&boost::asio::io_service::run, &service));
}

void Processor::Dispose()
{
	if (disposed) return; disposed = true;

	service.stop();

	threads.interrupt_all();
	threads.join_all();

	delete this;
}

Processor::~Processor()
{

}