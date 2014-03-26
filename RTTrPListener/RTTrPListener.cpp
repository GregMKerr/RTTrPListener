#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

#include "RTTrPListener.h"
#include "blacktrax_third_party_protocol.h"

using namespace boost::asio::ip;

namespace RTTrPListener
{
	class Listener{
	public:
		Listener(const int multicast_port, const std::string multicast_address, const std::string listen_address) :
			multicast_port(multicast_port),
			multicast_address(address::from_string(multicast_address)),
			listen_address(address::from_string(listen_address)),
			socket(this->service)
		{
		}

		int init(){
			try{
				udp::endpoint listen_endpoint(listen_address, multicast_port);
				socket.open(listen_endpoint.protocol());
				socket.set_option(udp::socket::reuse_address(true));
				socket.bind(listen_endpoint);

				socket.set_option(multicast::join_group(multicast_address));

				socket.async_receive_from(
					boost::asio::buffer(data, max_length), sender_endpoint,
					boost::bind(&Listener::handle_receive_from, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}
			catch (std::exception& e)
			{
				std::cout << "Exception: " << e.what() << std::endl;
			}

			return 0;
		}

		void handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
		{

			RTTRPHeader* header = parseHeader(reinterpret_cast<const unsigned char*>(data.c_array()));
			if (header){
				Print(header);
			}

			socket.async_receive_from(
				boost::asio::buffer(data), sender_endpoint,
				boost::bind(&Listener::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}

	private:
		boost::asio::io_service service;
		udp::socket socket;
		udp::endpoint sender_endpoint;
		const address listen_address;
		const address multicast_address;
		enum { max_length = 1024 };
		boost::array<char, max_length> data;
		const int multicast_port = 24002;
	};

	int Interface::Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address)
	{

	}

	int Interface::Start()
	{

	}

	int Interface::Stop()
	{

	}
}