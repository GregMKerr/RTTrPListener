#include <string>
#include <stdint.h>

#ifdef RTTRPLISTENER_EXPORTS
#define RTTRPLISTENER_API __declspec(dllexport) 
#else
#define RTTRPLISTENER_API __declspec(dllimport) 
#endif

typedef void(*callback_function)(RTTRPHeader);

namespace RTTrPListener
{
	class Interface
	{
	public:
		//initialized UDP multicast listener - listen address defaults to 'any'
		static RTTRPLISTENER_API int Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address = "0.0.0.0");

		//
		static RTTRPLISTENER_API int Start();

		//
		static RTTRPLISTENER_API int Stop();
	};
}

struct RTTRPHeader {
	unsigned char signature[4];         // Value = 0x41, 0x54, 0x34, 0x43
	unsigned char version[2];           // Value = 0x00, 0x01
	uint32_t packetID;                  // packet sequence number
	unsigned char packetFormat; // Value = 0x00 (Raw), 0x01 (Protobuf), 0x02 (Thrift)
	uint16_t size;                      // Size of packet including header
	uint32_t context;                   // User-definable context number
	uint8_t numberModules;              // Number of Packet Modules
};