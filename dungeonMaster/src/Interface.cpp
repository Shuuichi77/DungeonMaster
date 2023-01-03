#include "../include/Interface.hpp"
#include "../include/TextureManager.hpp"

Interface::Interface(Player &player, unsigned int windowWidth, unsigned int windowHeight,
                     ModelManager &modelManager, const TextureManager &textureManager,
                     Program &program, FreeflyCamera &camera, mat4 &projMatrix, GLint &uMVPMatrix, GLint &uMVMatrix,
                     GLint &uNormalMatrix, GLint &uTexture, GLuint &vao)
        : _player(player)
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _modelManager(modelManager)
        , _textureManager(textureManager)
        , _program(program)
        , _camera(camera)
        , _projMatrix(projMatrix)
        , _uMVPMatrix(uMVPMatrix)
        , _uMVMatrix(uMVMatrix)
        , _uNormalMatrix(uNormalMatrix)
        , _uTexture(uTexture)
        , _vao(vao) {}

void Interface::drawInterface()
{
    _modelManager.drawMultipleFixModels(HEALTH_MODEL, _camera.getPosition(), _program,
                                        _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix,
                                        (float) (_windowWidth * 0.00000375), _player.getHealth());

    _modelManager.drawMultipleFixModels(KEY_MODEL, _camera.getPosition(), _program,
                                        _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix,
                                        (float) (_windowWidth * 0.000008), _player.getNbKeys());

    // Models Inventory from here
    drawInventoryBackground();


    _modelManager.drawWeapon(Weapon::getModelTypeFromWeaponType(_player.getCurrentWeapon()->getWeaponType()),
                             _program, _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix,
                             _player.getIsAttacking());

    if (_player.getIsAttacking())
    {
        _player.modelHasAttacked();
    }

    _modelManager.drawModel(MONEY_MODEL, _camera.getPosition(), DirectionType::NEUTRAL, _program, _projMatrix,
                            _uMVPMatrix, _uMVMatrix, _uNormalMatrix);

    _modelManager.drawModel(SKULL_MODEL, _camera.getPosition(), DirectionType::NEUTRAL, _program, _projMatrix,
                            _uMVPMatrix, _uMVMatrix, _uNormalMatrix);

    _modelManager.drawInventory(_player.getItems(), _player.getWeaponsTypes(), _program, _projMatrix, _uMVPMatrix,
                                _uMVMatrix, _uNormalMatrix);
}

void Interface::drawInventoryBackground()
{
    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::INVENTORY_TEXTURE));
    glUniform1i(_uTexture, 0);

    ModelTransformation modelTransformation = _modelManager.getModelTransformations().getModelTransformation(
            INVENTORY_MODEL);
    mat4                MVMMatrix           = _modelManager.applyModelTransformation(modelTransformation,
                                                                                     _camera.getPosition());

    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

