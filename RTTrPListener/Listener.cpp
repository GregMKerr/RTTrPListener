#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

#include "Listener.h"
#include "blacktrax_third_party_protocol.h"

using namespace boost::asio::ip;

namespace RTTrPListener
{
	int Listener::Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address){
		try{
			this->multicast_port = multicast_port;
			this->multicast_address = address::from_string(multicast_address);
			this->callbackfunc = callbackfunc;
			this->listen_address = address::from_string(listen_address);

			udp::endpoint listen_endpoint(listen_address, multicast_port);
			socket.open(listen_endpoint.protocol());
			socket.set_option(udp::socket::reuse_address(true));
			socket.bind(listen_endpoint);

			socket.set_option(multicast::join_group(multicast_address));

			socket.async_receive_from(
				boost::asio::buffer(data, max_length), sender_endpoint,
				boost::bind(&Listener::handle_receive_from, this, 
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		catch (std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	int Listener::Start(){
		try{
			service.run();
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	int Listener::Stop(){
		try{
			service.stop();
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	void Listener::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
	{
		try{
			RTTRPHeader* header = parseHeader(reinterpret_cast<const unsigned char*>(data.c_array()));
			if (callbackfunc){
				callbackfunc(header);
			}
	
			socket.async_receive_from(
				boost::asio::buffer(data), sender_endpoint,
				boost::bind(&Listener::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}
}