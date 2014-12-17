/***
* Filereader for linux and windows
**/
#pragma once
#ifndef FILEREADER_H_UTH
#define FILEREADER_H_UTH

#include <cstdio>
#include <string>
#include <fstream>
#include <physfs/physfs.h>
#include <UtH/Platform/BinaryData.hpp>

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

		static bool isCompressed;
	private:
		std::FILE* file;
		PHYSFS_file* cFile;
        bool m_writable;
	};
}

#endif