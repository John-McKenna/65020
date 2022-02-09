#ifndef STRINGPOOL_H
#define STRINGPOOL_H

#include <vector>
#include <unordered_map>

struct String
{
	String();
	String( const char* ptrParam, size_t lengthParam );
	String( const char* cstring );
	bool operator == ( const String& rhs ) const;
	bool operator == ( const char* rhs ) const;
	bool operator < ( const String& rhs ) const;
	size_t hash() const;

	const char* ptr;
	size_t length;
};

namespace std
{
	template<> struct hash<String>
	{
		std::size_t operator()(const String& string) const
		{
			return string.hash();
		}
	};
};

class StringPool
{
	public:
		size_t AddString( const String& str );
		const String& GetString( size_t index ) const;

	private:
		std::unordered_map<String, size_t> m_stringToIndex;
		std::vector<String> m_strings;
};

#endif
