#ifndef BLACKTRAX_THIRD_PARTY_PROTOCOL_H_
#define BLACKTRAX_THIRD_PARTY_PROTOCOL_H_

#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include <cstdio>

typedef unsigned char uint8_t;

struct ModuleHeader {
    uint8_t type;               // Type of module
    uint16_t size;              // size of module    
};

struct RTTRPHeader {
	unsigned char signature[4];         // Value = 0x41, 0x54, 0x34, 0x43
	unsigned char version[2];           // Value = 0x00, 0x01
	uint32_t packetID;                  // packet sequence number
	unsigned char packetFormat; // Value = 0x00 (Raw), 0x01 (Protobuf), 0x02 (Thrift)
	uint16_t size;                      // Size of packet including header
	uint32_t context;                   // User-definable context number
	uint8_t numberModules;              // Number of Packet Modules
};

struct TrackableModule {
    uint8_t type;
    uint16_t size; 
	uint8_t nameLength;
	char* name;
	uint8_t numberModules;
};

struct CentroidPositionModule {
    uint8_t type;
    uint16_t size;
	uint16_t latency;
	double x;
	double y;
	double z;
};

struct EulerOrientation {
    uint8_t type;
    uint16_t size;
	uint16_t latency;
	uint16_t order;
	double r1;
	double r2;
	double r3;
};

struct QuaternionOrientation {
    uint8_t type;
    uint16_t size;
	uint16_t latency;
	double Qx;
	double Qy;
	double Qz;
	double Qw;
};

struct LedPositionModule {
    uint8_t type;
    uint16_t size;
	uint16_t latency;
	double x;
	double y;
	double z;
	uint8_t index;
};

struct FixtureModule {
    uint8_t type;
    uint16_t size;
	uint32_t spotNumber;
	uint8_t inverseTilt;
	uint8_t inversePan;
	uint8_t numberModules;
};

struct FixtureModule* new_FixtureModule(
		const unsigned char * packet, int index) {
	struct FixtureModule* module = 
		(struct FixtureModule*) malloc(sizeof(struct FixtureModule));
	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->spotNumber), &packet[index+3], 4);
	memcpy(&(module->inverseTilt), &packet[index+7], 1);
	memcpy(&(module->inversePan), &packet[index+8], 1);
	memcpy(&(module->numberModules), &packet[index+9], 1);
	module->size = _byteswap_ushort(module->size);
	module->spotNumber = _byteswap_ulong(module->spotNumber);
	return module;
}

void delete_FixtureModule(struct FixtureModule* module) {
	free(module);
}

void Print(const struct FixtureModule* module) {
	printf("%-27s", "\nFixture Module: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("spotNumber: %-10u ", module->spotNumber);
	printf("inverseTilt: %-1hhu ", module->inversePan);
	printf("inversePan: %-1hhu ", module->inversePan);
	printf("numberModules: %-3u ", module->numberModules);
}

struct LedPositionModule* new_LedPositionModule(
		const unsigned char * packet, int index) {
	struct LedPositionModule* module = 
		(struct LedPositionModule*) malloc(sizeof(struct LedPositionModule));

	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->latency), &packet[index+3], 2);
	memcpy(&(module->x), &packet[index+5], 8);
	memcpy(&(module->y), &packet[index+13], 8);
	memcpy(&(module->z), &packet[index+21], 8);
	memcpy(&(module->index), &packet[index+29], 1);
	module->size = _byteswap_ushort(module->size);
	module->latency = _byteswap_ushort(module->latency);
	return module;
}

void delete_LedPositionModule(struct LedPositionModule* module) {
	free(module);
}

void Print(const struct LedPositionModule* module) {
	printf("%-27s", "\nCentroid Position Module:");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("latency: %-5hu ", module->latency);
	printf("x: %-8f ", module->x);
	printf("y: %-8f ", module->y);
	printf("z: %-8f ", module->z);
	printf("index: %-1hu ", module->index);
}

