# 1. Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# 2. Имя проекта и версия
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# 3. Указание стандарта C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Поиск всех исходных файлов в папке src
file(GLOB SOURCES "src/*.cpp")

# 5. Указание директорий с заголовочными файлами (.h)
include_directories(include)

# 6. Создание исполняемого файла
add_executable(phantom ${SOURCES})

# 7. (Опционально) Линковка сторонних библиотек
# target_link_libraries(my_app PRIVATE имя_библиотеки)
