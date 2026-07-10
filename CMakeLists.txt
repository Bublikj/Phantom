# 1. Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# 2. Имя проекта и версия
project(Phantom VERSION 1.0.0 LANGUAGES CXX)

# 3. Поиск всех исходных файлов в папке src
file(GLOB SOURCES "src/*.cpp")

# 4. Указание директорий с заголовочными файлами (.h)
include_directories(include)

# 5. Создание исполняемого файла
add_executable(phantom ${SOURCES})

# 6. (Опционально) Линковка сторонних библиотек
# target_link_libraries(my_app PRIVATE имя_библиотеки)
