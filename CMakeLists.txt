cmake_minimum_required(VERSION 3.0.0)
project(2DRenderer)

file(GLOB SRC Src/*.cpp Include/*.h Tests/Src/*.cpp Tests/Include/*.h Vendor/imgui/*.cpp Vendor/imgui/*.h)
add_executable(2DRenderer ${SRC})

target_link_libraries(2DRenderer GL GLEW glfw imgui)

# Copy shaders to binary dir
add_custom_command( 
        TARGET 2DRenderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Shaders/
                ${CMAKE_CURRENT_BINARY_DIR}/Shaders) 
   
# Copy res to binary dir  
add_custom_command( 
        TARGET 2DRenderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
                ${CMAKE_SOURCE_DIR}/Res/
                ${CMAKE_CURRENT_BINARY_DIR}/Res)
 

                