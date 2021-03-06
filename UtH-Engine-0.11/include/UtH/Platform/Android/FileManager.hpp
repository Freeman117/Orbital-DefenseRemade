/***
 * Android Specific filereader
 **/
#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstdio>
#include <string>
#include <fstream>
#include <UtH/Platform/BinaryData.hpp>

struct AAssetManager;
struct AAsset;

namespace uth
{
	class FileManager
	{
	public:
		enum class Location
		{
			ASSET = 0,
			EXTERNAL = 1,
			INTERNAL = 2,
		};

		FileManager();
        FileManager(const std::string& path, const Location = Location::ASSET, bool isWritable = false);
		~FileManager();

     
        bool OpenFile(const std::string& path, const Location = Location::ASSET, bool isWritable = false);
        void CloseFile();
		int GetFileSize();
		
		// Move the file pointer by offset from origin(defaults to beginning of file)
		// see SEEK_SET, SEEK_CUR and SEEK_END
		bool FileSeek(int offset, int origin = SEEK_SET);

		// Read a 'count' ammount of 'blockSize' sized blocks of data from file to buffer
		// Buffer is a pointer to the first element of an array
		// Also sets the file pointer to the end of read block
		bool ReadBytes(void* const buffer, const unsigned int count, const unsigned int blockSize = 1);
		
		// Returns the content of whole file as binary data
		const BINARY_DATA ReadBinary();

		// Returns the content of the whole file as text
		const std::string ReadText();

        // Write text to file.
		void WriteString(const std::string& data);

		void WriteBytes(const void* const buffer, const unsigned int count, const unsigned int blockSize = 1);
		void WriteBinary(const BINARY_DATA& data);

		static AAssetManager* m_manager;
		
		
		static AAsset* loadSound(const std::string& fileName);

		static int64_t getAssetLength(void* asset);
		static int64_t seekAsset(int64_t offset, int whence, void* asset);
		static int64_t readAsset(void* buffer, int64_t count, void* asset);
		static int64_t tellAsset(void* asset);
		
	private:
		std::fstream m_stream;
		AAsset* m_asset;
        bool m_writable;
	};
}

#endif