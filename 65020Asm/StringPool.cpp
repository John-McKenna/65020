#include "StringPool.h"
#include "Errors.h"
#include <memory.h>
#include <ctype.h>
#include <algorithm>

String::String()
{
	ptr = nullptr;
	length = 0;
}

String::String( const char* ptrParam, size_t lengthParam )
{
	ptr = ptrParam;
	length = lengthParam;
}

String::String( const char* cstring )
{
	ptr = cstring;
	length = strlen( cstring );
}

bool String::operator == ( const String& rhs ) const
{
	if ( length != rhs.length )
	{
		return false;
	}
	return _strnicmp( ptr, rhs.ptr, length ) == 0;
}

bool String::operator == ( const char* rhs ) const
{
	if ( length != strlen(rhs) )
	{
		return false;
	}
	return _strnicmp( ptr, rhs, length ) == 0;
}

bool String::operator < ( const String& rhs ) const
{
	size_t minLength = std::min( length, rhs.length );
	int result = _strnicmp( ptr, rhs.ptr, minLength );
	if ( result == 0 )
	{
		return length < rhs.length;
	}
	return result == -1;
}

size_t String::hash() const
{
	size_t init;
	size_t prime;
	switch ( sizeof(size_t) )
	{
		case 4:
			init = (size_t)0x811c9dc5;
			prime = (size_t)16777619;
			break;
		case 8:
			init = (size_t)0xcbf29ce484222325ull;
			prime = (size_t)1099511628211ull;
			break;
		default:
			Error( nullptr, nullptr, "size_t is an unhandled size" );
	}
	size_t result = init;
	const uint8_t* data = (const uint8_t*)ptr;
	for ( size_t i = 0; i < length; i++ )
	{
		result = result ^ tolower(data[i]);
		result = result * prime;
	}
	return result;
}

size_t StringPool::AddString( const String& str )
{
	auto result = m_stringToIndex.find(str);
	if ( result == m_stringToIndex.end() )
	{
		// this is a new string
		size_t index = m_strings.size();
		m_strings.push_back( str );
		m_stringToIndex[str] = index;
		return index;
	}
	else
	{
		// already have this string
		return result->second;
	}
}

const String& StringPool::GetString( size_t index ) const
{
	return m_strings[index];
}
