#include "include/Game.hpp"

int main(int argc, char **argv)
{
    FilePath filePath(argv[0]);
    Game     game(filePath, 800.f * 2.f, 600.f * 2.f);

    return game.run();
}

//    // Initialize glew for OpenGL3+ support
//    GLenum glewInitError = glewInit();
//    if (GLEW_OK != glewInitError)
//    {
//        std::cerr << glewGetErrorString(glewInitError) << std::endl;
//        return EXIT_FAILURE;
//    }
//
//    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
//    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
//
//    /*********************************
//     * HERE SHOULD COME THE INITIALIZATION CODE
//     *********************************/
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
////    ShapeVertex vertices[] = {{ vec3(1.0f, 1.0f, 0.0f),   vec3(1.0f, 1.0f, 0.0f),   vec2(1.0f, 0.0f) },
////                              { vec3(1.0f, -1.0f, 0.0f),  vec3(1.0f, -1.0f, 0.0f),  vec2(1.0f, 1.0f) },
////                              { vec3(-1.0f, -1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f) },
////
////                              { vec3(1.0f, 1.0f, 0.0f),   vec3(1.0f, 1.0f, 0.0f),   vec2(1.0f, 0.0f) },
////                              { vec3(-1.0f, -1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f) },
////                              { vec3(-1.0f, 1.0f, 0.0f),  vec3(-1.0f, 1.0f, 0.0f),  vec2(0.0f, 0.0f) }
////    };
//
////    ShapeVertex vertices[] = {{ vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f) },
////                              { vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f) },
////                              { vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) },
////
////                              { vec3(1.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f) },
////                              { vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) },
////                              { vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) }
////    };
//
//    ShapeVertex vertices[] = {{ vec3(0.5f, 0.5f, 0.0f),   vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 0.0f) },
//                              { vec3(0.5f, -0.5f, 0.0f),  vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 1.0f) },
//                              { vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 1.0f) },
//
//                              { vec3(0.5f, 0.5f, 0.0f),   vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 0.0f) },
//                              { vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 1.0f) },
//                              { vec3(-0.5f, 0.5f, 0.0f),  vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 0.0f) }
//    };
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(ShapeVertex) * 6, vertices, GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    // -------- VAO --------
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    const GLuint VERTEX_ATTR_POSITION  = 0;
//    const GLuint VERTEX_ATTR_NORMAL    = 1;
//    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
//
//    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
//    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
//    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
//                          (const GLvoid *) offsetof(ShapeVertex, position));
//    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
//                          (const GLvoid *) offsetof(ShapeVertex, normal));
//    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
//                          (const GLvoid *) offsetof(ShapeVertex, texCoords));
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    // -------- Shaders --------
//
////    program.use();
////
////    GLint uMVPMatrix    = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
////    GLint uMVMatrix     = glGetUniformLocation(program.getGLId(), "uMVMatrix");
////    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
////    GLint uTexture      = glGetUniformLocation(program.getGLId(), "uTexture");
//
////    glEnable(GL_DEPTH_TEST);
//
////    unique_ptr<Image> walls = loadImage(applicationPath.dirPath() + "assets/textures/walls.jpg");
////    if (walls == NULL)
////    {
////        std::cout << "Error while loading the walls image" << std::endl;
////        return 0;
////    }
////    GLuint wallTexture;
////    glGenTextures(1, &wallTexture);
////    glBindTexture(GL_TEXTURE_2D, wallTexture);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, walls->getWidth(), walls->getHeight(), 0, GL_RGBA,
////                 GL_FLOAT, walls->getPixels());
////    glBindTexture(GL_TEXTURE_2D, 0);
////
////
////    unique_ptr<Image> floor = loadImage(applicationPath.dirPath() + "assets/textures/floor.png");
////    if (floor == NULL)
////    {
////        std::cout << "Error while loading the floor image" << std::endl;
////        return 0;
////    }
////    GLuint floorTexture;
////    glGenTextures(1, &floorTexture);
////    glBindTexture(GL_TEXTURE_2D, floorTexture);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, floor->getWidth(), floor->getHeight(), 0, GL_RGBA,
////                 GL_FLOAT, floor->getPixels());
////    glBindTexture(GL_TEXTURE_2D, 0);
//
//    // Application loop:
//    bool                                               done         = false;
////    mat4 ProjMatrix                                                 = perspective(radians(70.f), width / height, 0.1f,
////                                                                                  100.f);
////    mat4 MVMMatrix, NormalMatrix;
//    FreeflyCamera                                      camera       = FreeflyCamera();
//    bool                                               canMove      = true;
//    std::chrono::time_point<std::chrono::system_clock> timeMoved    = std::chrono::system_clock::now();
//    mat4                                               globalMatrix = mat4(1.0f);
//
//
//    while (!done)
//    {
//        vector<vec3> objects = {
//                vec3(-1.f, 0.f, -5.f),
//                vec3(1.f, 0.f, -5.f)
//        };
//
//        if (!canMove && canMoveAgain(timeMoved))
//        {
//            std::cout << "Current Position: " << camera.getPosition() << "\n" << std::endl;
//            canMove = true;
//        }
//
//        if (canMove)
//        {
//            if (windowManager.isKeyPressed(SDLK_a))
//            {
//                camera.rotateLeft(90.f);
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//            if (windowManager.isKeyPressed(SDLK_e))
//            {
//                camera.rotateLeft(-90.f);
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//            if (windowManager.isKeyPressed(SDLK_z))
//            {
//                if (allowMovement(camera, objects, DirectionType::FORWARD))
//                {
//                    camera.moveFront(1.f);
//                }
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//            if (windowManager.isKeyPressed(SDLK_s))
//            {
//                if (allowMovement(camera, objects, DirectionType::BACKWARD))
//                {
//                    camera.moveFront(-1.f);
//                }
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//            if (windowManager.isKeyPressed(SDLK_q))
//            {
//                if (allowMovement(camera, objects, DirectionType::LEFT))
//                {
//                    camera.moveLeft(1.f);
//
//                }
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//            if (windowManager.isKeyPressed(SDLK_d))
//            {
//                if (allowMovement(camera, objects, DirectionType::RIGHT))
//                {
//                    camera.moveLeft(-1.f);
//
//                }
//                timeMoved = std::chrono::system_clock::now();
//                canMove   = false;
//            }
//        }
//
//
//        mat4 viewMatrix = camera.getViewMatrix();
//
//        // Event loop:
//        SDL_Event e;
//        while (windowManager.pollEvent(e))
//        {
//            if (e.type == SDL_QUIT)
//            {
//                done = true; // Leave the loop after this iteration
//            }
//        }
//
//        /*********************************
//         * HERE SHOULD COME THE RENDERING CODE
//         *********************************/
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        glBindVertexArray(vao);
//
//
//        // First Wall
//        glBindTexture(GL_TEXTURE_2D, wallTexture);
//        glUniform1i(uTexture, 0);
//        MVMMatrix    = globalMatrix;
//        MVMMatrix    = translate(MVMMatrix, vec3(-0.5f, 0.0f, -1));
//        MVMMatrix    = rotate(MVMMatrix, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
//        MVMMatrix    = viewMatrix * MVMMatrix;
//        NormalMatrix = transpose(inverse(MVMMatrix));
//        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMMatrix));
//        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMMatrix));
//        glUniform1i(uTexture, 0);
//        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        glBindTexture(GL_TEXTURE_2D, wallTexture);
//        glUniform1i(uTexture, 0);
//        MVMMatrix    = globalMatrix;
//        MVMMatrix    = translate(MVMMatrix, vec3(0.0f, 0.0f, -1.0));
////        MVMMatrix    = rotate(MVMMatrix, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
//        MVMMatrix    = viewMatrix * MVMMatrix;
//        NormalMatrix = transpose(inverse(MVMMatrix));
//        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMMatrix));
//        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMMatrix));
//        glUniform1i(uTexture, 0);
//        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
////        for (int i = 0; i < 5; ++i)
////        {
////            // First Wall
////            glBindTexture(GL_TEXTURE_2D, wallTexture);
////            glUniform1i(uTexture, 0);
////            MVMMatrix    = globalMatrix;
//////            MVMMatrix = translate(MVMMatrix, vec3(-0.5f, 0.0f, -5.0f));
////            MVMMatrix    = translate(MVMMatrix, vec3(-0.5f, 0.0f, -i));
////            MVMMatrix    = rotate(MVMMatrix, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
////            MVMMatrix    = viewMatrix * MVMMatrix;
////            NormalMatrix = transpose(inverse(MVMMatrix));
////            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMMatrix));
////            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMMatrix));
////            glUniform1i(uTexture, 0);
////            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
////            glDrawArrays(GL_TRIANGLES, 0, 6);
////
////            // Second Wall
////            MVMMatrix    = globalMatrix;
//////            MVMMatrix = translate(MVMMatrix, vec3(0.5f, 0.0f, -5.0f));
////            MVMMatrix    = translate(MVMMatrix, vec3(0.5f, 0.0f, -i));
////            MVMMatrix    = rotate(MVMMatrix, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
////            MVMMatrix    = viewMatrix * MVMMatrix;
////            NormalMatrix = transpose(inverse(MVMMatrix));
////            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMMatrix));
////            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMMatrix));
////            glUniform1i(uTexture, 0);
////            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
////            glDrawArrays(GL_TRIANGLES, 0, 6);
////
////            // Floor
////            glBindTexture(GL_TEXTURE_2D, floorTexture);
////            glUniform1i(uTexture, 0);
////            MVMMatrix    = globalMatrix;
//////            MVMMatrix = translate(MVMMatrix, vec3(0.0f, -0.5f, -5.0f));
////            MVMMatrix    = translate(MVMMatrix, vec3(0.0f, -0.5f, -i));
////            MVMMatrix    = rotate(MVMMatrix, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
////            MVMMatrix    = viewMatrix * MVMMatrix;
////            NormalMatrix = transpose(inverse(MVMMatrix));
////            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(ProjMatrix * MVMMatrix));
////            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMMatrix));
////            glUniform1i(uTexture, 0);
////            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
////            glDrawArrays(GL_TRIANGLES, 0, 6);
////        }
//
//
//        glBindVertexArray(0);
//
//        // Update the display
//        windowManager.swapBuffers();
//    }
//
//    glDeleteTextures(1, &wallTexture);
//
//    return EXIT_SUCCESS;
//}
