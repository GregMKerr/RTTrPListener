#include <string>
#include <stdint.h>

#include "blacktrax_third_party_protocol.h"

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
		virtual RTTRPLISTENER_API int Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address = "0.0.0.0");

		//
		virtual RTTRPLISTENER_API int Start();

		//
		virtual RTTRPLISTENER_API int Stop();
	};

	//extern
}
