#include "lisp-core.h"
#include "lisp-gl.h"
#include "lisp-dl.h"

int main() {
    auto test = R"(
    (begin
        (glfwInit)
        (glfwWindowHint GLFW_CONTEXT_VERSION_MAJOR 3)
        (glfwWindowHint GLFW_CONTEXT_VERSION_MINOR 3)
        (glfwWindowHint GLFW_OPENGL_PROFILE GLFW_OPENGL_CORE_PROFILE)
        (glfwWindowHint GLFW_RESIZABLE GL_FALSE)

        (def 'window (glfwCreateWindow 800 600 "Lisp Test" null null))

        (if '(== window null)
            '(begin
                (print "Failed to create GLFW window")
                (glfwTerminate)
                (exit -1)
            ) '()
        )

        (glfwMakeContextCurrent window)

        (def 'width (malloc 4))
        (def 'height (malloc 4))

        (glfwGetFramebufferSize window width height)

        (glViewport 0 0 (ptr_to_int width) (ptr_to_int height))

        (while '(! (glfwWindowShouldClose window))
            '(begin
                (glfwPollEvents)
                (glClear GL_COLOR_BUFFER_BIT)
                (glClearColor 127 127 127 127)
                (glfwSwapBuffers window)
            )
        )

        (free width)
        (free height)
    )
    )";

    lisp::Env env;
    import_core(env);
    import_dl(env);
    import_gl(env);

    lisp::eval(&env, test);
}