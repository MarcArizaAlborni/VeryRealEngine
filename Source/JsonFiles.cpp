#include "JsonFiles.h"
#include <fstream>
#include <iomanip>




json JSONFiles::Load(const char* File) const
{

	// MYTODO: Use PhysFS and check if file exists!

	bool ret = true;

	// --- Create JSON object ---
	json jsonfile;

	if (File == nullptr)
	{
		ret = false;
		
	}

	else
	{

		// --- Load File ---
		std::ifstream ifs;
		ifs.open(File);

		if (!ifs.is_open())
		{
			
			ret = false;
		}

		else
		{
			// --- Parse File, put data in jsonfile ---
			try
			{
				jsonfile = json::parse(ifs);
			}
			catch (json::parse_error& e)
			{
			
			}

			ifs.close();

		}

	}

	return jsonfile;
}