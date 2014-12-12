//
// SNMPEventArgs.cpp
//
// $Id: //poco/1.4/Net/src/SNMPEventArgs.cpp#1 $
//
// Library: Net
// Package: SNMP
// Module:  SNMPEventArgs
//
// Implementation of SNMPEventArgs
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/SNMPEventArgs.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/DNS.h"
#include "Poco/Exception.h"
#include "Poco/Net/NetException.h"
#include <numeric>


using Poco::IOException;
using Poco::InvalidArgumentException;


namespace Poco {
namespace Net {


SNMPEventArgs::SNMPEventArgs(const SocketAddress& address):
	_address(address), 
	_message()
{
}


SNMPEventArgs::~SNMPEventArgs()
{
}


std::string SNMPEventArgs::hostName() const
{
	try
	{
		return DNS::resolve(_address.host().toString()).name();
	}
	catch (HostNotFoundException&) 
	{
	}
	catch (NoAddressFoundException&) 
	{
	}
	catch (DNSException&)
	{
	}
	catch (IOException&)
	{
	}
	return _address.host().toString();
}


std::string SNMPEventArgs::hostAddress() const
{
	return _address.host().toString();
}


SNMPTypes::SNMPMessage::Ptr SNMPEventArgs::message() const
{
	return _message;
}


const std::string &SNMPEventArgs::error() const
{
	return _error;
}


void SNMPEventArgs::setMessage(SNMPTypes::SNMPMessage::Ptr message)
{
	_message = message;
}


void SNMPEventArgs::setError(const std::string &error)
{
	_error = error;
}


} } // namespace Poco::Net
