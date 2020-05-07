#include "app.h"
#include <GL/glew.h>
#include <imgui.h>
#include <stdint.h>
#include <string>

static uint32_t compile_shader(uint32_t type, const std::string& source) {
    uint32_t id = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        auto message = (char*)alloca(length);
        glGetShaderInfoLog(id, length, &length, message);
        fprintf(stderr, "Failed to compile %s shader: %s\n", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static uint32_t create_program(const std::string& vs_source, const std::string& fs_source) {
    uint32_t program = glCreateProgram();

    uint32_t vs = compile_shader(GL_VERTEX_SHADER, vs_source);
    uint32_t fs = compile_shader(GL_FRAGMENT_SHADER, fs_source);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void App::init() {
    float positions[] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vs = R"""(
        #version 330 core

        layout(location = 0) in vec4 position;

        void main() {
            gl_Position = position;
        }
    )""";

    std::string fs = R"""(
        #version 330 core

        layout(location = 0) out vec4 color;

        void main() {
            color = vec4(0.0, 1.0, 0.0, 1.0);
        }
    )""";

    shader = create_program(vs, fs);
    glUseProgram(shader);
}

void App::deinit() {
    glDeleteProgram(shader);
}

void App::frame() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
