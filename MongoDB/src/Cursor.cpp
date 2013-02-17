//
// Cursor.cpp
//
// $Id$
//
// Library: MongoDB
// Package: MongoDB
// Module:  Cursor
//
// Implementation of the Cursor class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include "Poco/MongoDB/Cursor.h"
#include "Poco/MongoDB/GetMoreRequest.h"
#include "Poco/MongoDB/KillCursorsRequest.h"

namespace Poco
{
namespace MongoDB
{


Cursor::Cursor(const std::string& db, const std::string& collection, QueryRequest::Flags flags)
	: _query(db + '.' + collection, flags)
{
}


Cursor::Cursor(const std::string& fullCollectionName, QueryRequest::Flags flags)
	: _query(fullCollectionName, flags)
{
}


Cursor::~Cursor()
{
	poco_assert_dbg(_response.cursorID());
}


ResponseMessage& Cursor::next(Connection& connection)
{
	if ( _response.cursorID() == 0 )
	{
		connection.sendRequest(_query, _response);
	}
	else
	{
		Poco::MongoDB::GetMoreRequest getMore(_query.fullCollectionName(), _response.cursorID());
		getMore.setNumberToReturn(_query.getNumberToReturn());
		_response.clear();
		connection.sendRequest(getMore, _response);
	}
	return _response;
}


void Cursor::kill(Connection& connection)
{
	if ( _response.cursorID() != 0 )
	{
		KillCursorsRequest killRequest;
		killRequest.cursors().push_back(_response.cursorID());
		connection.sendRequest(killRequest);
	}
	_response.clear();
}

} } // Namespace Poco::MongoDB

