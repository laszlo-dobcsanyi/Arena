#ifndef NETWORK_PACKET_H
#define NETWORK_PACKET_H

#include <string>

#include <boost\shared_ptr.hpp>

struct Packet
{
public:
	int size = 0;
	char* data = 0;

	Packet(const int &_command, const std::string &_message);
	~Packet();

	static std::string ToString(char* _data, unsigned int _size);

private:
	Packet(const Packet &_other);
	Packet & operator=(const Packet &other);
};

class Character;

struct PacketPair
{
public:
	Packet *packet;
	boost::shared_ptr< Character > sender;

	PacketPair(Packet *_packet);
	PacketPair(Packet *_packet, boost::shared_ptr< Character> _sender);
	~PacketPair();

private:
	PacketPair(const PacketPair &_other);
	PacketPair & operator=(const PacketPair &_other);
};

#endif
