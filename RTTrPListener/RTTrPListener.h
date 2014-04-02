#include <string>
#include <stdint.h>

#include "blacktrax_third_party_protocol.h"

#ifdef RTTRPLISTENER_EXPORTS
#define RTTRPLISTENER_API __declspec(dllexport)
#else
#define RTTRPLISTENER_API __declspec(dllimport)
#endif

typedef void(*callback_function)(RTTRPHeader*);

namespace RTTrPListener
{
	struct IListener
	{
		//initialized UDP multicast listener - listen address defaults to 'any'
		virtual int Init(const int multicast_port, const std::string multicast_address, callback_function callbackfunc, const std::string listen_address = "0.0.0.0");

		//
		virtual int Start();

		//
		virtual int Stop();
	};

	extern "C" RTTRPLISTENER_API Interface* APIENTRY GetIListener();
}
