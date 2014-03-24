

int main(int argc, char* argv[])
{
	Receiver rec(service, address::from_string("0.0.0.0"), address::from_string("238.210.10.1"));
	if (rec.init() != 0) { return 1; }
	service.run();

	while (1){}

	return 0;
}