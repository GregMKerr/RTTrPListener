#include <exception>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost\array.hpp>

using namespace boost::asio::ip;

const int multicast_port = 24002;

class Receiver{
public:
	//io_service, listen_address, multicast_address
	Receiver(boost::asio::io_service& io_service, const address& listen_address, const address& multicast_address)
		: socket(io_service), listen_address(listen_address), multicast_address(multicast_address)
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
				boost::bind(&Receiver::handle_receive_from, this, boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		catch (std::exception& e)
		{
			std::cout << "Standard exception: " << e.what() << std::endl;
		}

		return 0;
	}

	void handle_receive_from(const boost::system::error_code& error,
	  size_t bytes_recvd)
	{
		std::cout << "receive" << bytes_recvd << std::endl;

		socket.async_receive_from(
			boost::asio::buffer(data), sender_endpoint,
			boost::bind(&Receiver::handle_receive_from, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	
private:
	udp::socket socket;
	udp::endpoint sender_endpoint;
	const address& listen_address;
	const address& multicast_address;
	enum { max_length = 1024};
	boost::array<char, max_length> data;
};


int main(int argc, char* argv[])
{
	boost::asio::io_service service;
	Receiver rec(service, address::from_string("0.0.0.0"), address::from_string("238.210.10.1"));
	if (rec.init() != 0) { return 1; }
	service.run();

	while(1){}

	return 0;
}