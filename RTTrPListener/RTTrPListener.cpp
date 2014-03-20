#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

using namespace boost::asio::ip;

class Receiver;

class Receiver{
public:
	Receiver(boost::asio::io_service& io_service)
		: m_socket(io_service)
	{

		boost::asio::ip::address ipAddr = boost::asio::ip::address_v4::any();
		boost::asio::ip::udp::endpoint listen_endpoint(ipAddr, 24002);

		m_socket.open(listen_endpoint.protocol());
		m_socket.bind(listen_endpoint);

		m_socket.async_receive_from(
			boost::asio::buffer(m_data), m_sender_endpoint,
			boost::bind(&Receiver::handle_receive_from, this, boost::asio::placeholders::error, 
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive_from(const boost::system::error_code& error,
	  size_t bytes_recvd)
	{
	std::cout << "receive" << bytes_recvd << std::endl;


	  m_socket.async_receive_from(
		  boost::asio::buffer(m_data), m_sender_endpoint,
		  boost::bind(&Receiver::handle_receive_from, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

private:
	udp::socket m_socket;
	udp::endpoint m_sender_endpoint;
	boost::array<char, 100> m_data;
};


int main(int argc, char* argv[])
{
	boost::asio::io_service service;
	Receiver rec(service);

	service.run();

	while(1){}

	return 0;
}