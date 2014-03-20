#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

using namespace boost::asio::ip;

class Receiver;

class Receiver{
public:
	Receiver(boost::asio::io_service& io_service) : m_socket(io_service)
	{
	}

	int init(){
		boost::asio::ip::address ipAddr = boost::asio::ip::address_v4::any();//from_string("238.210.10.1")
		boost::asio::ip::udp::endpoint listen_endpoint(ipAddr, 59261);

		std::cout << listen_endpoint << std::endl;

		try{
		m_socket.open(listen_endpoint.protocol());
		m_socket.bind(listen_endpoint);

		m_socket.async_receive_from(
			boost::asio::buffer(m_data), m_sender_endpoint,
			boost::bind(&Receiver::handle_receive_from, this, boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		}
		catch (std::exception& e)
		{
			std::cout << "Standard exception: " << e.what() << std::endl;
		}

		return 0;
	}

private:
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

	udp::socket m_socket;
	udp::endpoint m_sender_endpoint;
	boost::array<char, 100> m_data;
};


int main(int argc, char* argv[])
{
	boost::asio::io_service service;
	Receiver rec(service);
	if (rec.init() != 0) { return 1; }
	service.run();

	while(1){}

	return 0;

	//try
	//{
	//	boost::asio::io_service io_service;

	//	udp::socket socket(io_service, udp::endpoint(udp::v4(), 59261));

	//	udp::endpoint sender_endpoint;

	//	// Receive data.
	//	boost::array<char, 4> buffer;
	//	std::size_t bytes_transferred = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

	//	std::cout << "got " << bytes_transferred << " bytes." << std::endl;
	//	
	//}
	//catch (std::exception& e)
	//{
	//	std::cout << "Standard exception: " << e.what() << std::endl;
	//}

	//int test;
	//std::cin >> test;
}