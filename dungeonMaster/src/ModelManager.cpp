#include "../include/ModelManager.hpp"

#include <utility>


ModelManager::ModelManager(const glimac::FilePath &applicationPath)
        : _directory(applicationPath.dirPath() + "assets/models")
{
    std::cout << "directory: " << _directory << std::endl;
    loadModelFromFile("/sword/source/The_Sword.fbx", SWORD_MODEL);
}

bool ModelManager::loadModelFromFile(const std::string &path, const char *modelName)
{
    std::string modelPath = _directory + path;
    std::cout << "modelPath: " << modelPath << std::endl;
    Model model(modelPath);

    if (model.getMeshesSize() == 0)
    {
        return false;
    }

    _models.emplace(modelName, model);
    return true;
}

Model ModelManager::getModel(const string &modelName) const
{
    return _models.at(modelName);
}

