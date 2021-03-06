/*!
 *  @file		AppleMIDI_EndSession.h
 *  Project		Arduino AppleMIDI Library
 *	@brief		AppleMIDI Library for the Arduino 
 *	Version		0.3
 *  @author		lathoub 
 *	@date		04/04/14
 *  License		GPL
 */

#pragma once

#include "utility/AppleMidi_Settings.h"
#include "utility/AppleMidi_Defs.h"
#include "utility/AppleMidi_Util.h"

BEGIN_APPLEMIDI_NAMESPACE
	
typedef struct AppleMIDI_EndSession {

	uint8_t		signature[2];
	uint8_t		command[2];
	uint32_t	version;
	uint32_t	initiatorToken;
	uint32_t	ssrc;


	inline AppleMIDI_EndSession()
	{
		init();
	}

	void init()
	{
		memcpy(signature, amSignature, sizeof(amSignature));
		memcpy(command, amEndSession, sizeof(amEndSession));
	}

	void write(EthernetUDP* udp)
	{
		udp->beginPacket(udp->remoteIP(), udp->remotePort());

		udp->write(signature, sizeof(signature));
		udp->write(command,   sizeof(command));

		// To appropriate endian conversion
		uint32_t _version = AppleMIDI_Util::toEndian(version);
		uint32_t _initiatorToken = AppleMIDI_Util::toEndian(initiatorToken);
		uint32_t _ssrc = AppleMIDI_Util::toEndian(ssrc);

		// write then out
		udp->write((uint8_t*) ((void*) (&_version)), sizeof(_version));
		udp->write((uint8_t*) ((void*) (&_initiatorToken)), sizeof(_initiatorToken));
		udp->write((uint8_t*) ((void*) (&_ssrc)), sizeof(_ssrc));

		udp->endPacket(); 
		udp->flush(); // Waits for the transmission of outgoing serial data to complete
	}

} EndSession_t;

END_APPLEMIDI_NAMESPACE
