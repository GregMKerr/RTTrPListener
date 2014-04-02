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
			m_multicast_port = multicast_port;
			m_multicast_address = address::from_string(multicast_address);
			m_callbackfunc = callbackfunc;
			m_listen_address = address::from_string(listen_address);

			udp::endpoint listen_endpoint(m_listen_address, m_multicast_port);
			m_socket.open(listen_endpoint.protocol());
			m_socket.set_option(udp::socket::reuse_address(true));
			m_socket.bind(listen_endpoint);

			m_socket.set_option(multicast::join_group(m_multicast_address));

			m_socket.async_receive_from(
				boost::asio::buffer(m_data, max_length), m_sender_endpoint,
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
			m_service.run();
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	int Listener::Stop(){
		try{
			m_service.stop();
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
			return 1;
		}

		return 0;
	}

	int Listener::Release(){
		return 0;
	}

	void Listener::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
	{
		try{
			RTTRPHeader* header = parseHeader(reinterpret_cast<const unsigned char*>(m_data.c_array()));
			if (m_callbackfunc){
				m_callbackfunc(header);
			}
	
			m_socket.async_receive_from(
				boost::asio::buffer(m_data), m_sender_endpoint,
				boost::bind(&Listener::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}catch(std::exception& e){
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}
}