struct QuaternionOrientation* new_QuaternionOrientation(
		const unsigned char * packet, int index) {
	struct QuaternionOrientation* module = 
		(struct QuaternionOrientation*) malloc(sizeof(struct QuaternionOrientation));

	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->latency), &packet[index+3], 2);
	memcpy(&(module->Qx), &packet[index+5], 8);
	memcpy(&(module->Qy), &packet[index+13], 8);
	memcpy(&(module->Qz), &packet[index+21], 8);
	memcpy(&(module->Qw), &packet[index+29], 8);
	module->size = _byteswap_ushort(module->size);
	module->latency = _byteswap_ushort(module->latency);
	return module;
}

void delete_QuaternionOrientation(struct QuaternionOrientation* module) {
	free(module);
}

void Print(const struct QuaternionOrientation* module) {
	printf("%-27s", "\nCentroid Position Module: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("latency: %-5hu ", module->latency);
	printf("Qx: %-8f ", module->Qx);
	printf("Qy: %-8f ", module->Qy);
	printf("Qz: %-8f ", module->Qz);
	printf("Qw: %-8f ", module->Qw);
}

struct EulerOrientation* new_EulerOrientation(
		const unsigned char * packet, int index) {
	struct EulerOrientation* module = 
		(struct EulerOrientation*) malloc(sizeof(struct EulerOrientation));

	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->latency), &packet[index+3], 2);
	memcpy(&(module->order), &packet[index+5], 2);
	memcpy(&(module->r1), &packet[index+7], 8);
	memcpy(&(module->r2), &packet[index+15], 8);
	memcpy(&(module->r3), &packet[index+23], 8);
	module->size = _byteswap_ushort(module->size);
	module->latency = _byteswap_ushort(module->latency);
	module->order = _byteswap_ushort(module->order);
	return module;
}

void delete_EulerOrientation(struct EulerOrientation* module) {
	free(module);
}

void Print(const struct EulerOrientation* module) {
	printf("%-27s", "\nCentroid Position Module: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("latency: %-5hu ", module->latency);
	printf("order: 0x%-3x ", module->order);
	printf("r1: %-8f ", module->r1);
	printf("r2: %-8f ", module->r2);
	printf("r3: %-8f ", module->r3);
}

struct CentroidPositionModule* new_CentroidPositionModule(
		const unsigned char * packet, int index) {
	struct CentroidPositionModule* module = 
		(struct CentroidPositionModule*) malloc(sizeof(struct CentroidPositionModule));

	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->latency), &packet[index+3], 2);
	memcpy(&(module->x), &packet[index+5], 8);
	memcpy(&(module->y), &packet[index+13], 8);
	memcpy(&(module->z), &packet[index+21], 8);
	module->size = _byteswap_ushort(module->size);
	module->latency = _byteswap_ushort(module->latency);
	return module;
}

void delete_CentroidPositionModule(struct CentroidPositionModule* module) {
	free(module);
}

