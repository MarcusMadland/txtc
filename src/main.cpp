/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <algorithm>

#include <bx/string.h>

#include <tinystl/allocator.h>
#include <tinystl/string.h>
#include <tinystl/vector.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

#define TXTC_VERSION_MAJOR 1
#define TXTC_VERSION_MINOR 0

#if 0
#	define BX_TRACE(_format, ...) \
		do { \
			bx::printf(BX_FILE_LINE_LITERAL "BGFX " _format "\n", ##__VA_ARGS__); \
		} while(0)

#	define BX_WARN(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				BX_TRACE(BX_FILE_LINE_LITERAL "WARN " _format, ##__VA_ARGS__); \
			} \
		} while(0)

#	define BX_ASSERT(_condition, _format, ...) \
		do { \
			if (!(_condition) ) \
			{ \
				BX_TRACE(BX_FILE_LINE_LITERAL "CHECK " _format, ##__VA_ARGS__); \
				bx::debugBreak(); \
			} \
		} while(0)
#endif // 0

#include <bx/bx.h>
#include <bx/bounds.h>
#include <bx/commandline.h>
#include <bx/debug.h>
#include <bx/file.h>
#include <bx/hash.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>

void processFile(const bx::FilePath& _inFilePath, const bx::FilePath& _outFilePath)
{
	bx::FileReader fr;
	if (!bx::open(&fr, _inFilePath))
	{
		bx::printf("Unable to open file '%s'.\n", _inFilePath);
		return;
	}

	bx::FileWriter fw;
	if (!bx::open(&fw, _outFilePath))
	{
		bx::printf("Unable to write file '%s'.\n", _outFilePath);
		return;
	}

	const int32_t bufferSize = 4096;
	char buffer[bufferSize];
	int32_t bytesRead;

	bx::ErrorIgnore err;
	while ((bytesRead = bx::read(&fr, buffer, bufferSize, &err)) > 0)
	{
		if (bx::write(&fw, buffer, bytesRead, &err) != bytesRead)
		{
			bx::printf("Failed to write file %s.\n", _outFilePath);
			break;
		}
	}

	bx::close(&fr);
	bx::close(&fw);
}

void processDirectory(const bx::FilePath& folderPath, const bx::FilePath& outFolderPath, bool recursive)
{
	bx::ErrorIgnore err;

	bx::DirectoryReader dr;
	if (!bx::open(&dr, folderPath))
	{
		bx::printf("Unable to open input folder '%s'.\n", folderPath.getCPtr());
		return;
	}

	bx::FileInfo fileInfo;
	while (bx::read(&dr, &fileInfo, sizeof(fileInfo), &err) > 0)
	{
		if (fileInfo.type == bx::FileType::File)
		{
			const bx::FilePath filePath = fileInfo.filePath;

			bx::StringView ext = filePath.getExt();
			if (0 == bx::strCmpI(ext, ".h") ||
				0 == bx::strCmpI(ext, ".c") ||
				0 == bx::strCmpI(ext, ".hpp") ||
				0 == bx::strCmpI(ext, ".cpp"))
			{
				bx::FilePath inFilePath = folderPath;
				inFilePath.join(filePath.getFileName());

				bx::FilePath outFilePath = outFolderPath;
				stl::string fileName = filePath.getFileName().getPtr();
				fileName.append(".txt");
				outFilePath.join(fileName.c_str());

				processFile(inFilePath, outFilePath);
			}
			else
			{
				bx::printf("Unsupported input file format '%s', skipping this file...\n", filePath.getCPtr());
			}
		}
		else if (fileInfo.type == bx::FileType::Dir && recursive)
		{
			if (0 != bx::strCmp(fileInfo.filePath.getCPtr(), ".") &&
				0 != bx::strCmp(fileInfo.filePath.getCPtr(), ".."))
			{
				bx::FilePath subFolderPath = folderPath;
				subFolderPath.join(fileInfo.filePath.getFileName());

				bx::FilePath subOutFolderPath = outFolderPath;
				subOutFolderPath.join(fileInfo.filePath.getFileName());

				if (!bx::makeAll(subOutFolderPath))
				{
					bx::printf("Unable to make output directory '%s'.\n", subOutFolderPath);
					return;
				}

				processDirectory(subFolderPath, subOutFolderPath, true);
			}
		}
	}

	bx::close(&dr);
}


void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		bx::printf("Error:\n%s\n\n", _error);
	}

	bx::printf(
		  "txtc, source to txt converter tool, version %d.%d.\n"
		  "Copyright 2024 Marcus Madland. All rights reserved.\n"
		  "License: https://github.com/marcusmadland/txtc/blob/main/LICENSE\n\n"
		, TXTC_VERSION_MAJOR
		, TXTC_VERSION_MINOR
		);

	bx::printf(
		  "Usage: txtc -f <in> -o <out>\n"

		  "\n"
		  "Supported input file types:\n"
		  "    *.h					  C Headers\n"
		  "    *.c					  C Source\n"
		  "    *.hpp				  C++ Headers\n"
		  "    *.cpp                  C++ Source\n"

		  "\n"
		  "Options:\n"
		  "  -h, --help               Display this help and exit.\n"
		  "  -v, --version            Output version information and exit.\n"
		  "  -f <file path>           Input's file path.\n"
		  "  -o <file path>           Output's file path.\n"
		  "	 -r, --recursive		  Convert folders recursivly."

		  "\n"
		  "For additional information, see https://github.com/marcusmadland/txtc\n"
		);
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('v', "version") )
	{
		bx::printf(
			"txtc, source to txt converter tool, version %d.%d.\n"
			, TXTC_VERSION_MAJOR
			, TXTC_VERSION_MINOR
		);
		return bx::kExitSuccess;
	}

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return bx::kExitFailure;
	}

	const char* folderPath = cmdLine.findOption('f');
	if (NULL == folderPath)
	{
		help("Input folder name must be specified.\n");
		return bx::kExitFailure;
	}

	const char* outFolderPath = cmdLine.findOption('o');
	if (NULL == outFolderPath)
	{
		help("Output folder name must be specified.\n");
		return bx::kExitFailure;
	}

	bool recursive = cmdLine.hasArg('r', "recursive");

	bx::ErrorIgnore err;

	if (!bx::makeAll(outFolderPath))
	{
		bx::printf("Unable to make output directory '%s'.\n", outFolderPath);
		return bx::kExitFailure;
	}

	processDirectory(folderPath, outFolderPath, recursive);
	/*
	bx::DirectoryReader dr;
	if (!bx::open(&dr, folderPath))
	{
		bx::printf("Unable to open input folder '%s'.\n", folderPath);
		return bx::kExitFailure;
	}
	
	bx::FileInfo fileInfo;
	while (bx::read(&dr, &fileInfo, sizeof(fileInfo), &err) > 0)
	{
		if (fileInfo.type == bx::FileType::File)
		{
			const bx::FilePath filePath = fileInfo.filePath;

			bx::StringView ext = filePath.getExt();
			if (0 == bx::strCmpI(ext, ".h") ||
				0 == bx::strCmpI(ext, ".c") ||
				0 == bx::strCmpI(ext, ".hpp") ||
				0 == bx::strCmpI(ext, ".cpp"))
			{
				bx::FilePath inFilePath = folderPath;
				inFilePath.join(filePath.getFileName());

				bx::FilePath outFilePath = outFolderPath;
				stl::string fileName = filePath.getFileName().getPtr();
				fileName.append(".txt");
				outFilePath.join(fileName.c_str());

				convert(inFilePath, outFilePath);
			}
			else
			{
				bx::printf("Unsupported input file format '%s', skipping this file...\n", filePath);
			}
		}
		else if (fileInfo.type == bx::FileType::Dir && recursive)
		{
			
		}
	}
	bx::close(&dr);*/

	/*
	bx::printf("parse %f [s]\ntri reorder %f [s]\nconvert %f [s]\ng %d, p %d, v %d, i %d\n"
		, double(parseElapsed)/bx::getHPFrequency()
		, double(triReorderElapsed)/bx::getHPFrequency()
		, double(convertElapsed)/bx::getHPFrequency()
		, uint32_t(mesh.m_groups.size()-1)
		, writtenPrimitives
		, writtenVertices
		, writtenIndices
		);*/

	return bx::kExitSuccess;
}
