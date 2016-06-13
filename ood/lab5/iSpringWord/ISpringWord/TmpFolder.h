#pragma once
#include "ICommand_fwd.h"
#include <filesystem>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

static const std::string IMAGES_FOLDER = "images";

class CTmpFolder
{
public:
	CTmpFolder(std::string & folder)
	{
		m_folder = fs::temp_directory_path().string() + folder;
		m_imagesFolder = m_folder + "/" + IMAGES_FOLDER;
		RemoveTmpFolder();
		fs::create_directories(m_imagesFolder);

	}
	const std::string& GetPath() const
	{
		return m_folder;
	}
	const std::string& GetImagesPath() const
	{
		return m_imagesFolder;
	}
	~CTmpFolder()
	{
		RemoveTmpFolder();
	}

private:
	std::string m_folder;
	std::string m_imagesFolder;

	void RemoveTmpFolder() const
	{
		if (fs::exists(m_folder) && fs::is_directory(m_folder))
		{
			fs::remove_all(m_folder);
		}
	}
};