void Print(const struct CentroidPositionModule* module) {
	printf("%-27s","\nCentroid Position Module: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("latency: %-5hu ", module->latency);
	printf("x: %-8f ", module->x);
	printf("y: %-8f ", module->y);
	printf("z: %-8f ", module->z);
}

struct TrackableModule* new_TrackableModule(
		const unsigned char * packet, int index) {
	struct TrackableModule* module = 
		(struct TrackableModule*) malloc(sizeof(struct TrackableModule));
	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	memcpy(&(module->nameLength), &packet[index+3], 1);
	module->name = (char*)malloc(module->nameLength+1);
	module->name[module->nameLength] = 0;
	memcpy(module->name, &packet[index+4], module->nameLength);
	index  = index + 4 + module->nameLength;
	memcpy(&(module->numberModules), &packet[index], 1);
	module->size = _byteswap_ushort(module->size);
	return module;
}

void delete_TrackableModule(struct TrackableModule* module) {
	free(module->name);
	free(module);
}

void Print(const struct TrackableModule* module) {
	printf("%-27s", "\nTrackable Module: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu ", module->size);
	printf("nameLength: %-5u ", module->nameLength);
	printf("name: %-10s ", module->name);
	printf("numberModules: %-3u ", module->numberModules);
}

struct ModuleHeader* new_ModuleHeader(
		const unsigned char * packet, int index) {
	struct ModuleHeader* module =
		(struct ModuleHeader*) malloc(sizeof(struct ModuleHeader));

	memcpy(&(module->type), &packet[index], 1);
	memcpy(&(module->size), &packet[index+1], 2);
	module->size = _byteswap_ushort(module->size);
	return module;
}

void delete_ModuleHeader(struct ModuleHeader* module) {
	free(module);
}

void Print(const struct ModuleHeader* module) {
	printf("%-27s", "\nModule Packet: ");
	printf("type: %-2u ", module->type);
	printf("size: %-4hu", module->size);
}

struct RTTRPHeader* new_RTTRPHeader(const unsigned char * packet) {
	struct RTTRPHeader* header =
		(struct RTTRPHeader*) malloc(sizeof(struct RTTRPHeader));
	memcpy(header->signature, &packet[0], 4);
	memcpy(header->version, &packet[4], 2);
	memcpy(&(header->packetID), &packet[6], 4);
	memcpy(&(header->packetFormat), &packet[10], 1);
	memcpy(&(header->size), &packet[11], 2);
	memcpy(&(header->context), &packet[13], 4);
	memcpy(&(header->numberModules), &packet[17], 1);
	header->size = _byteswap_ushort(header->size);
	header->context = _byteswap_ulong(header->context);
	header->packetID = _byteswap_ulong(header->packetID);
	return header;
}

void delete_RTTRPHeader(struct RTTRPHeader* module) {
	free(module);
}

void Print(const struct RTTRPHeader* header) {
	if(header == NULL) return;
	printf("%-27s", "\nHeader Packet: ");
	printf("signature: %-4s ", (char *)&(header->signature));
	printf("version: %-2s ", (char *)&(header->version));
	printf("packetID: %-5u ", header->packetID);
	printf("packetFormat: %-1c", header->packetFormat);
	printf("size: %-4hu ", header->size);
	printf("context: %-10u ", header->context);
	printf("numberModules: %-3hhu", header->numberModules);
}

struct TrackableModule* parseTrackable(
		const unsigned char * packet, int index) {

	struct TrackableModule* module = new_TrackableModule(packet, index);
	index = index + 5 + module->nameLength;
	Print(module);
	int i = 0;
	while(i < module->numberModules) {
		struct ModuleHeader * header = new_ModuleHeader(packet, index);
		Print(header);
		if(header->type == 2) {
			struct CentroidPositionModule* position = 
				new_CentroidPositionModule(packet, index);
			Print(position);
			delete_CentroidPositionModule(position);
		} else if(header->type == 3) {
			struct QuaternionOrientation* or = new_QuaternionOrientation(packet, index);
			Print(or);
			delete_QuaternionOrientation(or);
		} else if(header->type == 4) {
			struct EulerOrientation* orientation  = new_EulerOrientation(packet, index);
			Print(orientation);
			delete_EulerOrientation(orientation);
		} else if(header->type == 6) {
			struct LedPositionModule* position = new_LedPositionModule(packet, index);
			Print(position);
			delete_LedPositionModule(position);
		}
		index = index + header->size;
		i++;
		delete_ModuleHeader(header);
	}
	return module;
}

struct RTTRPHeader* parseHeader(const unsigned char * packet) {
	struct RTTRPHeader* header = new_RTTRPHeader(packet);
	if(header == NULL) return NULL;
	if(header->signature[0] != 'A' && header->signature[1] != 'T' &&
		header->signature[2] != '4' && header->signature[3] != 'C') {
		free(header);
		printf("Error: packet signiture mismatch!");
		return NULL;
	}
	int i = 0;
	int index = 18;
	Print(header);

	while(i < header->numberModules) {
		struct ModuleHeader * moduleHeader = new_ModuleHeader(packet, index);
		Print(moduleHeader);

		if(moduleHeader->type == 1) {
			struct TrackableModule* trackable = parseTrackable(packet, index);
			delete_TrackableModule(trackable);
		} else if(moduleHeader->type == 5) {
			//ignored atm.
		}

		index = index + moduleHeader->size;
		i++;
		delete_ModuleHeader(moduleHeader);
	}
	
	return header;
}

#endif /* BLACKTRAX_THIRD_PARTY_PROTOCOL_H_ */
