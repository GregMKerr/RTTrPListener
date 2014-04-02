#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

#include "IListener.h"

using namespace boost::asio::ip;

namespace RTTrPListener
{
	class Listener : IListener{
	public:
		Listener() : socket(this->service)
		{
		}

		int Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address = "0.0.0.0");

		int Start();

		int Stop();

		void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd);

	private:
		boost::asio::io_service service;
		udp::socket socket;
		udp::endpoint sender_endpoint;
		const address listen_address;
		const address multicast_address;
		const int multicast_port;
		enum { max_length = 1024 };
		boost::array<char, max_length> data;
		callback_function callbackfunc;
	};
}