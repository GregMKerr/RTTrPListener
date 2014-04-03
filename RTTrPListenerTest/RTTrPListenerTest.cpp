#include <memory>
#include <functional>

#include "RTTrPListener.h"
#include "blacktrax_third_party_protocol.h"

typedef std::shared_ptr<RTTrPListener::IListener> IListenerPtr;

int main(int argc, char* argv[])
{
	IListenerPtr listenerPtr(::GetIListener(), std::mem_fn(&RTTrPListener::IListener::Release));

	if(listenerPtr)
	{
	    listenerPtr->Init(24002, "238.210.10.1", listenerCallbackFunc);
	}

	return 0;
}

static void listenerCallbackFunc(RTTRPHeader* header){
	Print(header);
}
