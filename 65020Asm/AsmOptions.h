#ifndef ASMOPTIONS_H
#define ASMOPTIONS_H

#include <vector>

class AsmOptions
{
	public:
		std::vector<const char*> inputFileNames;
		const char* outputFileName;
		const char* memFileName;
		std::vector<const char*> inputPaths;
		const char* crossReferenceFileName;
		const char* listingFileName;

		AsmOptions();
		void ParseCommandLine( int argc, char* argv[] );

	private:
		const char* ReadParameter( int& i, int argc, char* argv[], const char* parameterType );
};

#endif
