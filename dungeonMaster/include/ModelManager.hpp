#pragma once

#include <unordered_map>
#include <memory.h>

#include "Mesh.hpp"
#include "Model.hpp"

class ModelManager
{
private:
    std::string                            _directory;
    std::unordered_map<std::string, Model> _models;

    bool loadModelFromFile(const std::string &path, const char *modelName);

    static constexpr const char *SWORD_MODEL = "sword";
    static constexpr const char *CHEST_MODEL = "chest";

    Model getModel(const std::string &modelName) const;

    friend class DrawingProgram;

public:
    explicit ModelManager(const glimac::FilePath &applicationPath);

    ~ModelManager() = default;
};