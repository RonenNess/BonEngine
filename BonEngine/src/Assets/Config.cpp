#include <Assets/Types/Config.h>
#include <Framework/PointF.h>
#include <Framework/Exceptions.h>
#include <string>
#include <list>
using namespace bon::framework;

namespace bon
{
	namespace assets
	{
		// get a string in format of "x,y", and extract x and y components from it.
		void SplitPointStr(const std::string& str, float& outX, float& outY)
		{
			try
			{
				std::string xStr = str.substr(0, str.find(','));
				outX = std::stof(xStr);
				std::string yStr = str.substr(str.find(',') + 1);
				outY = std::stof(yStr);
			}
			catch (const std::exception&)
			{
				throw framework::AssetLoadError("Invalid point format in config file! Must be 'x,y'.");
			}
		}

		// split string by delimiter
		void SplitString(const std::string& s, char delimiter, std::list<std::string>& outList)
		{
			size_t last = 0; 
			size_t next = 0; 
			while ((next = s.find(delimiter, last)) != string::npos) 
			{ 
				outList.push_back(s.substr(last, next - last));
				last = next + 1; 
			} 
			outList.push_back(s.substr(last));
		}

		// get pointf from config
		framework::PointF _Config::GetPointF(const char* section, const char* name, const framework::PointF& defaultVal) const
		{
			PointF ret;
			const char* asStr = GetStr(section, name, nullptr);
			if (asStr == nullptr) { return defaultVal; }
			SplitPointStr(asStr, ret.X, ret.Y);
			return ret;
		}

		// get color from config
		framework::Color _Config::GetColor(const char* section, const char* name, const framework::Color& defaultVal) const
		{
			// get string and return default if not set
			const char* asStr = GetStr(section, name, nullptr);
			if (asStr == nullptr) { return defaultVal; }

			// break and parse
			std::list<std::string> parts;
			SplitString(asStr, ',', parts);
			Color ret;
			auto iter = parts.begin();
			ret.R = (float)std::stoi(*iter) / 255.0f; iter++;
			ret.G = (float)std::stoi(*iter) / 255.0f; iter++;
			ret.B = (float)std::stoi(*iter) / 255.0f; iter++;
			if (iter != parts.end()) { ret.A = (float)std::stoi(*iter) / 255.0f; }
			return ret;
		}

		// get rect from config
		framework::RectangleF _Config::GetRectangleF(const char* section, const char* name, const framework::RectangleF& defaultVal) const
		{
			// get string and return default if not set
			const char* asStr = GetStr(section, name, nullptr);
			if (asStr == nullptr) { return defaultVal; }

			// break and parse
			std::list<std::string> parts;
			SplitString(asStr, ',', parts);
			framework::RectangleF ret;
			auto iter = parts.begin();
			ret.X = (float)std::stoi(*iter); iter++;
			ret.Y = (float)std::stoi(*iter); iter++;
			ret.Width = (float)std::stoi(*iter); iter++;
			ret.Height = (float)std::stoi(*iter); 
			return ret;
		}

		// get option index from config
		int _Config::GetOption(const char* section, const char* name, const char* options[], int optionsCount, int defaultVal) const
		{
			// get config as string and return default val if not exist
			const char* asStr = GetStr(section, name, nullptr);
			if (!asStr) { return defaultVal; }

			// find value index
			for (int i = 0; i < optionsCount; ++i)
			{
				if (strcmp(asStr, options[i]) == 0) {
					return i;
				}
			}

			// invalid value
			throw framework::InvalidValue((std::string("Invalid config value: '") + asStr + "': value is not one of the given options.").c_str());
		}
	}
}