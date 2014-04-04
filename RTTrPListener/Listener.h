#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

#include "RTTrPListener.h"

using namespace boost::asio::ip;


class Listener : IListener{
public:
	Listener() : m_socket(this->m_service)
	{
	}

	int Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address = "0.0.0.0");

	int Start();

	int Stop();

	int Release();

	void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

private:
	boost::asio::io_service m_service;
	udp::socket m_socket;
	udp::endpoint m_sender_endpoint;
	address m_listen_address;
	address m_multicast_address;
	int m_multicast_port;
	enum { max_length = 1024 };
	boost::array<char, max_length> m_data;
	callback_function m_callbackfunc;
};
